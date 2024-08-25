/**
 * @file        snorlax/virtual/private/network/socket/client.h
 * @brief
 * @details
 * 
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 24, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SOCKET_CLIENT__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SOCKET_CLIENT__H__

#include <snorlax.h>
#include <snorlax/descriptor.h>
#include <snorlax/socket/client.h>

struct virtual_private_network_socket_client;
struct virtual_private_network_socket_client_func;

typedef struct virtual_private_network_socket_client            virtual_private_network_socket_client_t;
typedef struct virtual_private_network_socket_client_func       virtual_private_network_socket_client_func_t;

struct virtual_private_network_socket_client {
    virtual_private_network_socket_client_func_t * func;
    sync_t * sync;
    ___reference event_object_meta_t * meta;
    descriptor_buffer_t buffer;
    descriptor_exception_t exception;
    int32_t value;
    uint32_t status;
    int32_t domain;
    int32_t type;
    int32_t protocol;
    socket_addr_t addr;
};

struct virtual_private_network_socket_client_func {
    virtual_private_network_socket_client_t * (*rem)(virtual_private_network_socket_client_t *);

    int32_t (*open)(___notnull virtual_private_network_socket_client_t *);
    int64_t (*read)(___notnull virtual_private_network_socket_client_t *);
    int64_t (*write)(___notnull virtual_private_network_socket_client_t *);
    int32_t (*close)(___notnull virtual_private_network_socket_client_t *);
    int32_t (*check)(___notnull virtual_private_network_socket_client_t *, uint32_t);

    int32_t (*shutdown)(___notnull virtual_private_network_socket_client_t *, uint32_t);
};

extern virtual_private_network_socket_client_t * virtual_private_network_socket_client_gen(int32_t domain, int32_t type, int32_t protocol, void * addr, uint64_t addrlen);

#define virutal_private_network_socket_client_factory                       ((socket_client_factory_t) virtual_private_network_socket_client_gen)

extern virtual_private_network_socket_client_t * virtual_private_network_socket_client_gen_tcp4(const uint8_t * destination, uint16_t port);
extern virtual_private_network_socket_client_t * virtual_private_network_socket_client_gen_tcp6(const uint8_t * destination, uint16_t port);

#define virtual_private_network_socket_client_rem(descriptor)               ((descriptor)->func->rem(descriptor))
#define virtual_private_network_socket_client_open(descriptor)              ((descriptor)->func->open(descriptor))
#define virtual_private_network_socket_client_read(descriptor)              ((descriptor)->func->read(descriptor))
#define virtual_private_network_socket_client_write(descriptor)             ((descriptor)->func->write(descriptor))
#define virtual_private_network_socket_client_close(descriptor)             ((descriptor)->func->close(descriptor))
#define virtual_private_network_socket_client_check(descriptor, state)      ((descriptor)->func->check(descriptor, state))
#define virtual_private_network_socket_client_shutdown(descriptor, how)     ((descriptor)->func->shutdown(descriptor, how))

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SOCKET_CLIENT__H__
