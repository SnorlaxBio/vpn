#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "client.h"

#include "../application.h"

typedef virtual_private_network_socket_client_t * (*virtual_private_network_socket_client_rem_t)(virtual_private_network_socket_client_t *);

typedef int32_t (*virtual_private_network_socket_client_open_t)(___notnull virtual_private_network_socket_client_t *);
typedef int64_t (*virtual_private_network_socket_client_read_t)(___notnull virtual_private_network_socket_client_t *);
typedef int64_t (*virtual_private_network_socket_client_write_t)(___notnull virtual_private_network_socket_client_t *);
typedef int32_t (*virtual_private_network_socket_client_close_t)(___notnull virtual_private_network_socket_client_t *);
typedef int32_t (*virtual_private_network_socket_client_check_t)(___notnull virtual_private_network_socket_client_t *, uint32_t);

typedef int32_t (*virtual_private_network_socket_client_shutdown_t)(___notnull virtual_private_network_socket_client_t *, uint32_t);

static int32_t virtual_private_network_socket_client_func_open(___notnull virtual_private_network_socket_client_t * descriptor);

static virtual_private_network_socket_client_func_t func = {
    (virtual_private_network_socket_client_rem_t) socket_func_rem,
    virtual_private_network_socket_client_func_open,
    (virtual_private_network_socket_client_read_t) descriptor_func_read,
    (virtual_private_network_socket_client_write_t) descriptor_func_write,
    (virtual_private_network_socket_client_close_t) descriptor_func_close,
    (virtual_private_network_socket_client_check_t) socket_func_check,
    (virtual_private_network_socket_client_shutdown_t) socket_func_shutdown
};

extern virtual_private_network_socket_client_t * virtual_private_network_socket_client_gen_tcp4(const uint8_t * destination, uint16_t port) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = uint32_of(destination);
    addr.sin_port = port;

    return virtual_private_network_socket_client_gen(AF_INET, SOCK_STREAM, IPPROTO_TCP, address_of(addr), sizeof(struct sockaddr_in));
}

extern virtual_private_network_socket_client_t * virtual_private_network_socket_client_gen_tcp6(const uint8_t * destination, uint16_t port) {
    struct sockaddr_in6 addr;

    addr.sin6_family = AF_INET6;
    memcpy(addr.sin6_addr.s6_addr, destination, 16);
    addr.sin6_port = port;

    return virtual_private_network_socket_client_gen(AF_INET6, SOCK_STREAM, IPPROTO_TCP, address_of(addr), sizeof(struct sockaddr_in6));
}

extern virtual_private_network_socket_client_t * virtual_private_network_socket_client_gen(int32_t domain, int32_t type, int32_t protocol, void * addr, uint64_t addrlen) {
    virtual_private_network_socket_client_t * descriptor = (virtual_private_network_socket_client_t *) calloc(1, sizeof(virtual_private_network_socket_client_t));

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

extern int32_t virtual_private_network_socket_client_func_open(___notnull virtual_private_network_socket_client_t * descriptor) {
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

        virtual_private_network_application_t * application = virtual_private_network_application_get();

        network_tun_protect(virtual_private_network_application_tun_get(application), (descriptor_t *) descriptor);

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