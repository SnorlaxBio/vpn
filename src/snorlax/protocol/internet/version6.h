/**
 * @file        snorlax/protocol/internet/version6.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 29, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_VERSION6__H__
#define   __SNORLAX__PROTOCOL_INTERNET_VERSION6__H__

#include <snorlax.h>
#include <snorlax/hashtable.h>
#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

#define internet_protocol_version6_maximum_transmission_unit_size_default                   1500
#define internet_protocol_version6_current_hop_limit_default                                64
#define internet_protocol_version6_reachable_time_default                                   30000
#define internet_protocol_version6_random_factor_min                                        (0.5f)
#define internet_protocol_version6_random_factor_max                                        (1.5f)
#define internet_protocol_version6_retransmission_timer                                     1000

struct internet_protocol_version6_packet;
struct internet_protocol_version6_pseudo;

struct internet_protocol_version6_extension;
struct internet_protocol_version6_extension_hopbyhop;
struct internet_protocol_version6_extension_routing;
struct internet_protocol_version6_extension_fragment;
struct internet_protocol_version6_extension_destination;

struct internet_protocol_version6_module;
struct internet_protocol_version6_module_host;
struct internet_protocol_version6_module_host_func;
struct internet_protocol_version6_module_router;
struct internet_protocol_version6_module_router_func;
struct internet_protocol_version6_module_func;
struct internet_protocol_version6_context;
struct internet_protocol_version6_context_func;
struct internet_protocol_version6_extension_module;
struct internet_protocol_version6_extension_module_func;
struct internet_protocol_version6_extension_context;
struct internet_protocol_version6_extension_context_func;
struct internet_protocol_version6_extension_hopbyhop_module;
struct internet_protocol_version6_extension_hopbyhop_module_func;
struct internet_protocol_version6_extension_hopbyhop_context;
struct internet_protocol_version6_extension_hopbyhop_context_func;
struct internet_protocol_version6_extension_routing_module;
struct internet_protocol_version6_extension_routing_module_func;
struct internet_protocol_version6_extension_routing_context;
struct internet_protocol_version6_extension_routing_context_func;
struct internet_protocol_version6_extension_fragment_module;
struct internet_protocol_version6_extension_fragment_module_func;
struct internet_protocol_version6_extension_fragment_context;
struct internet_protocol_version6_extension_fragment_context_func;
struct internet_protocol_version6_extension_destination_module;
struct internet_protocol_version6_extension_destination_module_func;
struct internet_protocol_version6_extension_destination_context;
struct internet_protocol_version6_extension_destination_context_func;

struct internet_control_message_protocol_version6_context;

typedef struct internet_protocol_version6_packet internet_protocol_version6_packet_t;
typedef struct internet_protocol_version6_pseudo internet_protocol_version6_pseudo_t;

typedef uint8_t internet_protocol_version6_address_t;
typedef uint8_t internet_protocol_version6_option_t;
typedef uint8_t internet_protocol_version6_routing_data_t;
typedef uint8_t internet_protocol_version6_segment_t;

typedef struct internet_protocol_version6_extension internet_protocol_version6_extension_t;
typedef struct internet_protocol_version6_extension_hopbyhop internet_protocol_version6_extension_hopbyhop_t;
typedef struct internet_protocol_version6_extension_routing internet_protocol_version6_extension_routing_t;
typedef struct internet_protocol_version6_extension_fragment internet_protocol_version6_extension_fragment_t;
typedef struct internet_protocol_version6_extension_destination internet_protocol_version6_extension_destination_t;

typedef struct internet_protocol_version6_module internet_protocol_version6_module_t;
typedef struct internet_protocol_version6_module_func internet_protocol_version6_module_func_t;

typedef struct internet_protocol_version6_module_host internet_protocol_version6_module_host_t;
typedef struct internet_protocol_version6_module_host_func internet_protocol_version6_module_host_func_t;
typedef struct internet_protocol_version6_module_router internet_protocol_version6_module_router_t;
typedef struct internet_protocol_version6_module_router_func internet_protocol_version6_module_router_func_t;

typedef struct internet_protocol_version6_context internet_protocol_version6_context_t;
typedef struct internet_protocol_version6_context_func internet_protocol_version6_context_func_t;
typedef struct internet_protocol_version6_extension_module internet_protocol_version6_extension_module_t;
typedef struct internet_protocol_version6_extension_module_func internet_protocol_version6_extension_module_func_t;
typedef struct internet_protocol_version6_extension_context internet_protocol_version6_extension_context_t;
typedef struct internet_protocol_version6_extension_context_func internet_protocol_version6_extension_context_func_t;

typedef struct internet_protocol_version6_extension_hopbyhop_module internet_protocol_version6_extension_hopbyhop_module_t;
typedef struct internet_protocol_version6_extension_hopbyhop_module_func internet_protocol_version6_extension_hopbyhop_module_func_t;
typedef struct internet_protocol_version6_extension_hopbyhop_context internet_protocol_version6_extension_hopbyhop_context_t;
typedef struct internet_protocol_version6_extension_hopbyhop_context_func internet_protocol_version6_extension_hopbyhop_context_func_t;

typedef struct internet_protocol_version6_extension_routing_module internet_protocol_version6_extension_routing_module_t;
typedef struct internet_protocol_version6_extension_routing_module_func internet_protocol_version6_extension_routing_module_func_t;
typedef struct internet_protocol_version6_extension_routing_context internet_protocol_version6_extension_routing_context_t;
typedef struct internet_protocol_version6_extension_routing_context_func internet_protocol_version6_extension_routing_context_func_t;

typedef struct internet_protocol_version6_extension_fragment_module internet_protocol_version6_extension_fragment_module_t;
typedef struct internet_protocol_version6_extension_fragment_module_func internet_protocol_version6_extension_fragment_module_func_t;
typedef struct internet_protocol_version6_extension_fragment_context internet_protocol_version6_extension_fragment_context_t;
typedef struct internet_protocol_version6_extension_fragment_context_func internet_protocol_version6_extension_fragment_context_func_t;

typedef struct internet_protocol_version6_extension_destination_module internet_protocol_version6_extension_destination_module_t;
typedef struct internet_protocol_version6_extension_destination_module_func internet_protocol_version6_extension_destination_module_func_t;
typedef struct internet_protocol_version6_extension_destination_context internet_protocol_version6_extension_destination_context_t;
typedef struct internet_protocol_version6_extension_destination_context_func internet_protocol_version6_extension_destination_context_func_t;

typedef struct internet_control_message_protocol_version6_context internet_control_message_protocol_version6_context_t;

extern const char * internet_protocol_version6_addr_to_str(char * destination, uint8_t * addr);
extern int32_t internet_protocol_version6_extension_check(uint32_t no);

struct internet_protocol_version6_packet {
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint32_t prefix;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t version:4;
    uint8_t traffic;
    uint32_t label:20;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint16_t payload;
    uint8_t next;
    uint8_t limit;
    uint8_t source[16];
    uint8_t destination[16];
};

struct internet_protocol_version6_pseudo {
    uint8_t source[16];
    uint8_t destination[16];
    uint32_t length;
    uint32_t zero:24;
    uint8_t next;
};

extern internet_protocol_version6_pseudo_t * internet_protocol_version6_pseudo_gen(internet_protocol_version6_packet_t * datagram, uint8_t next, uint64_t len);

#define internet_protocol_version6_packet_header_length_min                                 (40)

#define internet_protocol_version6_extension_no_next_protocol_no                            (59)

#define internet_protocol_version6_version_get(packet)                                      ((uint8_t) (0x0000000Fu & (packet)->prefix))
#define internet_protocol_version6_traffic_class_get(packet)                                ((uint8_t) (((0x00000F00u & (packet)->prefix) >> 8u) | (0x000000F0u & (packet)->prefix)))
#define internet_protocol_version6_flow_label_get(packet)                                   (ntohl(0xFFFFF000u & (packet)->prefix))

#define internet_protocol_version6_option_type_get(option)                                  (*(option))
#define internet_protocol_version6_option_length_get(option)                                (*(option) != 0 ? (option)[1] : 1)
#define internet_protocol_version6_option_data_get(option)                                  (*(option) != 0 ? &(option)[2] : nil)
#define internet_protocol_version6_option_next(option)                                      (*(option) == 0 ? &(option)[1] : &(option)[(option)[1]])

#define internet_protocol_version6_option_exception_handling_type_get(option)               (*(option) & 0xC0u)
#define internet_protocol_version6_option_changable_get(option)                             (*(option) & 0x20u)

struct internet_protocol_version6_extension {
    uint8_t next;
    uint8_t length;
};

#define internet_protocol_version6_extension_length_min                                     (8)

#define internet_protocol_version6_extension_hopbyhop_protocol_no                           (0)

#define internet_protocol_version6_extension_hopbyhop_total_get(extension)                  (((extension)->length + 1) * 8)
#define internet_protocol_version6_extension_hopbyhop_data_get(extension)                   ((internet_protocol_version6_option_t *) (&((uint8_t *) (extension))[2]))

#define internet_protocol_version6_extension_hopbyhop_length_get(extension)                 ((extension)->length * 8)
#define internet_protocol_version6_extension_hopbyhop_length_set(extension, v)              ((extension)->length = ((v) / 8 + ((v) % 8 ? 1 : 0)))

struct internet_protocol_version6_extension_hopbyhop {
    uint8_t next;
    uint8_t length;
};

struct internet_protocol_version6_extension_routing {
    uint8_t next;
    uint8_t length;
    uint8_t type;
    uint8_t left;
};

#define internet_protocol_version6_extension_routing_protocol_no                            (43)

#define internet_protocol_version6_extension_routing_total_get(extension)                   (((extension)->length + 1) * 8)
#define internet_protocol_version6_extension_routing_data_get(extension)                    ((internet_protocol_version6_routing_data_t *) (&((uint8_t *) (extension))[4]))

#define internet_protocol_version6_extension_routing_length_get(extension)                  ((extension)->length * 8)
#define internet_protocol_version6_extension_routing_length_set(extension, v)               ((extension)->length = ((v) / 8 + ((v) % 8 ? 1 : 0)))
#define internet_protocol_version6_extension_routing_type_get(extension)                    ((extension)->type)
#define internet_protocol_version6_extension_routing_type_set(extension, v)                 ((extension)->type = v)
#define internet_protocol_version6_extension_routing_segments_left_get(extension)           ((extension)->left)
#define internet_protocol_version6_extension_routing_segments_left_set(extension, v)        ((extension)->left = v)

struct internet_protocol_version6_extension_fragment {
    uint8_t next;
    uint8_t reserved;
    uint16_t offset:13;
    uint8_t flag:3;
    uint32_t identification;
};

#define internet_protocol_version6_extension_fragment_protocol_no                           (44)

#define internet_protocol_version6_extension_fragment_total_get(extension)                  (8)
#define internet_protocol_version6_extension_fragment_data_get(extension)                   (nil)

#define internet_protocol_version6_extension_fragment_offset_get(extension)                 ((extension)->offset)
#define internet_protocol_version6_extension_fragment_offset_set(extension, v)              ((extension)->offset = v)
#define intenret_protocol_version6_extension_fragment_flag_get(extension)                   ((extension)->flag)
#define internet_protocol_version6_extension_fragment_flag_set(extension, v)                ((extension)->flag = v)
#define internet_protocol_version6_extension_fragment_identification_get(extension)         ((extension)->identification)
#define internet_protocol_version6_extension_fragment_identification_set(extension, v)      ((extension)->identification = v)

struct internet_protocol_version6_extension_destination {
    uint8_t next;
    uint8_t length;
};

typedef int32_t (*internet_protocol_version6_context_handler_t)(internet_protocol_version6_module_t *, uint32_t, protocol_context_t *, internet_protocol_version6_context_t *);

struct internet_protocol_version6_module {
    internet_protocol_version6_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    internet_protocol_version6_context_handler_t on;
};

struct internet_protocol_version6_module_func {
    internet_protocol_version6_module_t * (*rem)(internet_protocol_version6_module_t *);
    int32_t (*deserialize)(internet_protocol_version6_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);
    int32_t (*serialize)(internet_protocol_version6_module_t *, protocol_context_t *, internet_protocol_version6_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_module_t *, FILE *, internet_protocol_version6_context_t *);
    int32_t (*in)(internet_protocol_version6_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);
//    int32_t (*out)(internet_protocol_version6_module_t *, protocol_context_t *, internet_protocol_version6_context_t *, protocol_packet_t **, uint64_t *);
    int32_t (*control_message_context_in)(internet_protocol_version6_module_t *, internet_control_message_protocol_version6_context_t *);
};

extern internet_protocol_version6_module_t * internet_protocol_version6_module_gen(protocol_module_map_t * map, internet_protocol_version6_context_handler_t on);
extern int32_t internet_protocol_version6_module_func_on(internet_protocol_version6_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context);

extern internet_protocol_version6_module_t * internet_protocol_version6_module_func_rem(internet_protocol_version6_module_t * module);
extern int32_t internet_protocol_version6_module_func_deserialize(internet_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version6_context_t ** context);
extern int32_t internet_protocol_version6_module_func_serialize(internet_protocol_version6_module_t * module, protocol_context_t * parent, internet_protocol_version6_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
extern void internet_protocol_version6_module_func_debug(internet_protocol_version6_module_t * module, FILE * stream, internet_protocol_version6_context_t * context);
extern int32_t internet_protocol_version6_module_func_in(internet_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version6_context_t ** context);

extern int32_t internet_protocol_version6_module_func_control_message_context_in(internet_protocol_version6_module_t * module, internet_control_message_protocol_version6_context_t * context);

#define internet_protocol_version6_module_rem(module)                                               ((module)->func->rem(module))
#define internet_protocol_version6_module_deserialize(module, packet, packetlen, parent, context)   ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version6_module_serialize(module, parent, context, packet, packetlen)     ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version6_module_debug(module, stream, context)                            ((module)->func->debug(module, stream, context))
#define internet_protocol_version6_module_in(module, packet, packetlen, parent, context)            ((module)->func->in(module, packet, packetlen, parent, context))

#define internet_protocol_version6_module_control_message_context_in(module, context)               ((module)->func->control_message_context_in(module, context))

#define internet_protocol_version6_module_on(module, type, parent, context)                         ((module)->on(module, type, parent, context))

typedef int32_t (*internet_protocol_version6_host_context_handler_t)(internet_protocol_version6_module_host_t *, uint32_t, protocol_context_t *, internet_protocol_version6_context_t *);

struct internet_protocol_version6_module_host {
    internet_protocol_version6_module_host_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    internet_protocol_version6_host_context_handler_t on;

    uint32_t link_maximum_transmission_unit;
    uint8_t current_hop_limit;
    uint32_t base_reachable_time;
    uint32_t reachable_time;
    uint32_t retransmission_timer;

#if       0
    hashtable_t * default_router_table;
#endif // 0
};

struct internet_protocol_version6_module_host_func {
    internet_protocol_version6_module_host_t * (*rem)(internet_protocol_version6_module_host_t *);
    int32_t (*deserialize)(internet_protocol_version6_module_host_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);
    int32_t (*serialize)(internet_protocol_version6_module_host_t *, protocol_context_t *, internet_protocol_version6_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_module_host_t *, FILE *, internet_protocol_version6_context_t *);
    int32_t (*in)(internet_protocol_version6_module_host_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);

    int32_t (*control_message_context_in)(internet_protocol_version6_module_host_t *, internet_control_message_protocol_version6_context_t *);
};

extern internet_protocol_version6_module_host_t * internet_protocol_version6_module_host_gen(protocol_module_map_t * map, internet_protocol_version6_host_context_handler_t on);
extern int32_t internet_protocol_version6_module_host_func_on(internet_protocol_version6_module_host_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context);
extern int32_t internet_protocol_version6_module_host_func_control_message_context_in(internet_protocol_version6_module_host_t * module, internet_control_message_protocol_version6_context_t * context);

typedef int32_t (*internet_protocol_version6_router_context_handler_t)(internet_protocol_version6_module_host_t *, uint32_t, protocol_context_t *, internet_protocol_version6_context_t *);

struct internet_protocol_version6_module_router {
    internet_protocol_version6_module_router_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    internet_protocol_version6_router_context_handler_t on;
};

struct internet_protocol_version6_module_router_func {
    internet_protocol_version6_module_router_t * (*rem)(internet_protocol_version6_module_router_t *);
    int32_t (*deserialize)(internet_protocol_version6_module_router_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);
    int32_t (*serialize)(internet_protocol_version6_module_router_t *, protocol_context_t *, internet_protocol_version6_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_module_router_t *, FILE *, internet_protocol_version6_context_t *);
    int32_t (*in)(internet_protocol_version6_module_router_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);

    int32_t (*control_message_context_in)(internet_protocol_version6_module_router_t *, internet_control_message_protocol_version6_context_t *);
};

extern internet_protocol_version6_module_router_t * internet_protocol_version6_module_router_gen(protocol_module_map_t * map, internet_protocol_version6_router_context_handler_t on);
extern int32_t internet_protocol_version6_module_router_func_on(internet_protocol_version6_module_host_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context);
extern int32_t internet_protocol_version6_module_router_func_control_message_context_in(internet_protocol_version6_module_router_t * module, internet_control_message_protocol_version6_context_t * context);

struct internet_protocol_version6_context {
    internet_protocol_version6_context_func_t * func;
    sync_t * sync;
    internet_protocol_version6_module_t * module;
    protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_protocol_version6_packet_t * datagram;
    uint64_t datagramlen;
    internet_protocol_version6_pseudo_t * pseudo;
    uint64_t pseudolen;

    uint8_t version;
    uint8_t traffic;
    uint32_t label;
//    uint16_t payloadlen;
};

struct internet_protocol_version6_context_func {
    internet_protocol_version6_context_t * (*rem)(internet_protocol_version6_context_t *);
    int32_t (*valid)(internet_protocol_version6_context_t *);
};

extern internet_protocol_version6_context_t * internet_protocol_version6_context_gen(internet_protocol_version6_module_t * module, protocol_context_t * parent, internet_protocol_version6_packet_t * datagram, uint64_t datagramlen);

#define internet_protocol_version6_context_rem(context)                     ((context)->func->rem(context))
#define internet_protocol_version6_context_valid(context)                   ((context)->func->valid(context))

#define internet_protocol_version6_context_error_get(context)               ((context)->error)
#define internet_protocol_version6_context_error_set(context, v)            ((context)->error = v)
#define internet_protocol_version6_context_packetlen_get(context)           ((context)->datagramlen)
#define internet_protocol_version6_context_packetlen_set(context, v)        ((context)->datagramlen = v)
#define internet_protocol_version6_context_version_get(context)             ((context)->version)
#define internet_protocol_version6_context_version_set(context, v)          ((context)->version = v)
#define internet_protocol_version6_context_traffic_class_get(contex)        ((context)->traffic)
#define internet_protocol_version6_context_traffic_class_set(context, v)    ((context)->traffic = v)
#define internet_protocol_version6_context_flow_label_get(context)          ((context)->label)
#define internet_protocol_version6_context_flow_label_set(context, v)       ((context)->label = v)
#define internet_protocol_version6_context_payload_length_get(context)      (htons((context)->datagram->payload))
#define internet_protocol_version6_context_payload_length_set(context, v)   ((context)->datagram->payload = ntohs(v))
#define internet_protocol_version6_context_next_header_get(context)         ((context)->datagram->next)
#define internet_protocol_version6_context_next_header_set(context, v)      ((context)->datagram->next = v)
#define internet_protocol_version6_context_hop_limit_get(context)           ((context)->datagram->limit)
#define internet_protocol_version6_context_hop_limit_set(context, v)        ((context)->datagram->limit = v)
#define internet_protocol_version6_context_source_get(context)              ((context)->datagram->source)
#define internet_protocol_version6_context_source_set(context, v)           (memcpy((context)->datagram->source, v, 16))
#define internet_protocol_version6_context_destination_get(context)         ((context)->datagram->destination)
#define internet_protocol_version6_context_destination_set(context, v)      (memcpy((context)->datagram->destination, v, 16))
#define internet_protocol_version6_context_pseudo_set(context, v, len)      (((context)->pseudolen = len), ((context)->pseudo = v))
#define internet_protocol_version6_context_pseudo_get(context)              ((context)->pseudo)
#define internet_protocol_version6_context_pseudolen_get(context)           ((context)->pseudolen)

#define internet_protocol_version6_context_next_protocol_get(context)       ((context)->datagram->next)
#define internet_protocol_version6_context_next_packet_get(context)         (&((protocol_packet_t *)((context)->datagram))[internet_protocol_version6_packet_header_length_min])
#define internet_protocol_version6_context_next_packetlen_get(context)      ((context)->datagramlen - sizeof(internet_protocol_version6_packet_t))

typedef int32_t (*internet_protocol_version6_extension_context_handler_t)(internet_protocol_version6_extension_module_t *, uint32_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_context_t *);

struct internet_protocol_version6_extension_module {
    internet_protocol_version6_extension_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t ** map;

    internet_protocol_version6_extension_context_handler_t on;
};

struct internet_protocol_version6_extension_module_func {
    internet_protocol_version6_extension_module_t * (*rem)(internet_protocol_version6_extension_module_t *);
    int32_t (*deserialize)(internet_protocol_version6_extension_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_context_t **);
    int32_t (*serialize)(internet_protocol_version6_extension_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_extension_module_t *, FILE *, internet_protocol_version6_extension_context_t *);
    int32_t (*in)(internet_protocol_version6_extension_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_context_t **);
//    int32_t (*out)(internet_protocol_version6_extension_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_context_t *, protocol_packet_t **, uint64_t *);
};

extern int32_t internet_protocol_version6_extension_module_func_on(internet_protocol_version6_extension_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_context_t * context);

#define internet_protocol_version6_extension_module_rem(module)                                                 ((module)->func->rem(module))
#define internet_protocol_version6_extension_module_deserialize(module, packet, packetlen, parent, context)     ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version6_extension_module_serialize(module, parent, context, packet, packetlen)       ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version6_extension_module_debug(module, stream, context)                              ((module)->func->debug(module, stream, context))
#define internet_protocol_version6_extension_module_in(module, packet, packetlen, parent, context)              ((module)->func->in(module, packet, packetlen, parent, context))

#define internet_protocol_version6_extension_module_on(module, type, parent, context)                           ((module)->on(module, type, parent, context))

struct internet_protocol_version6_extension_context {
    internet_protocol_version6_extension_context_func_t * func;
    sync_t * sync;
    internet_protocol_version6_extension_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_protocol_version6_extension_t * packet;
    uint64_t packetlen;
};

struct internet_protocol_version6_extension_context_func {
    internet_protocol_version6_extension_context_t * (*rem)(internet_protocol_version6_extension_context_t *);
    int32_t (*valid)(internet_protocol_version6_extension_context_t *);
};
#define internet_protocol_version6_extension_context_next_protocol_get(context)     (((internet_protocol_version6_extension_context_t *) (context))->packet->next)
#define internet_protocol_version6_extension_context_next_packetlen_get(context)    (((((internet_protocol_version6_extension_context_t *) (context))->packet->length) + 1) * 8)
#define internet_protocol_version6_extension_context_next_packet_get(context)       (&((protocol_packet_t *) ((context)->packet))[internet_protocol_version6_extension_context_next_packetlen_get(context)])

#define internet_protocol_version6_extension_context_rem(context)                   ((context)->func->rem(context))
#define internet_protocol_version6_extension_context_valid(context)                 ((context)->func->valid(context))

#define internet_protocol_version6_extension_context_length_set(context, v)         ((context)->packetlen = v)
#define internet_protocol_version6_extension_context_length_get(context)            ((context)->packetlen)

typedef int32_t (*internet_protocol_version6_extension_hopbyhop_context_handler_t)(internet_protocol_version6_extension_hopbyhop_module_t *, uint32_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_hopbyhop_context_t *);

struct internet_protocol_version6_extension_hopbyhop_module {
    internet_protocol_version6_extension_hopbyhop_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    internet_protocol_version6_extension_hopbyhop_context_handler_t on;
};

struct internet_protocol_version6_extension_hopbyhop_module_func {
    internet_protocol_version6_extension_hopbyhop_module_t * (*rem)(internet_protocol_version6_extension_hopbyhop_module_t *);
    int32_t (*deserialize)(internet_protocol_version6_extension_hopbyhop_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_hopbyhop_context_t **);
    int32_t (*serialize)(internet_protocol_version6_extension_hopbyhop_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_hopbyhop_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_extension_hopbyhop_module_t *, FILE *, internet_protocol_version6_extension_hopbyhop_context_t *);
    int32_t (*in)(internet_protocol_version6_extension_hopbyhop_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_hopbyhop_context_t **);
//    int32_t (*out)(internet_protocol_version6_extension_hopbyhop_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_hopbyhop_context_t *, protocol_packet_t **, uint64_t *);
};

extern internet_protocol_version6_extension_hopbyhop_module_t * internet_protocol_version6_extension_hopbyhop_module_gen(internet_protocol_version6_extension_hopbyhop_context_handler_t on);
extern int32_t internet_protocol_version6_extension_hopbyhop_module_func_on(internet_protocol_version6_extension_hopbyhop_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_hopbyhop_context_t * context);

#define internet_protocol_version6_extension_hopbyhop_module_rem(module)                                                ((module)->func->rem(module))
#define internet_protocol_version6_extension_hopbyhop_module_deserialize(module, packet, packetlen, parent, context)    ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version6_extension_hopbyhop_module_serialize(module, parent, context, packet, packetlen)      ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version6_extension_hopbyhop_module_debug(module, stream, context)                             ((module)->func->debug(module, stream, context))
#define internet_protocol_version6_extension_hopbyhop_module_in(module, packet, packetlen, parent, context)             ((module)->func->in(module, packet, packetlen, parent, context))

#define internet_protocol_version6_extension_hopbyhop_module_on(module, type, parent, context)                          ((module)->on(module, type, parent, context))

struct internet_protocol_version6_extension_hopbyhop_context {
    internet_protocol_version6_extension_hopbyhop_context_func_t * func;
    sync_t * sync;
    internet_protocol_version6_extension_hopbyhop_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_protocol_version6_extension_hopbyhop_t * extension;
    uint64_t extensionlen;

    internet_protocol_version6_option_t ** option;
    uint64_t optionlen;
};

struct internet_protocol_version6_extension_hopbyhop_context_func {
    internet_protocol_version6_extension_hopbyhop_context_t * (*rem)(internet_protocol_version6_extension_hopbyhop_context_t *);
    int32_t (*valid)(internet_protocol_version6_extension_hopbyhop_context_t *);
};

extern internet_protocol_version6_extension_hopbyhop_context_t * internet_protocol_version6_extension_hopbyhop_context_gen(internet_protocol_version6_extension_hopbyhop_module_t * module, internet_protocol_version6_context_t * parent, protocol_packet_t * datagram, uint64_t datagramlen);

#define internet_protocol_version6_extension_hopbyhop_context_option_begin(context)     (&((uint8_t *) ((context)->extension))[2])
#define internet_protocol_version6_extension_hopbyhop_context_option_end(context)       (&((uint8_t *) ((context)->extension))[(context)->extensionlen])

#define internet_protocol_version6_extension_hopbyhop_context_rem(context)              ((context)->func->rem(context))
#define internet_protocol_version6_extension_hopbyhop_context_valid(context)            ((context)->func->valid(context))

#define internet_protocol_version6_extension_hopbyhop_context_error_set(context, v)     ((context)->error = v)
#define internet_protocol_version6_extension_hopbyhop_context_error_get(context)        ((context)->error)
#define internet_protocol_version6_extension_hopbyhop_context_length_set(context, v)    ((context)->extensionlen = v)
#define internet_protocol_version6_extension_hopbyhop_context_length_get(context)       ((context)->extensionlen)

typedef int32_t (*internet_protocol_version6_extension_routing_context_handler_t)(internet_protocol_version6_extension_routing_module_t *, uint32_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_routing_context_t *);

struct internet_protocol_version6_extension_routing_module {
    internet_protocol_version6_extension_routing_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    internet_protocol_version6_extension_routing_context_handler_t on;
};

struct internet_protocol_version6_extension_routing_module_func {
    internet_protocol_version6_extension_routing_module_t * (*rem)(internet_protocol_version6_extension_routing_module_t *);
    int32_t (*deserialize)(internet_protocol_version6_extension_routing_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_routing_context_t **);
    int32_t (*serialize)(internet_protocol_version6_extension_routing_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_routing_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_extension_routing_module_t *, FILE *, internet_protocol_version6_extension_routing_context_t *);
    int32_t (*in)(internet_protocol_version6_extension_routing_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_routing_context_t **);
//    int32_t (*out)(internet_protocol_version6_extension_routing_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_routing_context_t *, protocol_packet_t **, uint64_t *);
};

extern internet_protocol_version6_extension_routing_module_t * internet_protocol_version6_extension_routing_module_gen(internet_protocol_version6_extension_routing_context_handler_t on);
extern int32_t internet_protocol_version6_extension_routing_module_func_on(internet_protocol_version6_extension_routing_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t * context);

#define internet_protocol_version6_extension_routing_module_rem(module)                                                 ((module)->func->rem(module))
#define internet_protocol_version6_extension_routing_module_deserialize(module, packet, packetlen, parent, context)     ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version6_extension_routing_module_serialize(module, parent, context, packet, packetlen)       ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version6_extension_routing_module_debug(module, stream, context)                              ((module)->func->debug(module, stream, context))
#define internet_protocol_version6_extension_routing_module_in(module, packet, packetlen, parent, context)              ((module)->func->in(module, packet, packetlen, parent, context))

#define internet_protocol_version6_extension_routing_module_on(module, type, parent, context)                           ((module)->on(module, type, parent, context))

struct internet_protocol_version6_extension_routing_context {
    internet_protocol_version6_extension_routing_context_func_t * func;
    sync_t * sync;
    internet_protocol_version6_extension_routing_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_protocol_version6_extension_routing_t * extension;
    uint64_t extensionlen;
};

struct internet_protocol_version6_extension_routing_context_func {
    internet_protocol_version6_extension_routing_context_t * (*rem)(internet_protocol_version6_extension_routing_context_t *);
    int32_t (*valid)(internet_protocol_version6_extension_routing_context_t *);
};

extern internet_protocol_version6_extension_routing_context_t * internet_protocol_version6_extension_routing_context_gen(internet_protocol_version6_extension_routing_module_t * module, internet_protocol_version6_context_t * parent, protocol_packet_t * datagram, uint64_t datagramlen);

#define internet_protocol_version6_extension_routing_context_rem(context)               ((context)->func->rem(context))
#define internet_protocol_version6_extension_routing_context_valid(context)             ((context)->func->valid(context))

#define internet_protocol_version6_extension_routing_context_error_set(context, v)      ((context)->error = v)
#define internet_protocol_version6_extension_routing_context_error_get(context)         ((context)->error)
#define internet_protocol_version6_extension_routing_context_length_set(context, v)     ((context)->extensionlen = v)
#define internet_protocol_version6_extension_routing_context_length_get(context)        ((context)->extensionlen)

typedef int32_t (*internet_protocol_version6_extension_fragment_context_handler_t)(internet_protocol_version6_extension_fragment_module_t *, uint32_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_fragment_context_t *);

struct internet_protocol_version6_extension_fragment_module {
    internet_protocol_version6_extension_fragment_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    internet_protocol_version6_extension_fragment_context_handler_t on;
};

struct internet_protocol_version6_extension_fragment_module_func {
    internet_protocol_version6_extension_fragment_module_t * (*rem)(internet_protocol_version6_extension_fragment_module_t *);
    int32_t (*deserialize)(internet_protocol_version6_extension_fragment_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_fragment_context_t **);
    int32_t (*serialize)(internet_protocol_version6_extension_fragment_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_fragment_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_extension_fragment_module_t *, FILE *, internet_protocol_version6_extension_fragment_context_t *);
    int32_t (*in)(internet_protocol_version6_extension_fragment_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_fragment_context_t **);
//    int32_t (*out)(internet_protocol_version6_extension_fragment_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_fragment_context_t *, protocol_packet_t **, uint64_t *);
};

extern internet_protocol_version6_extension_fragment_module_t * internet_protocol_version6_extension_fragment_module_gen(internet_protocol_version6_extension_fragment_context_handler_t on);
extern int32_t internet_protocol_version6_extension_fragment_module_func_on(internet_protocol_version6_extension_fragment_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_fragment_context_t * context);

#define internet_protocol_version6_extension_fragment_module_rem(module)                                                ((module)->func->rem(module))
#define internet_protocol_version6_extension_fragment_module_deserialize(module, packet, packetlen, parent, context)    ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version6_extension_fragment_module_serialize(module, parent, context, packet, packetlen)      ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version6_extension_fragment_module_debug(module, stream, context)                             ((module)->func->debug(module, stream, context))
#define internet_protocol_version6_extension_fragment_module_in(module, packet, packetlen, parent, context)             ((module)->func->in(module, packet, packetlen, parent, context))

#define internet_protocol_version6_extension_fragment_module_on(module, type, parent, context)                          ((module)->on(module, type, parent, context))

struct internet_protocol_version6_extension_fragment_context {
    internet_protocol_version6_extension_fragment_context_func_t * func;
    sync_t * sync;
    internet_protocol_version6_extension_fragment_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_protocol_version6_extension_fragment_t * extension;
    uint64_t extensionlen;
};

struct internet_protocol_version6_extension_fragment_context_func {
    internet_protocol_version6_extension_fragment_context_t * (*rem)(internet_protocol_version6_extension_fragment_context_t *);
    int32_t (*valid)(internet_protocol_version6_extension_fragment_context_t *);
};

extern internet_protocol_version6_extension_fragment_context_t * internet_protocol_version6_extension_fragment_context_gen(internet_protocol_version6_extension_fragment_module_t * module, internet_protocol_version6_context_t * parent, protocol_packet_t * datagram, uint64_t datagramlen);

#define internet_protocol_version6_extension_fragment_context_rem(context)              ((context)->func->rem(context))
#define internet_protocol_version6_extension_fragment_context_valid(context)            ((context)->func->valid(context))

#define internet_protocol_version6_extension_fragment_context_error_set(context, v)     ((context)->error = v)
#define internet_protocol_version6_extension_fragment_context_error_get(context)        ((context)->error)
#define internet_protocol_version6_extension_fragment_context_length_set(context, v)    ((context)->extensionlen = v)
#define internet_protocol_version6_extension_fragment_context_length_get(context)       ((context)->extensionlen)

typedef int32_t (*internet_protocol_version6_extension_destination_context_handler_t)(internet_protocol_version6_extension_destination_module_t *, uint32_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_destination_context_t *);

struct internet_protocol_version6_extension_destination_module {
    internet_protocol_version6_extension_destination_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    internet_protocol_version6_extension_destination_context_handler_t on;
};

struct internet_protocol_version6_extension_destination_module_func {
    internet_protocol_version6_extension_destination_module_t * (*rem)(internet_protocol_version6_extension_destination_module_t *);
    int32_t (*deserialize)(internet_protocol_version6_extension_destination_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_destination_context_t **);
    int32_t (*serialize)(internet_protocol_version6_extension_destination_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_destination_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version6_extension_destination_module_t *, FILE *, internet_protocol_version6_extension_destination_context_t *);
    int32_t (*in)(internet_protocol_version6_extension_destination_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_protocol_version6_extension_destination_context_t **);
//    int32_t (*out)(internet_protocol_version6_extension_destination_module_t *, internet_protocol_version6_context_t *, internet_protocol_version6_extension_destination_context_t *, protocol_packet_t **, uint64_t *);
};

extern internet_protocol_version6_extension_destination_module_t * internet_protocol_version6_extension_destination_module_gen(internet_protocol_version6_extension_destination_context_handler_t on);
extern int32_t internet_protocol_version6_extension_destination_module_func_on(internet_protocol_version6_extension_destination_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_destination_context_t * context);

#define internet_protocol_version6_extension_destination_module_rem(module)                                                 ((module)->func->rem(module))
#define internet_protocol_version6_extension_destination_module_deserialize(module, packet, packetlen, parent, context)     ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version6_extension_destination_module_serialize(module, parent, context, packet, packetlen)       ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version6_extension_destination_module_debug(module, stream, context)                              ((module)->func->debug(module, stream, context))
#define internet_protocol_version6_extension_destination_module_in(module, packet, packetlen, parent, context)              ((module)->func->in(module, packet, packetlen, parent, context))

#define internet_protocol_version6_extension_destination_module_on(module, type, parent, context)                           ((module)->on(module, type, parent, context))

struct internet_protocol_version6_extension_destination_context {
    internet_protocol_version6_extension_destination_context_func_t * func;
    sync_t * sync;
    internet_protocol_version6_extension_destination_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_protocol_version6_extension_destination_t * extension;
    uint64_t extensionlen;
};

struct internet_protocol_version6_extension_destination_context_func {
    internet_protocol_version6_extension_destination_context_t * (*rem)(internet_protocol_version6_extension_destination_context_t *);
    int32_t (*valid)(internet_protocol_version6_extension_destination_context_t *);
};

extern internet_protocol_version6_extension_destination_context_t * internet_protocol_version6_extension_destination_context_gen(internet_protocol_version6_extension_destination_module_t * module, internet_protocol_version6_context_t * parent, protocol_packet_t * datagram, uint64_t datagramlen);

#define internet_protocol_version6_extension_destination_context_option_begin(context)      (&((uint8_t *) ((context)->extension))[2])
#define internet_protocol_version6_extension_destination_context_option_end(context)        (&((uint8_t *) ((context)->extension))[(context)->extensionlen])

#define internet_protocol_version6_extension_destination_context_rem(context)               ((context)->func->rem(context))
#define internet_protocol_version6_extension_destination_context_valid(context)             ((context)->func->valid(context))

#define internet_protocol_version6_extension_destination_context_error_set(context, v)      ((context)->error = v)
#define internet_protocol_version6_extension_destination_context_error_get(context)         ((context)->error)
#define internet_protocol_version6_extension_destination_context_length_set(context, v)     ((context)->extensionlen = v)
#define internet_protocol_version6_extension_destination_context_length_get(context)        ((context)->extensionlen)

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION6__H__
