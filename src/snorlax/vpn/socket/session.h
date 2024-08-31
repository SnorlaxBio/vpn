/**
 * @file        snorlax/vpn/socket/session.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 24, 2024
 */

#ifndef   __SNORLAX__VPN_SOCKET_SESSION__H__
#define   __SNORLAX__VPN_SOCKET_SESSION__H__

#include <snorlax.h>
#include <snorlax/descriptor.h>
#include <snorlax/socket/session.h>

struct vpn_socket_session;
struct vpn_socket_session_func;

typedef struct vpn_socket_session           vpn_socket_session_t;
typedef struct vpn_socket_session_func      vpn_socket_session_func_t;

struct vpn_socket_session {
    vpn_socket_session_func_t * func;
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

struct vpn_socket_session_func {
    vpn_socket_session_t * (*rem)(___notnull vpn_socket_session_t *);

    int32_t (*open)(___notnull vpn_socket_session_t *);
    int64_t (*read)(___notnull vpn_socket_session_t *);
    int64_t (*write)(___notnull vpn_socket_session_t *);
    int32_t (*close)(___notnull vpn_socket_session_t *);
    int32_t (*check)(___notnull vpn_socket_session_t *, uint32_t);

    int32_t (*shutdown)(___notnull vpn_socket_session_t *, uint32_t);
};

extern vpn_socket_session_t * vpn_socket_session_gen(int32_t value, int32_t domain, int32_t type, int32_t protocol, void * addr, uint64_t addrlen);

#define vpn_socket_session_rem(descriptor)              ((descriptor)->func->rem(descriptor))
#define vpn_socket_session_open(descriptor)             ((descriptor)->func->open(descriptor))
#define vpn_socket_session_read(descriptor)             ((descriptor)->func->read(descriptor))
#define vpn_socket_session_write(descriptor)            ((descriptor)->func->write(descriptor))
#define vpn_socket_session_close(descriptor)            ((descriptor)->func->close(descriptor))
#define vpn_socket_session_check(descriptor, state)     ((descriptor)->func->check(descriptor, state))
#define vpn_socket_session_shutdown(descriptor, how)    ((descriptor)->func->shutdown(descriptor, how))

#endif // __SNORLAX__VPN_SOCKET_SESSION__H__
