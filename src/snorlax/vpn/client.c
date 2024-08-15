#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <snorlax/network/tun.h>
#include <snorlax/descriptor/event/subscription.h>
#include <snorlax/buffer/mem.h>

#include "client.h"
#include "client/app.h"

typedef vpn_client_t * (*vpn_client_rem_t)(vpn_client_t *);

typedef int32_t (*vpn_client_open_t)(___notnull vpn_client_t *);
typedef int64_t (*vpn_client_read_t)(___notnull vpn_client_t *);
typedef int64_t (*vpn_client_write_t)(___notnull vpn_client_t *);
typedef int32_t (*vpn_client_close_t)(___notnull vpn_client_t *);
typedef int32_t (*vpn_client_check_t)(___notnull vpn_client_t *, uint32_t);

typedef int32_t (*vpn_client_shutdown_t)(___notnull vpn_client_t *, uint32_t);

static int32_t vpn_client_func_open(___notnull vpn_client_t * descriptor);

static vpn_client_func_t func = {
    (vpn_client_rem_t) socket_func_rem,
    vpn_client_func_open,
    (vpn_client_read_t) descriptor_func_read,
    (vpn_client_write_t) descriptor_func_write,
    (vpn_client_close_t) descriptor_func_close,
    (vpn_client_check_t) socket_func_check,
    (vpn_client_shutdown_t) socket_func_shutdown
};

extern vpn_client_t * vpn_client_gen(int32_t domain, int32_t type, int32_t protocol, void * addr, uint64_t addrlen) {
    vpn_client_t * descriptor = (vpn_client_t *) calloc(1, sizeof(vpn_client_t));

    descriptor->func = address_of(func);

    descriptor->value = invalid;
    descriptor->buffer.in = (buffer_t *) buffer_mem_gen(0);
    descriptor->buffer.out = (buffer_t *) buffer_mem_gen(0);
    descriptor->status = descriptor_state_close;
    descriptor->domain = domain;
    descriptor->type = type;
    descriptor->protocol = protocol;

    if(addr && addrlen) {
        descriptor->addr.value = malloc(addrlen);
        descriptor->addr.len = addrlen;
        memcpy(descriptor->addr.value, addr, addrlen);
    } else {
#ifndef   RELEASE
        snorlaxdbg(addr == nil || addrlen == 0, false, "critical", "");
#endif // RELEASE
    }

    return descriptor;
}

extern int32_t vpn_client_func_open(___notnull vpn_client_t * descriptor) {
#ifndef   RELEASE
    snorlaxdbg(descriptor == nil, false, "critical", "");
#endif // RELEASE

    if(descriptor_exception_get(descriptor)) {
        return fail;
    }

    if(descriptor->value <= invalid) {
        descriptor->value = socket(descriptor->domain, descriptor->type, descriptor->protocol);
        if(descriptor->value <= invalid) {
            descriptor_exception_set(descriptor, descriptor_exception_type_system, errno, socket);
            return fail;
        }

        vpn_client_app_t * app = vpn_client_app_get();

        network_tun_protect((network_tun_t *) app->tun->descriptor, (descriptor_t *) descriptor);

        descriptor_nonblock_on((descriptor_t *) descriptor);

        if(connect(descriptor->value, (struct sockaddr *) descriptor->addr.value, descriptor->addr.len) == fail) {
            if(errno == EAGAIN || errno == EALREADY || errno == EINPROGRESS) {
                descriptor->status = descriptor->status & (~descriptor_state_close);
                return success;
            }
#ifndef   RELEASE
                snorlaxdbg(false, true, "warning", "fail to connect => %d", errno);
#endif // RELEASE

            if(close(descriptor->value) == fail) {
#ifndef   RELEASE
                snorlaxdbg(false, true, "warning", "fail to close => %d", errno);
#endif // RELEASE
            }

            descriptor->value = invalid;
            descriptor_exception_set(descriptor, descriptor_exception_type_system, errno, socket);
            return fail;
        }

        descriptor->status = descriptor->status | (descriptor_state_open | descriptor_state_write);
        descriptor->status = descriptor->status & (~descriptor_state_close);

        return success;
    } else if((descriptor->status & descriptor_state_open) == 0) {
        snorlaxdbg(descriptor->status & descriptor_state_open, false, "implement", "");
    }

    return success;
}