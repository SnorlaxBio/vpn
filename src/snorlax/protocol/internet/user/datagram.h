/**
 * @file        snorlax/protocol/internet/user/datagram.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 5, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_USER_DATAGRAM__H__
#define   __SNORLAX__PROTOCOL_USER_DATAGRAM__H__

#include <snorlax.h>
#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

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

#define user_datagram_protocol_packet_length_min                        8

extern uint16_t user_datagram_protocol_checksum_cal(user_datagram_protocol_packet_t * datagram, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen);

typedef int32_t (*user_datagram_protocol_context_handler_t)(user_datagram_protocol_module_t *, uint32_t, internet_protocol_context_t *, user_datagram_protocol_context_t *);

struct user_datagram_protocol_module {
    user_datagram_protocol_module_func_t * func;
    sync_t * sync;
    uint16_t type;
    uint16_t addrlen;
    ___reference protocol_module_map_t * map;

    user_datagram_protocol_context_handler_t on;
};

struct user_datagram_protocol_module_func {
    user_datagram_protocol_module_t * (*rem)(user_datagram_protocol_module_t *);
    int32_t (*deserialize)(user_datagram_protocol_module_t *, protocol_packet_t *, uint64_t, internet_protocol_context_t *, user_datagram_protocol_context_t **);
    int32_t (*serialize)(user_datagram_protocol_module_t *, internet_protocol_context_t *, user_datagram_protocol_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(user_datagram_protocol_module_t *, FILE *, user_datagram_protocol_context_t *);
    int32_t (*in)(user_datagram_protocol_module_t *, protocol_packet_t *, uint64_t, internet_protocol_context_t *, user_datagram_protocol_context_t **);
    int32_t (*out)(user_datagram_protocol_module_t *, protocol_path_node_t *, protocol_context_t *);
    user_datagram_protocol_context_t * (*context_gen)(user_datagram_protocol_module_t *, protocol_path_node_t *, protocol_context_t *);
    user_datagram_protocol_context_t * (*reply_gen)(user_datagram_protocol_module_t *, user_datagram_protocol_context_t *);
};

extern user_datagram_protocol_module_t * user_datagram_protocol_module_gen(protocol_module_map_t * map, user_datagram_protocol_context_handler_t on);
extern int32_t user_datagram_protocol_module_func_on(user_datagram_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, user_datagram_protocol_context_t * context);

#define user_datagram_protocol_module_addrlen_get(module)                                               ((module)->addrlen)
#define user_datagram_protocol_module_number_get(module)                                                ((module)->type)

#define user_datagram_protocol_module_rem(module)                                                       ((module)->func->rem(module))
#define user_datagram_protocol_module_deserialize(module, packet, packetlen, parent, context)           ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define user_datagram_protocol_module_serialize(module, parent, context, packet, len)                   ((module)->func->serialize(module, parent, context, packet, len))
#define user_datagram_protocol_module_debug(module, stream, context)                                    ((module)->func->debug(module, stream, context))
#define user_datagram_protocol_module_in(module, packet, packetlen, parent, context)                    ((module)->func->in(module, packet, packetlen, parent, context))
#define user_datagram_protocol_module_out(module, node, child)                                          ((module)->func->out(module, node, child))
#define user_datagram_protocol_module_context_gen(module, node, child)                                  ((module)->func->context_gen(module, node, child))
#define user_datagram_protocol_module_reply_gen(module, request)                                        ((module)->func->reply_gen(module, request))

#define user_datagram_protocol_module_on(module, type, parent, context)                                 ((module)->on(module, type, parent, context))

struct user_datagram_protocol_context {
    user_datagram_protocol_context_func_t * func;
    sync_t * sync;
    user_datagram_protocol_module_t * module;
    internet_protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    user_datagram_protocol_packet_t * packet;
    uint64_t packetlen;
    uint64_t * bufferlen;

    uint16_t source;
    uint16_t destination;
    uint16_t length;
    uint16_t checksum;
};

struct user_datagram_protocol_context_func {
    user_datagram_protocol_context_t * (*rem)(user_datagram_protocol_context_t *);
    int32_t (*valid)(user_datagram_protocol_context_t *);
    uint8_t * (*addrptr)(user_datagram_protocol_context_t *, uint32_t);
    void (*checksum_build)(user_datagram_protocol_context_t *, const uint8_t *, uint64_t);
};

extern user_datagram_protocol_context_t * user_datagram_protocol_context_gen(user_datagram_protocol_module_t * module, internet_protocol_context_t * parent, user_datagram_protocol_packet_t * packet, uint64_t packetlen, uint64_t * bufferlen);

#define user_datagram_protocol_context_buffer_reserve(context, n)                       ((context)->func->buffer_reserve(context, n))

#define user_datagram_protocol_context_rem(context)                                     ((context)->func->rem(context))
#define user_datagram_protocol_context_valid(context)                                   ((context)->func->valid(context))
#define user_datagram_protocol_context_addrptr(context, type)                           ((context)->func->addrptr(context, type))
#define user_datagram_protocol_context_checksum_build(context, pseudo, pseudolen)       ((context)->func->checksum_build(context, pseudo, pseudolen))

#define user_datagram_protocol_context_error_get(context)                               ((context)->error)
#define user_datagram_protocol_context_error_set(context, v)                            ((context)->error = v)
#define user_datagram_protocol_context_source_get(context)                              ((context)->source)
#define user_datagram_protocol_context_source_set(context, v)                           ((context)->source = v)
#define user_datagram_protocol_context_destination_get(context)                         ((context)->destination)
#define user_datagram_protocol_context_destination_set(context, v)                      ((context)->destination = v)
#define user_datagram_protocol_context_length_get(context)                              ((context)->length)
#define user_datagram_protocol_context_length_set(context, v)                           ((context)->length = v)
#define user_datagram_protocol_context_checksum_get(context)                            ((context)->checksum)
#define user_datagram_protocol_context_checksum_set(context, v)                         ((context)->checksum = v)

#endif // __SNORLAX__PROTOCOL_USER_DATAGRAM__H__
