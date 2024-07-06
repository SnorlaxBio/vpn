#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <unistd.h>

#include "tun.h"

typedef virtual_private_network_tun_t * (*virtual_private_network_tun_func_rem_t)(___notnull virtual_private_network_tun_t *);

typedef int32_t (*virtual_private_network_tun_func_open_t)(___notnull virtual_private_network_tun_t *);
typedef int64_t (*virtual_private_network_tun_func_read_t)(___notnull virtual_private_network_tun_t *);
typedef int64_t (*virtual_private_network_tun_func_write_t)(___notnull virtual_private_network_tun_t *);
typedef int32_t (*virtual_private_network_tun_func_close_t)(___notnull virtual_private_network_tun_t *);
typedef int32_t (*virtual_private_network_tun_func_check_t)(___notnull virtual_private_network_tun_t *, uint32_t);

static int32_t virtual_private_network_tun_func_open(___notnull virtual_private_network_tun_t * descriptor);

static virtual_private_network_tun_func_t func = {
    (virtual_private_network_tun_func_rem_t) descriptor_func_rem,
    virtual_private_network_tun_func_open,
    (virtual_private_network_tun_func_read_t) descriptor_func_read,
    (virtual_private_network_tun_func_write_t) descriptor_func_write,
    (virtual_private_network_tun_func_close_t) descriptor_func_close,
    (virtual_private_network_tun_func_check_t) descriptor_func_check,
};

extern virtual_private_network_tun_t * virtual_private_network_tun_gen(void) {
    virtual_private_network_tun_t * descriptor = (virtual_private_network_tun_t *) calloc(1, sizeof(virtual_private_network_tun_t));

    descriptor->func = address_of(func);

    descriptor->value = invalid;

    descriptor->buffer.in = buffer_gen(0);
    descriptor->buffer.out = buffer_gen(0);

    descriptor->status = descriptor_state_close;

    return descriptor;
}

static int32_t virtual_private_network_tun_func_open(___notnull virtual_private_network_tun_t * descriptor) {
#ifndef   RELEASE
    snorlaxdbg(descriptor == nil, false, "critical", "");
#endif // RELEASE

    if(descriptor->value <= invalid) {
        descriptor->value = open("/dev/net/tun", O_RDWR);

        if(descriptor->value <= invalid) {
#ifndef   RELEASE
            snorlaxdbg(descriptor->value <= invalid, false, "critical", "fail to open => %d", errno);
#endif // RELEASE
            descriptor_exception_set(descriptor, descriptor_exception_type_system, errno, open);

            return fail;
        }

        descriptor->status = descriptor->status | (descriptor_state_open | descriptor_state_write);
        descriptor->status = descriptor->status & (~descriptor_state_close);

        struct ifreq req;
        memset(&req, 0, sizeof(req));

        req.ifr_flags = req.ifr_flags | IFF_MULTI_QUEUE;    // IFF_ONE_QUEUE
        req.ifr_flags = req.ifr_flags | IFF_NO_PI;          // IFF_ONE_QUEUE
        req.ifr_flags = req.ifr_flags | IFF_TUN;

        snprintf(req.ifr_name, 16, "tun%d", 0);

        if(ioctl(descriptor->value, TUNSETIFF, &req) < 0) {
#ifndef   RELEASE
            snorlaxdbg(true, false, "critical", "fail to ioctl => %d", errno);
#endif // RELEASE
            descriptor_exception_set(descriptor, descriptor_exception_type_system, errno, open);

            return fail;
        }

        // TX QUEUE SET / 
        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        if(fd > 0) {
            req.ifr_qlen = ETH_DATA_LEN;
            if(ioctl(fd, SIOCSIFTXQLEN, &req) < 0) {
#ifndef   RELEASE
                snorlaxdbg(false, true, "warning", "fail to ioctl(...) caused by %d", errno);
#endif // RELEASE
            }

            ((struct sockaddr_in *)(&(req.ifr_addr)))->sin_family = AF_INET;
            ((struct sockaddr_in *)(&(req.ifr_addr)))->sin_port = 0;
            ((struct sockaddr_in *)(&(req.ifr_addr)))->sin_addr.s_addr = inet_addr("10.0.0.1");

            if(ioctl(fd, SIOCSIFADDR, &req) < 0) {
#ifndef   RELEASE
                snorlaxdbg(false, true, "warning", "fail to ioctl(...) caused by %d", errno);
#endif // RELEASE
            }

            ((struct sockaddr_in *)(&(req.ifr_addr)))->sin_addr.s_addr = inet_addr("255.255.255.0");

            if(ioctl(fd, SIOCSIFNETMASK, &req) < 0) {
#ifndef   RELEASE
                snorlaxdbg(false, true, "warning", "fail to ioctl(...) caused by %d", errno);
#endif // RELEASE
            }

            close(fd);
        } else {
#ifndef   RELEASE
            snorlaxdbg(false, true, "warning", "fail to socket(...) => %d", errno);
#endif // RELEASE
        }

        // SET ADDR




        descriptor_nonblock_on((descriptor_t *) descriptor);

    } else {
#ifndef   RELEASE
        snorlaxdbg(false, true, "warning", "");
#endif // RELEASE
    }

    return success;
}