/**
 * @file        snorlax/protocol/module.h
 */

#ifndef   __SNORLAX__PROTOCOL_MODULE__H__
#define   __SNORLAX__PROTOCOL_MODULE__H__

#include <snorlax.h>

struct protocol_module;
struct protocol_module_func;
struct protocol_module_map;
struct protocol_context;

typedef struct protocol_module protocol_module_t;
typedef struct protocol_module_func protocol_module_func_t;
typedef struct protocol_module_map protocol_module_map_t;
typedef struct protocol_context protocol_context_t;
typedef uint8_t protocol_packet_t;

struct protocol_module {
    protocol_module_func_t * func;
    sync_t * sync;
    protocol_module_t * parent;
    protocol_module_map_t * map;
};

struct protocol_module_func {
    protocol_module_t * (*rem)(protocol_module_t *);
    int32_t (*deserialize)(protocol_module_t *, protocol_packet_t *, uint32_t, protocol_context_t *, protocol_context_t **);
    int32_t (*serialize)(protocol_module_t *, protocol_context_t *, protocol_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(protocol_module_t *, FILE *, protocol_context_t *);
};

#define protocol_module_rem(module)     ((module)->func->rem(module))
#define protocol_module_deserialize(module, packet, packetlen, parent, context)         ((module)->func->deserialize(module, packet, packetlen, parent, context))

#endif // __SNORLAX__PROTOCOL_MODULE__H__
