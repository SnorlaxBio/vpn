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

#define protocol_event_complete_in          4

#define protocol_packet_max                 65536

#define protocol_address_type_none          0
#define protocol_address_type_source        1
#define protocol_address_type_destination   2

struct protocol_module;
struct protocol_module_func;
struct protocol_context;
struct protocol_context_func;
struct protocol_module_map;
struct protocol_module_map_func;
struct protocol_context_array;
struct protocol_context_array_func;

struct protocol_path;
struct protocol_path_func;
struct protocol_path_node;

typedef uint8_t protocol_packet_t;
typedef uint8_t protocol_address_t;

typedef struct protocol_module              protocol_module_t;
typedef struct protocol_module_func         protocol_module_func_t;
typedef struct protocol_context             protocol_context_t;
typedef struct protocol_context_func        protocol_context_func_t;
typedef struct protocol_module_map          protocol_module_map_t;
typedef struct protocol_module_map_func     protocol_module_map_func_t;
typedef struct protocol_context_array       protocol_context_array_t;
typedef struct protocol_context_array_func  protocol_context_array_func_t;
typedef struct protocol_path                protocol_path_t;
typedef struct protocol_path_func           protocol_path_func_t;
typedef struct protocol_path_node           protocol_path_node_t;

typedef protocol_module_t * (*protocol_module_map_get_t)(protocol_module_map_t *, uint64_t);

typedef int32_t (*protocol_context_handler_t)(protocol_module_t *, uint32_t, protocol_context_t *, protocol_context_t *);

extern char * protocol_address_to_hexadecimalstr(char * s, const protocol_address_t * addr, uint16_t len);

struct protocol_module {
    protocol_module_func_t * func;
    sync_t * sync;
    uint16_t type;
    uint16_t addrlen;
    ___reference protocol_module_map_t * map;
    protocol_context_handler_t on;
};

struct protocol_module_func {
    protocol_module_t * (*rem)(protocol_module_t *);
    int32_t (*deserialize)(protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, protocol_context_t **);
    int32_t (*serialize)(protocol_module_t *, protocol_context_t *, protocol_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(protocol_module_t *, FILE *, protocol_context_t *);
    int32_t (*in)(protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, protocol_context_t **);
    int32_t (*out)(protocol_module_t *, protocol_context_t *, protocol_path_node_t *);
    protocol_context_t * (*context_gen)(protocol_module_t *, protocol_context_t *);
};

extern int32_t protocol_module_func_serialize(protocol_module_t * module, protocol_context_t * parent, protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
extern int32_t protocol_module_func_out(protocol_module_t * module, protocol_context_t * context, protocol_path_node_t * node);

extern int32_t protocol_module_func_on(protocol_module_t * module, uint32_t type, protocol_context_t * parent, protocol_context_t * context);

#define protocol_module_addrlen_get(module)                                             ((module)->addrlen)

#define protocol_module_rem(module)                                                     ((module)->func->rem(module))
#define protocol_module_deserialize(module, packet, packetlen, parent, context)         ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define protocol_module_serialize(module, parent, context, packet, len)                 ((module)->func->serialize(module, parent, context, packet, len))
#define protocol_module_debug(module, stream, context)                                  ((module)->func->debug(module, stream, context))
#define protocol_module_in(module, packet, packetlen, parent, context)                  ((module)->func->in(module, packet, packetlen, parent, context))
#define protocol_module_out(module, context, node)                                      ((module)->func->out(module, context, node))
#define protocol_module_context_gen(module, child)                                      ((module)->func->context_gen(module, child))

#define protocol_module_on(module, type, parent, context)                               ((module)->on(module, type, parent, context))

struct protocol_context {
    protocol_context_func_t * func;
    sync_t * sync;
    ___reference protocol_module_t * module;
    ___reference protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    ___reference protocol_packet_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
};

struct protocol_context_func {
    protocol_context_t * (*rem)(protocol_context_t *);
    int32_t (*valid)(protocol_context_t *);
    uint8_t * (*addrptr)(protocol_context_t *, uint32_t);
};

extern uint8_t * protocol_context_func_addrptr(protocol_context_t * context, uint32_t type);

#define protocol_context_rem(context)                                                   ((context)->func->rem(context))
#define protocol_context_valid(context)                                                 ((context)->func->valid(context))
#define protocol_context_addrptr(context, type)                                         ((context)->func->addrptr(context, type))

#define protocol_context_type_get(context)                                              ((context)->module->type)

#define protocol_context_error_get(context)                                             ((context)->error)
#define protocol_context_error_set(context, v)                                          ((context)->error = v)
#define protocol_context_source_node_get(context)                                       ((context)->source)
#define protocol_context_source_node_set(context, v)                                    ((context)->source = v)
#define protocol_context_destination_node_get(context)                                  ((context)->destination)
#define protocol_context_destination_node_set(context, v)                               ((context)->destination = v)

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

struct protocol_path_node {
    ___reference protocol_path_t * path;
    ___reference protocol_module_t * module;
    uint32_t length;
};

#define protocol_path_node_next(node)                               ((protocol_path_node_t *) (&((uint8_t *) (node))[sizeof(protocol_path_node_t) + ((node)->length * 2)]))
#define protocol_path_node_source_get(node)                         ((uint8_t *) (&((uint8_t *) (node))[sizeof(protocol_path_node_t)]))
#define protocol_path_node_destination_get(node)                    ((uint8_t *) (&((uint8_t *) (node))[sizeof(protocol_path_node_t) + (node)->length]))



struct protocol_path {
    protocol_path_func_t * func;
    sync_t * sync;
    uint64_t size;
    protocol_path_node_t * node;
    ___reference protocol_path_node_t * end;
};

struct protocol_path_func {
    protocol_path_t * (*rem)(protocol_path_t *);
    void (*debug)(protocol_path_t *, FILE * stream);
    protocol_path_node_t * (*add)(protocol_path_t *, protocol_path_node_t *, protocol_context_t *);
};

extern protocol_path_t * protocol_path_gen(protocol_context_t * original, uint64_t hint);

#define protocol_path_rem(path)                             ((path)->func->rem(path))
#define protocol_path_add(path, node, context)              ((path)->func->add(path, node, context))
#define protocol_path_debug(path, stream)                   ((path)->func->debug(path, stream))

#define protocol_path_begin(path)                           ((path)->node)
#define protocol_path_end(path)                             ((path)->end)

#endif // __SNORLAX__PROTOCOL__H__
