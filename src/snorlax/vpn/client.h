/**
 * @file        snorlax/vpn/client.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_CLIENT__H__
#define   __SNORLAX__VPN_CLIENT__H__

#include <snorlax.h>
#include <snorlax/descriptor.h>
#include <snorlax/socket.h>

struct vpn_client;
struct vpn_client_func;

typedef struct vpn_client vpn_client_t;
typedef struct vpn_client_func vpn_client_func_t;

struct vpn_client {
    vpn_client_func_t * func;
    sync_t * sync;
    event_object_meta_t * meta;
    descriptor_buffer_t buffer;
    descriptor_exception_t exception;
    int32_t value;
    uint32_t status;
    int32_t domain;
    int32_t type;
    int32_t protocol;
    socket_addr_t addr;
};

struct vpn_client_func {
    vpn_client_t * (*rem)(vpn_client_t *);

    int32_t (*open)(___notnull vpn_client_t *);
    int64_t (*read)(___notnull vpn_client_t *);
    int64_t (*write)(___notnull vpn_client_t *);
    int32_t (*close)(___notnull vpn_client_t *);
    int32_t (*check)(___notnull vpn_client_t *, uint32_t);

    int32_t (*shutdown)(___notnull vpn_client_t *, uint32_t);
};

extern vpn_client_t * vpn_client_gen(int32_t domain, int32_t type, int32_t protocol, void * addr, uint64_t addrlen);
extern vpn_client_t * vpn_client_tcp4_gen(uint32_t destination, uint16_t port);
extern vpn_client_t * vpn_client_tcp6_gen(const uint8_t * destination, uint16_t port);

#define vpn_client_rem(descriptor)               ((descriptor)->func->rem(descriptor))
#define vpn_client_open(descriptor)              ((descriptor)->func->open(descriptor))
#define vpn_client_read(descriptor)              ((descriptor)->func->read(descriptor))
#define vpn_client_write(descriptor)             ((descriptor)->func->write(descriptor))
#define vpn_client_close(descriptor)             ((descriptor)->func->close(descriptor))
#define vpn_client_check(descriptor, state)      ((descriptor)->func->check(descriptor, state))
#define vpn_client_shutdown(descriptor, how)     ((descriptor)->func->shutdown(descriptor, how))

#endif // __SNORLAX__VPN_CLIENT__H__
