/**
 * @file        snorlax/vpn/protocol.h
 * @brief       Virtual Private Network <sup>VPN</sup>
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_PROTOCOL__H__
#define   __SNORLAX__VPN_PROTOCOL__H__

#include <snorlax/protocol.h>

struct virtual_private_network_protocol_packet;

struct virtual_private_network_protocol_module;
struct virtual_private_network_protocol_module_func;
struct virtual_private_network_protocol_context;
struct virtual_private_network_protocol_context_func;

typedef struct virtual_private_network_protocol_packet virtual_private_network_protocol_packet_t;

typedef struct virtual_private_network_protocol_module virtual_private_network_protocol_module_t;
typedef struct virtual_private_network_protocol_module_func virtual_private_network_protocol_module_func_t;
typedef struct virtual_private_network_protocol_context virtual_private_network_protocol_context_t;
typedef struct virtual_private_network_protocol_context_func virtual_private_network_protocol_context_func_t;

typedef int32_t (*virtual_private_network_protocol_context_handler_t)(virtual_private_network_protocol_module_t *, uint32_t, protocol_context_t *, virtual_private_network_protocol_context_t *);

struct virtual_private_network_protocol_packet {
    uint16_t length;
    uint16_t type;
};

struct virtual_private_network_protocol_module {
    virtual_private_network_protocol_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;
    virtual_private_network_protocol_context_handler_t on;
};

struct virtual_private_network_protocol_module_func {
    virtual_private_network_protocol_module_t * (*rem)(virtual_private_network_protocol_module_t *);
    int32_t (*deserialize)(virtual_private_network_protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, virtual_private_network_protocol_context_t **);
    int32_t (*serialize)(virtual_private_network_protocol_module_t *, protocol_context_t *, virtual_private_network_protocol_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(virtual_private_network_protocol_module_t *, FILE *, virtual_private_network_protocol_context_t *);
    int32_t (*in)(virtual_private_network_protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, virtual_private_network_protocol_context_t **);
//    int32_t (*out)(protocol_module_t *, protocol_context_t *, protocol_context_t *, protocol_packet_t **, uint64_t *);
};

extern virtual_private_network_protocol_module_t * virtual_private_network_protocol_module_gen(protocol_module_map_t * map, virtual_private_network_protocol_context_handler_t on);

#define virtual_private_network_protocol_module_rem(module)                                                     ((module)->func->rem(module))
#define virtual_private_network_protocol_module_deserialize(module, packet, packetlen, parent, context)         ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define virtual_private_network_protocol_module_serialize(module, parent, context, packet, packetlen)           ((module)->func->serialize(module, parent, context, packet, packetlen))
#define virtual_private_network_protocol_module_debug(module, stream, context)                                  ((module)->func->debug(module, stream, context))
#define virtual_private_network_protocol_module_in(module, packet, packetlen, parent, context)                  ((module)->func->in(module, packet, packetlen, parent, context))

#define virtual_private_network_protocol_module_on(module, type, parent, context)                               ((module)->on(module, type, parent, context))

struct virtual_private_network_protocol_context {
    virtual_private_network_protocol_context_func_t * func;
    sync_t * sync;
    virtual_private_network_protocol_module_t * module;
    protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    virtual_private_network_protocol_packet_t * packet;
    uint64_t packetlen;
};

struct virtual_private_network_protocol_context_func {
    virtual_private_network_protocol_context_t * (*rem)(virtual_private_network_protocol_context_t *);
    int32_t (*valid)(virtual_private_network_protocol_context_t *);
};

extern virtual_private_network_protocol_context_t * virtual_private_network_protocol_context_gen(protocol_context_t * parent, virtual_private_network_protocol_packet_t * packet, uint64_t packetlen);

#define virtual_private_network_protocol_context_rem(context)           ((context)->func->rem(context))
#define virtual_private_network_protocol_context_valid(context)         ((context)->func->valid(context))

#define virtual_private_network_protocol_context_error_get(context)     ((context)->error)
#define virtual_private_network_protocol_context_error_set(context, v)  ((context)->error = v)
#define virtual_private_network_protocol_context_length_get(context)    ((context)->packetlen)
#define virtual_private_network_protocol_context_length_set(context, v) ((context)->packetlen = v)

#endif // __SNORLAX__VPN_PROTOCOL__H__
