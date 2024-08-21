/**
 * @file        snorlax/protocol/internet.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 29, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET__H__
#define   __SNORLAX__PROTOCOL_INTERNET__H__

#include <snorlax.h>
#include <snorlax/hash.h>
#include <snorlax/protocol.h>

/**
 * @see     [Protocol Numbers](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml)
 */
// REFACTOR PROTOCOL_NO_INTERNET_VERSION6_EXTENSION_HOPBYHOP_NO
#define internet_protocol_version6_extension_hopbyhop_no        0
#define internet_control_message_protocol_version4_no           1
#define transmission_control_protocol_no                        6
#define user_datagram_protocol_no                               17
#define internet_protocol_version6_extension_routing_no         43
#define internet_protocol_version6_extension_fragment_no        44
#define internet_protocol_version6_extension_destination_no     60
#define internet_control_message_protocol_version6_no           58
#define internet_protocol_version6_extension_no_next_header     59

#if       __BYTE_ORDER == __LITTLE_ENDIAN
#define internet_protocol_version_get(datagram)     (datagram[0] >> 4)
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
#define internet_protocol_version_get(datagram)     (datagram[0] & 0x0Fu)
#endif // __BYTE_ORDER == __LITTLE_ENDIAN

#define internet_protocol_version_hash                          default_hash

#define internet_protocol_direction_none                        0
#define internet_protocol_direction_in                          1
#define internet_protocol_direction_out                         2
#define internet_protocol_direction_internal                    3


struct internet_protocol_module;
struct internet_protocol_module_func;
struct internet_protocol_context;
struct internet_protocol_context_func;

struct internet_protocol_version4_module;
struct internet_protocol_version6_module;

typedef uint8_t internet_protocol_packet_t;
typedef uint8_t internet_protocol_pseudo_t;
typedef uint8_t internet_protocol_address_t;

typedef struct internet_protocol_module internet_protocol_module_t;
typedef struct internet_protocol_module_func internet_protocol_module_func_t;
typedef struct internet_protocol_context internet_protocol_context_t;
typedef struct internet_protocol_context_func internet_protocol_context_func_t;

typedef struct internet_protocol_version4_module internet_protocol_version4_module_t;
typedef struct internet_protocol_version6_module internet_protocol_version6_module_t;

typedef int32_t (*internet_protocol_context_handler_t)(internet_protocol_module_t *, uint32_t, protocol_context_t *, internet_protocol_context_t *);

extern uint32_t internet_protocol_checksum_sum(protocol_packet_t * packet, uint64_t packetlen);
extern const char * internet_protocol_address_to_string(uint8_t version, char * s, const uint8_t * addr);

extern internet_protocol_packet_t * internet_protocol_packet_build(internet_protocol_packet_t * datagram, uint64_t n, uint8_t version, const internet_protocol_address_t * source, const internet_protocol_address_t * destination);

struct internet_protocol_module {
    internet_protocol_module_func_t * func;
    sync_t * sync;
    uint16_t type;
    uint16_t addrlen;
    ___reference protocol_module_map_t * map;
    internet_protocol_context_handler_t on;
    
    ___reference uint8_t * addr;

    // NO INHERIED
    internet_protocol_version4_module_t * version4;
    internet_protocol_version6_module_t * version6;
};

struct internet_protocol_module_func {
    internet_protocol_module_t * (*rem)(internet_protocol_module_t *);
    int32_t (*deserialize)(internet_protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_context_t **);
    int32_t (*serialize)(internet_protocol_module_t *, protocol_context_t *, internet_protocol_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_module_t *, FILE *, internet_protocol_context_t *);
    int32_t (*in)(internet_protocol_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_context_t **);
    int32_t (*out)(internet_protocol_module_t *, internet_protocol_context_t *, protocol_path_node_t *);
    protocol_context_t * (*context_gen)(internet_protocol_module_t *, protocol_context_t *);
};

extern internet_protocol_module_t * internet_protocol_module_gen(protocol_module_map_t * map, internet_protocol_context_handler_t on, internet_protocol_version4_module_t * version4, internet_protocol_version6_module_t * version6);
extern int32_t internet_protocol_module_func_on(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);
extern int32_t internet_protocol_module_func_out(internet_protocol_module_t * module, internet_protocol_context_t * context, protocol_path_node_t * node);
extern protocol_context_t * internet_protocol_module_func_context_gen(internet_protocol_module_t * module, protocol_context_t * child);

#define internet_protocol_module_rem(module)                                                    ((module)->func->rem(module))
#define internet_protocol_module_deserialize(module, packet, packetlen, parent, context)        ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_module_serialize(module, parent, context, packet, len)                ((module)->func->serialize(module, parent, context, packet, len))
#define internet_protocol_module_debug(module, stream, context)                                 ((module)->func->debug(module, stream, context))
#define internet_protocol_module_in(module, packet, packetlen, parent, context)                 ((module)->func->in(module, packet, packetlen, parent, context))
#define internet_protocol_module_out(module, context, node)                                     ((module)->func->out(module, context, node))
#define internet_protocol_module_context_gen(module, child)                                     ((module)->func->context_gen(module, child))

#define internet_protocol_module_on(module, type, parent, context)                              ((module)->on(module, type, parent, context))

struct internet_protocol_context {
    internet_protocol_context_func_t * func;
    sync_t * sync;
    ___reference internet_protocol_module_t * module;
    ___reference protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    ___reference internet_protocol_packet_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;

    internet_protocol_pseudo_t * pseudo;
    uint64_t pseudolen;
};

struct internet_protocol_context_func {
    internet_protocol_context_t * (*rem)(internet_protocol_context_t *);
    int32_t (*valid)(internet_protocol_context_t *);
    uint8_t * (*addrptr)(internet_protocol_context_t *, uint32_t);
};

extern internet_protocol_context_t * internet_protocol_context_gen(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_packet_t * packet, uint64_t packetlen);
extern uint8_t * internet_protocol_context_source_get(internet_protocol_context_t * context);
extern uint8_t * internet_protocol_context_destination_get(internet_protocol_context_t * context);

#define internet_protocol_context_rem(context)                  ((context)->func->rem(context))
#define internet_protocol_context_valid(context)                ((context)->func->valid(context))
#define internet_protocol_context_addrptr(context, type)        ((context)->func->addrptr(context, type))

#define internet_protocol_context_error_get(context)            ((context)->error)
#define internet_protocol_context_error_set(context, v)         ((context)->error = v)
#define internet_protocol_context_pseudo_get(context)           ((context)->pseudo)
#define internet_protocol_context_pseudolen_get(context)        ((context)->pseudolen)
#define internet_protocol_context_pseudo_set(context, v, len)   (((context)->pseudolen = len), ((context)->pseudo = v))
#define internet_protocol_context_packetlen_get(context)        ((context)->packetlen)

#define internet_protocol_context_version_get(context)          (internet_protocol_version_get((context)->packet))

#endif // __SNORLAX__PROTOCOL_INTERNET__H__
