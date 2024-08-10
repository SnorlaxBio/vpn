/**
 * @file        snorlax/protocol/internet/version4.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 29, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_VERSION4__H__
#define   __SNORLAX__PROTOCOL_INTERNET_VERSION4__H__

#include <snorlax.h>
#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

#define internet_protocol_version4_packet_header_length_min             20

#define internet_protocol_version4_fragment_falgs_df_may                0
#define internet_protocol_version4_fragment_flags_df_do_not             1
#define internet_protocol_version4_fragment_flags_mf_last               0
#define internet_protocol_version4_fragment_flags_mf_more               1

#define internet_protocol_version4_option_type_end                      0
#define internet_protocol_version4_option_type_no_operation             1
#define internet_protocol_version4_option_type_security                 130
#define internet_protocol_version4_option_type_loose_source_route       131
#define internet_protocol_version4_option_type_strict_source_route      137
#define internet_protocol_version4_option_type_record_route             7
#define internet_protocol_version4_option_type_stream_identifier        136
#define internet_protocol_version4_option_type_internet_timestamp       68

struct internet_protocol_version4_packet;
struct internet_protocol_version4_pseudo;

struct internet_protocol_version4_module;
struct internet_protocol_version4_module_func;
struct internet_protocol_version4_context;
struct internet_protocol_version4_context_func;

typedef struct internet_protocol_version4_packet internet_protocol_version4_packet_t;
typedef struct internet_protocol_version4_pseudo internet_protocol_version4_pseudo_t;

typedef struct internet_protocol_version4_module internet_protocol_version4_module_t;
typedef struct internet_protocol_version4_module_func internet_protocol_version4_module_func_t;
typedef struct internet_protocol_version4_context internet_protocol_version4_context_t;
typedef struct internet_protocol_version4_context_func internet_protocol_version4_context_func_t;
typedef uint8_t internet_protocol_version4_option_t;
typedef uint8_t internet_protocol_version4_segment_t;

#define internet_protocol_version4_option_type_get(option)                                      (*(option))
#define internet_protocol_version4_option_length_get(option)                                    (*(option) == 0 || *(option) == 1 ? 1 : (option)[1])
#define internet_protocol_version4_option_security_field_get(option)                            (ntohs(*((uint16_t *)(&(option)[2]))))
#define internet_protocol_version4_option_security_compartment_field_get(option)                (ntohs(*((uint16_t *)(&(option)[4]))))
#define internet_protocol_version4_option_security_handling_restriction_field_get(option)       (ntohs(*((uint16_t *)(&(option)[6]))))
#define internet_protocol_version4_option_security_transmission_control_code_field_get(option)  ((ntohl(*((uint32_t *)(&(option)[7])))) & 0x00FFFFFFu)

#define internet_protocol_version4_option_loose_source_route_pointer_get(option)                ((option)[2])
#define internet_protocol_version4_option_loose_source_route_address_begin(option)              ((uint32_t *) (&(option)[3]))
#define internet_protocol_version4_option_loose_source_route_address_end(option)                ((uint32_t *)(&(option)[internet_protocol_version4_option_length_get(option)]))

#define internet_protocol_version4_option_strict_source_route_pointer_get(option)               ((option)[2])
#define internet_protocol_version4_option_strict_source_route_address_begin(option)             ((uint32_t *) (&(option)[3]))
#define internet_protocol_version4_option_strict_source_route_address_end(option)               ((uint32_t *)(&(option)[internet_protocol_version4_option_length_get(option)]))

#define internet_protocol_version4_option_record_route_pointer_get(option)                      ((option)[2])
#define internet_protocol_version4_option_record_route_address_begin(option)                    ((uint32_t *) (&(option)[3]))
#define internet_protocol_version4_option_record_route_address_end(option)                      ((uint32_t *)(&(option)[internet_protocol_version4_option_length_get(option)]))

#define internet_protocol_version4_option_stream_id_get(option)                                 (*((uint16_t *) (&(option)[2])))

#define internet_protocol_version4_option_internet_timestamp_length_max                         40

#define internet_protocol_version4_option_internet_timestamp_pointer_get(option)                ((option)[2])
#define internet_protocol_version4_option_internet_timestamp_overflow_get(option)               (((option)[3]) & 0x0Fu)
#define internet_protocol_version4_option_internet_timestamp_flag_get(option)                   (((option)[3]) >> 4)

#define internet_protocol_version4_option_internet_timestamp_begin(option)                      ((uint32_t *) (&(option)[4]))
#define internet_protocol_version4_option_internet_timestamp_end(option)                        ((uint32_t *)(&(option)[internet_protocol_version4_option_length_get(option)]))

struct internet_protocol_version4_packet {
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t length:4;
    uint8_t version:4;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t version:4;
    uint8_t length:4;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t  service;
    uint16_t total;
    uint16_t identification;
    uint16_t fragment;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint32_t source;
    uint32_t destination;
};

#define internet_protocol_version4_address_uint32_to_str(addr)          (inet_ntoa((struct in_addr) { .s_addr = addr }))

struct internet_protocol_version4_pseudo {
    uint32_t source;
    uint32_t destination;
    uint8_t zero;
    uint8_t protocol;
    uint8_t length;
};

extern internet_protocol_version4_pseudo_t * internet_protocol_version4_pseudo_gen(internet_protocol_version4_packet_t * datagram);

typedef uint64_t (*internet_protocol_version4_context_handler_t)(void);

struct internet_protocol_version4_module {
    internet_protocol_version4_module_func_t * func;
    sync_t * sync;
    protocol_module_t * parent;
    protocol_module_map_t * children;
};

struct internet_protocol_version4_module_func {
    internet_protocol_version4_module_t * (*rem)(internet_protocol_version4_module_t *);
    int32_t (*deserialize)(internet_protocol_version4_module_t *, protocol_packet_t *, uint32_t, protocol_context_t *, internet_protocol_version4_context_t **);
    int32_t (*serialize)(internet_protocol_version4_module_t *, protocol_context_t *, internet_protocol_version4_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(internet_protocol_version4_module_t *, FILE *, internet_protocol_version4_context_t *);
};

extern internet_protocol_version4_module_t * internet_protocol_version4_module_gen(protocol_module_t * parent, protocol_module_t ** children, uint64_t childrenlen, protocol_module_map_index_t index);

#define internet_protocol_version4_module_rem(module)                                               ((module)->func->rem(module))
#define internet_protocol_version4_module_deserialize(module, packet, packetlen, parent, context)   ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version4_module_serialize(module, parent, context, packet, packetlen)     ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version4_module_debug(module, stream, context)                            ((module)->func->debug(module, stream, context))

#define internet_protocol_version4_module_header_length_cal(datagram)       ((datagram)->length * 4)
#define internet_protocol_version4_module_option_offset_cal(datagram)       (&(((uint8_t *)(datagram))[internet_protocol_version4_packet_header_length_min]))
#define internet_protocol_version4_module_segment_offset_cal(datagram)      (&(((uint8_t *)(datagram))[internet_protocol_version4_module_header_length_cal(datagram)]))

extern uint16_t internet_protocol_version4_module_checksum_cal(internet_protocol_version4_packet_t * datagram);

struct internet_protocol_version4_context {
    internet_protocol_version4_context_func_t * func;
    sync_t * sync;
    protocol_context_t * parent;
    protocol_context_t * subcontext;
    int32_t error;
    internet_protocol_version4_packet_t * datagram;
    uint64_t datagramlen;
    internet_protocol_version4_pseudo_t * pseudo;
    uint64_t pseudolen;

    uint16_t total;
    uint16_t checksum;
    uint16_t identification;
    union {
        uint16_t value;
        struct {
            uint8_t zero:1;
            uint8_t df:1;
            uint8_t mf:1;
            uint16_t offset: 13;
        } detail;
    } fragment;
    
    uint32_t source;
    uint32_t destination;
    internet_protocol_version4_option_t * option;
    internet_protocol_version4_segment_t * segment;
    uint32_t segmentlen;
};

struct internet_protocol_version4_context_func {
    internet_protocol_version4_context_t * (*rem)(internet_protocol_version4_context_t *);
};

extern internet_protocol_version4_context_t * internet_protocol_version4_context_gen(protocol_context_t * parent, internet_protocol_version4_packet_t * datagram, uint64_t datagramlen);

#define internet_protocol_version4_context_rem(context)                     ((context)->func->rem(context))

#define internet_protocol_version4_context_error_set(context, v)            ((context)->error = v)
#define internet_protocol_version4_context_error_get(context)               ((context)->error)
#define internet_protocol_version4_context_packetlen_set(context, v)        ((context)->datagramlen = v)
#define internet_protocol_version4_context_packetlen_get(context)           ((context)->datagramlen)
#define internet_protocol_version4_context_total_set(context, v)            ((context)->total = v)
#define internet_protocol_version4_context_total_get(context)               ((context)->total)
#define internet_protocol_version4_context_checksum_set(context, v)         ((context)->checksum = v)
#define internet_protocol_version4_context_checksum_get(context)            ((context)->checksum)
#define internet_protocol_version4_context_identification_set(context, v)   ((context)->identification = v)
#define internet_protocol_version4_context_identification_get(context)      ((context)->identification)
#define internet_protocol_version4_context_fragment_set(context, v)         ((context)->fragment.value = v)
#define internet_protocol_version4_context_fragment_get(context)            ((context)->fragment.value)
#define internet_protocol_version4_context_fragment_offset_set(context, v)  ((context)->fragment.detail.offset = v)
#define internet_protocol_version4_context_fragment_offset_get(context)     ((context)->fragment.detail.offset)
#define internet_protocol_version4_context_fragment_df_set(context, v)      ((context)->fragment.detail.df = v)
#define internet_protocol_version4_context_fragment_df_get(context)         ((context)->fragment.detail.df)
#define internet_protocol_version4_context_fragment_mf_set(context, v)      ((context)->fragment.detail.mf = v)
#define internet_protocol_version4_context_fragment_mf_get(context)         ((context)->fragment.detail.mf)
#define internet_protocol_version4_context_source_set(context, v)           ((context)->datagram->source = v)
#define internet_protocol_version4_context_source_get(context)              ((context)->datagram->source)
#define internet_protocol_version4_context_destination_set(context, v)      ((context)->datagram->destination = v)
#define internet_protocol_version4_context_destination_get(context)         ((context)->datagram->destination)
#define internet_protocol_version4_context_option_offset_set(context, v)    ((context)->option = ((internet_protocol_version4_option_t *) v))
#define internet_protocol_version4_context_option_offset_get(context)       ((context)->option)
#define internet_protocol_version4_context_segment_offset_set(context, v)   ((context)->segment = ((internet_protocol_version4_segment_t *) v))
#define internet_protocol_version4_context_segment_offset_get(context)      ((context)->segment)
#define internet_protocol_version4_context_segment_length_set(context, v)   ((context)->segmentlen = v)
#define internet_protocol_version4_context_segment_length_get(context)      ((context)->segmentlen)

#define internet_protocol_version4_context_version_set(context, v)          ((context)->datagram->version = v)
#define internet_protocol_version4_context_version_get(context)             ((context)->datagram->version)
#define internet_protocol_version4_context_length_set(context, v)           ((context)->datagram->length = v)
#define internet_protocol_version4_context_length_get(context)              ((context)->datagram->length)
#define internet_protocol_version4_context_service_set(context, v)          ((context)->datagram->service = v)
#define internet_protocol_version4_context_service_get(context)             ((context)->datagram->service)
#define internet_protocol_version4_context_ttl_set(context)                 ((context)->datagram->ttl = v)
#define internet_protocol_version4_context_ttl_get(context)                 ((context)->datagram->ttl)
#define internet_protocol_version4_context_protocol_set(context)            ((context)->datagram->protocol = v)
#define internet_protocol_version4_context_protocol_get(context)            ((context)->datagram->protocol)

#define internet_protocol_version4_context_pseudo_set(context, v, len)      (((context)->pseudolen = len), ((context)->pseudo = v))
#define internet_protocol_version4_context_pseudo_get(context)              ((context)->pseudo)
#define internet_protocol_version4_context_pseudolen_get(context)           ((context)->pseudolen)

#define internet_protocol_version4_context_segment_length_cal(context)      (internet_protocol_version4_context_total_get(context) - internet_protocol_version4_module_header_length_cal((context)->datagram))

#define internet_protocol_version4_context_option_offset_next(option)       ((*(option) == 0 || *(option) == 1) ? (option) + 1 : (option) + (option)[1])

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION4__H__
