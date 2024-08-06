/**
 * @file        snorlax/protocol/internet/user/datagram.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 5, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_USER_DATAGRAM__H__
#define   __SNORLAX__PROTOCOL_USER_DATAGRAM__H__

#include <snorlax.h>
#include <snorlax/protocol/module.h>
#include <snorlax/protocol/module/map.h>
#include <snorlax/protocol/context.h>

struct user_datagram_protocol_packet;

struct user_datagram_protocol_module;
struct user_datagram_protocol_module_func;
struct user_datagram_protocol_context;
struct user_datagram_protocol_context_func;

typedef struct user_datagram_protocol_packet user_datagram_protocol_packet_t;

typedef struct user_datagram_protocol_module user_datagram_protocol_module_t;
typedef struct user_datagram_protocol_module_func user_datagram_protocol_module_func_t;
typedef struct user_datagram_protocol_context user_datagram_protocol_context_t;
typedef struct user_datagram_protocol_context_func user_datagram_protocol_context_func_t;

struct user_datagram_protocol_packet {
    uint16_t source;
    uint16_t destination;
    uint16_t length;
    uint16_t checksum;
};

struct user_datagram_protocol_module {
    user_datagram_protocol_module_func_t * func;
    sync_t * sync;
    protocol_module_t * parent;
    protocol_module_map_t * map;
};

struct user_datagram_protocol_module_func {
    user_datagram_protocol_module_t * (*rem)(user_datagram_protocol_module_t *);
    int32_t (*deserialize)(user_datagram_protocol_module_t *, protocol_packet_t *, uint32_t, protocol_context_t *, protocol_context_t **);
    int32_t (*serialize)(user_datagram_protocol_module_t *, protocol_context_t *, protocol_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(user_datagram_protocol_module_t *, FILE *, protocol_context_t *);
};

struct user_datagram_protocol_context;
struct user_datagram_protocol_context_func;


#endif // __SNORLAX__PROTOCOL_USER_DATAGRAM__H__
