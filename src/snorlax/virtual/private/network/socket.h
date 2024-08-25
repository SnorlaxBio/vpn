/**
 * @file        snorlax/virtual/private/network/socket.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 24, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SOCKET__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SOCKET__H__

#include <snorlax.h>
#include <snorlax/descriptor.h>
#include <snorlax/socket.h>

struct virtual_private_network_socket;
struct virtual_private_network_socket_func;

typedef struct virtual_private_network_socket           virtual_private_network_socket_t;
typedef struct virtual_private_network_socket_func      virtual_private_network_socket_func_t;

struct virtual_private_network_socket {
    virtual_private_network_socket_func_t * func;
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

struct virtual_private_network_socket_func {
    virtual_private_network_socket_t * (*rem)(virtual_private_network_socket_t *);

    int32_t (*open)(___notnull virtual_private_network_socket_t *);
    int64_t (*read)(___notnull virtual_private_network_socket_t *);
    int64_t (*write)(___notnull virtual_private_network_socket_t *);
    int32_t (*close)(___notnull virtual_private_network_socket_t *);
    int32_t (*check)(___notnull virtual_private_network_socket_t *, uint32_t);

    int32_t (*shutdown)(___notnull virtual_private_network_socket_t *, uint32_t);
};

#define virtual_private_network_socket_rem(descriptor)              ((descriptor)->func->rem(descriptor))
#define virtual_private_network_socket_open(descriptor)             ((descriptor)->func->open(descriptor))
#define virtual_private_network_socket_read(descriptor)             ((descriptor)->func->read(descriptor))
#define virtual_private_network_socket_write(descriptor)            ((descriptor)->func->write(descriptor))
#define virtual_private_network_socket_close(descriptor)            ((descriptor)->func->close(descriptor))
#define virtual_private_network_socket_check(descriptor, state)     ((descriptor)->func->check(descriptor, state))
#define virtual_private_network_socket_shutdown(descriptor, how)    ((descriptor)->func->shutdown(descriptor, how))

#define virtual_private_network_socket_meta_get(descriptor)         ((descriptor)->meta)

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SOCKET__H__
