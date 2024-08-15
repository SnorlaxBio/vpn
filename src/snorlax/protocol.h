/**
 * @file        snorlax/protocol.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 6, 2024
 */

#ifndef   __SNORLAX__PROTOCOL__H__
#define   __SNORLAX__PROTOCOL__H__

#include <snorlax.h>

#define protocol_event_in                   1
#define protocol_event_out                  2
#define protocol_event_exception            3

struct protocol_module;
struct protocol_module_func;
struct protocol_context;
struct protocol_context_func;
struct protocol_module_map;
struct protocol_module_map_func;
struct protocol_context_array;
struct protocol_context_array_func;

typedef uint8_t protocol_packet_t;
typedef uint16_t protocol_address_t;            // REFACTOR

typedef struct protocol_module protocol_module_t;
typedef struct protocol_module_func protocol_module_func_t;
typedef struct protocol_context protocol_context_t;
typedef struct protocol_context_func protocol_context_func_t;
typedef struct protocol_module_map protocol_module_map_t;
typedef struct protocol_module_map_func protocol_module_map_func_t;
typedef struct protocol_context_array protocol_context_array_t;
typedef struct protocol_context_array_func protocol_context_array_func_t;

typedef protocol_module_t * (*protocol_module_map_get_t)(protocol_module_map_t *, uint64_t);

typedef int32_t (*protocol_context_handler_t)(protocol_module_t *, uint32_t, protocol_context_t *, protocol_context_t *);

struct protocol_module {
    protocol_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;
    protocol_context_handler_t on;
};

struct protocol_module_func {
    protocol_module_t * (*rem)(protocol_module_t *);
    int32_t (*deserialize)(protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, protocol_context_t **);
    int32_t (*serialize)(protocol_module_t *, protocol_context_t *, protocol_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(protocol_module_t *, FILE *, protocol_context_t *);
    int32_t (*in)(protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, protocol_context_t *);
//    int32_t (*out)(protocol_module_t *, protocol_context_t *, protocol_context_t *, protocol_packet_t **, uint64_t *);
};

extern int32_t protocol_module_func_on(protocol_module_t * module, uint32_t type, protocol_context_t * parent, protocol_context_t * context);

#define protocol_module_rem(module)                                                     ((module)->func->rem(module))
#define protocol_module_deserialize(module, packet, packetlen, parent, context)         ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define protocol_module_serialize(module, parent, context, packet, len)                 ((module)->func->serialize(module, parent, context, packet, len))
#define protocol_module_debug(module, stream, context)                                  ((module)->func->debug(module, stream, context))
#define protocol_module_in(module, packet, packetlen, parent, context)                  ((module)->func->in(module, packet, packetlen, parent, context))

#define protocol_module_on(module, type, parent, context)                               ((module)->on(module, type, parent, context))

struct protocol_context {
    protocol_context_func_t * func;
    sync_t * sync;
    protocol_module_t * module;
    protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    uint8_t * packet;
    uint64_t packetlen;
};

struct protocol_context_func {
    protocol_context_t * (*rem)(protocol_context_t *);
    int32_t (*valid)(protocol_context_t *);
};

#define protocol_context_rem(context)                                                   ((context)->func->rem(context))
#define protocol_context_valid(context)                                                 ((context)->func->valid(context))

#define protocol_context_error_get(context)                                             ((context)->error)
#define protocol_context_error_set(context, v)                                          ((context)->error = v)

struct protocol_module_map {
    protocol_module_map_func_t * func;
    sync_t * sync;
    uint64_t size;
    protocol_module_t ** modules;
    protocol_module_map_get_t get;
};

struct protocol_module_map_func {
    protocol_module_map_t * (*rem)(protocol_module_map_t *);
};

extern protocol_module_map_t * protocol_module_map_gen(protocol_module_t ** modules, uint64_t n, protocol_module_map_get_t get);

#define protocol_module_map_rem(map)                    ((map) ? (map)->func->rem(map) : nil)
#define protocol_module_map_get(map, no)                ((map) ? (map)->get(map, no) : nil)

// #define protocol_module_map_modules_get(map)            ((map) ? (map)->modules : nil)
// #define protocol_module_map_size_get(map)               ((map) ? (map)->size : 0)
// #define protocol_module_map_index_get(map)              ((map) ? (map)->index : nil)

struct protocol_context_array {
    protocol_context_array_func_t * func;
    sync_t * sync;
    uint64_t size;
    uint8_t capacity;
    protocol_context_t ** container;
};

struct protocol_context_array_func {
    protocol_context_array_t * (*rem)(protocol_context_array_t *);
    protocol_context_t * (*get)(protocol_context_array_t *, uint64_t);
    protocol_context_t ** (*pop)(protocol_context_array_t *);
};

extern protocol_context_array_t * protocol_context_array_gen(void);

#define protocol_context_array_rem(collection)                      ((collection)->func->rem(collection))
#define protocol_context_array_get(collection, index)               ((collection)->func->get(collection, index))
#define protocol_context_array_pop(collection)                      ((collection)->func->pop(collection))

#endif // __SNORLAX__PROTOCOL__H__
