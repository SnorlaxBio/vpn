/**
 * @file        snorlax/vpn/tun.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 5, 2024
 */

#ifndef   __SNORLAX__VPN_TUN__H__
#define   __SNORLAX__VPN_TUN__H__

#include <snorlax.h>
#include <snorlax/descriptor.h>

struct virtual_private_network_tun;
struct virtual_private_network_tun_func;

typedef struct virtual_private_network_tun virtual_private_network_tun_t;
typedef struct virtual_private_network_tun_func virtual_private_network_tun_func_t;

struct virtual_private_network_tun {
    virtual_private_network_tun_func_t * func;
    sync_t * sync;
    descriptor_buffer_t buffer;
    descriptor_exception_t exception;
    int32_t value;
    uint32_t status;
};

struct virtual_private_network_tun_func {
    virtual_private_network_tun_t * (*rem)(___notnull virtual_private_network_tun_t *);

    int32_t (*open)(___notnull virtual_private_network_tun_t *);
    int64_t (*read)(___notnull virtual_private_network_tun_t *);
    int64_t (*write)(___notnull virtual_private_network_tun_t *);
    int32_t (*close)(___notnull virtual_private_network_tun_t *);
    int32_t (*check)(___notnull virtual_private_network_tun_t *, uint32_t);

    int32_t (*protect)(___notnull virtual_private_network_tun_t *);
};

extern virtual_private_network_tun_t * virtual_private_network_tun_gen(void);

#define virtual_private_network_tun_rem(descriptor)             ((descriptor)->func->rem(descriptor))
#define virtual_private_network_tun_open(descriptor)            ((descriptor)->func->open(descriptor))
#define virtual_private_network_tun_read(descriptor)            ((descriptor)->func->read(descriptor))
#define virtual_private_network_tun_write(descriptor)           ((descriptor)->func->write(descriptor))
#define virtual_private_network_tun_close(descriptor)           ((descriptor)->func->close(descriptor))
#define virtual_private_network_tun_check(descriptor, state)    ((descriptor)->func->check(descriptor, state))
#define virtual_private_network_tun_protect(descriptor)         ((descriptor)->func->protect(descriptor))


#endif // __SNORLAX__VPN_TUN__H__
