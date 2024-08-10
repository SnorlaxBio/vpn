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
#include <snorlax/protocol.h>

/**
 * @see     [Protocol Numbers](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml)
 */
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

struct internet_protocol_module;
struct internet_protocol_module_func;
struct internet_protocol_context;
struct internet_protocol_context_func;

struct internet_protocol_address;

typedef uint8_t internet_protocol_packet_t;
typedef uint8_t internet_protocol_pseudo_t;
typedef struct internet_protocol_address internet_protocol_address_t;

typedef struct internet_protocol_module internet_protocol_module_t;
typedef struct internet_protocol_module_func internet_protocol_module_func_t;
typedef struct internet_protocol_context internet_protocol_context_t;
typedef struct internet_protocol_context_func internet_protocol_context_func_t;

struct internet_protocol_module {
    internet_protocol_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;
    protocol_module_t * version4;
    protocol_module_t * version6;
};

struct internet_protocol_module_func {
    internet_protocol_module_t * (*rem)(internet_protocol_module_t *);
    int32_t (*deserialize)(internet_protocol_module_t *, protocol_packet_t *, uint32_t, protocol_context_t *, internet_protocol_context_t **);
    int32_t (*serialize)(internet_protocol_module_t *, protocol_context_t *, internet_protocol_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(internet_protocol_module_t *, FILE *, internet_protocol_context_t *);
};

extern internet_protocol_module_t * internet_protocol_module_gen(protocol_module_map_t * map);

#define internet_protocol_module_rem(module)                                                    ((module)->func->rem(module))
#define internet_protocol_module_deserialize(module, packet, packetlen, parent, context)        ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_module_serialize(module, parent, context, packet, len)                ((module)->func->serialize(module, parent, context, packet, len))
#define internet_protocol_module_debug(module, stream, context)                                 ((module)->func->debug(module, stream, context))

struct internet_protocol_context {
    internet_protocol_context_func_t * func;
    sync_t * sync;
    internet_protocol_module_t * module;
    protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_protocol_packet_t * packet;
    uint64_t packetlen;
    internet_protocol_pseudo_t * pseudo;
    uint64_t pseudolen;
};

struct internet_protocol_context_func {
    internet_protocol_context_t * (*rem)(internet_protocol_context_t *);
};

extern internet_protocol_context_t * internet_protocol_context_gen(protocol_context_t * parent, internet_protocol_packet_t * packet, uint64_t packetlen);

#define internet_protocol_context_rem(context)                  ((context)->func->rem(context))

#define internet_protocol_context_error_get(context)            ((context)->error)
#define internet_protocol_context_error_set(context, v)         ((context)->error = v)
#define internet_protocol_context_pseudo_get(context)           ((context)->pseudo)
#define internet_protocol_context_pseudolen_get(context)        ((context)->pseudolen)
#define internet_protocol_context_pseudo_set(context, v, len)   (((context)->pseudolen = len), ((context)->pseudo = v))
#define internet_protocol_context_packetlen_get(context)        ((context)->packetlen)

struct internet_protocol_address {
    protocol_address_t type;
    union {
        uint8_t version4[4];
        uint8_t version6[16];
    } value;
};

#endif // __SNORLAX__PROTOCOL_INTERNET__H__
