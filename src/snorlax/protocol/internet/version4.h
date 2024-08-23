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
struct internet_protocol_version6_address;

struct internet_protocol_version4_module;
struct internet_protocol_version4_module_func;
struct internet_protocol_version4_context;
struct internet_protocol_version4_context_func;

typedef struct internet_protocol_version4_packet internet_protocol_version4_packet_t;
typedef struct internet_protocol_version4_pseudo internet_protocol_version4_pseudo_t;
typedef struct internet_protocol_version6_address internet_protocol_version6_address_t;

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

#define internet_protocol_version4_context_buffer_reserve(context, n)                           (protocol_context_buffer_reversal_reserve((protocol_context_t *) context, n))

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

// extern internet_protocol_version4_packet_t * internet_protocol_version4_packet_build(internet_protocol_packet_t * buffer, uint64_t n, const internet_protocol_address_t * source, const internet_protocol_address_t * destination);

#define internet_protocol_version4_address_uint32_to_str(addr)          (inet_ntoa((struct in_addr) { .s_addr = addr }))

struct internet_protocol_version4_pseudo {
    uint32_t source;
    uint32_t destination;
    uint8_t zero;
    uint8_t protocol;
    uint16_t length;
};

struct internet_protocol_version4_address {
    uint32_t value;
};

extern internet_protocol_version4_pseudo_t * internet_protocol_version4_pseudo_gen(internet_protocol_version4_packet_t * datagram);
extern uint16_t internet_protocol_version4_checksum_cal(internet_protocol_version4_packet_t * datagram, uint64_t datagramlen);
extern uint32_t internet_protocol_version4_direction_cal(uint32_t source, uint32_t destination, uint32_t * local);
extern const char * internet_protocol_version4_address_to_string(char * s, uint32_t addr);
extern uint16_t internet_protocol_version4_fragment_field_gen(uint8_t df, uint8_t mf, uint16_t offset);

#define internet_protocol_version4_to_addr(addr)                                (*((uint32_t *)(addr)))


typedef int32_t (*internet_protocol_version4_context_handler_t)(internet_protocol_version4_module_t *, uint32_t, protocol_context_t *, internet_protocol_version4_context_t *);

struct internet_protocol_version4_module {
    internet_protocol_version4_module_func_t * func;
    sync_t * sync;
    uint16_t type;
    uint16_t addrlen;
    ___reference protocol_module_map_t * map;

    internet_protocol_version4_context_handler_t on;

    internet_protocol_module_t * parent;
    ___reference uint32_t * addr;

    uint16_t identification;
    uint8_t default_ttl;
};

struct internet_protocol_version4_module_func {
    internet_protocol_version4_module_t * (*rem)(internet_protocol_version4_module_t *);
    int32_t (*deserialize)(internet_protocol_version4_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version4_context_t **);
    int32_t (*serialize)(internet_protocol_version4_module_t *, protocol_context_t *, internet_protocol_version4_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_protocol_version4_module_t *, FILE *, internet_protocol_version4_context_t *);
    int32_t (*in)(internet_protocol_version4_module_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version4_context_t **);
    int32_t (*out)(internet_protocol_version4_module_t *, protocol_path_node_t *, protocol_context_t *);
    internet_protocol_version4_context_t * (*context_gen)(internet_protocol_version4_module_t *, protocol_path_node_t *, protocol_context_t *);
    internet_protocol_version4_context_t * (*reply_gen)(internet_protocol_version4_module_t *, internet_protocol_version4_context_t *);

    int32_t (*local_is)(internet_protocol_version4_module_t *, uint32_t);

};

extern internet_protocol_version4_module_t * internet_protocol_version4_module_gen(protocol_module_map_t * map, internet_protocol_version4_context_handler_t on, uint32_t * addr);

extern int32_t internet_protocol_version4_module_func_local_is(internet_protocol_version4_module_t * module, uint32_t addr);

extern int32_t internet_protocol_version4_module_func_on(internet_protocol_version4_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version4_context_t * context);

#define internet_protocol_version4_module_addrlen_get(module)                                       ((module)->addrlen)
#define internet_protocol_version4_module_number_get(module)                                        ((module)->type)

#define internet_protocol_version4_module_rem(module)                                               ((module)->func->rem(module))
#define internet_protocol_version4_module_deserialize(module, packet, packetlen, parent, context)   ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_protocol_version4_module_serialize(module, parent, context, packet, packetlen)     ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_protocol_version4_module_debug(module, stream, context)                            ((module)->func->debug(module, stream, context))
#define internet_protocol_version4_module_in(module, packet, packetlen, parent, context)            ((module)->func->in(module, packet, packetlen, parent, context))
#define internet_protocol_version4_module_out(module, node, child)                                  ((module)->func->out(module, node, child))
#define internet_protocol_version4_module_context_gen(module, node, child)                          ((module)->func->context_gen(module, node, child))
#define internet_protocol_version4_module_reply_gen(module, request)                                ((module)->func->reply_gen(module, request))

#define internet_protocol_version4_module_local_is(module, addr)                                    ((module)->func->local_is(module, addr))

#define internet_protocol_version4_module_on(module, type, parent, context)                         ((module)->on(module, type, parent, context))

#define internet_protocol_version4_module_identification_gen(module)                                ((module)->identification = (module)->identification + 1)
#define internet_protocol_version4_module_default_ttl_get(module)                                   ((module)->default_ttl)

#define internet_protocol_version4_module_header_length_cal(datagram)                               ((datagram)->length * 4)
#define internet_protocol_version4_module_option_offset_cal(datagram)                               (&(((uint8_t *)(datagram))[internet_protocol_version4_packet_header_length_min]))
#define internet_protocol_version4_module_segment_offset_cal(datagram)                              (&(((uint8_t *)(datagram))[internet_protocol_version4_module_header_length_cal(datagram)]))

struct internet_protocol_version4_context {
    internet_protocol_version4_context_func_t * func;
    sync_t * sync;
    ___reference internet_protocol_version4_module_t * module;
    ___reference protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    ___reference internet_protocol_version4_packet_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;

    internet_protocol_version4_pseudo_t * pseudo;
    uint64_t pseudolen;

    uint16_t checksumcal;
    internet_protocol_version4_option_t * option;
    internet_protocol_version4_segment_t * segment;
    uint64_t segmentlen;
};

struct internet_protocol_version4_context_func {
    internet_protocol_version4_context_t * (*rem)(internet_protocol_version4_context_t *);
    int32_t (*valid)(internet_protocol_version4_context_t *);
    uint8_t * (*addrptr)(internet_protocol_version4_context_t *, uint32_t);
    void (*checksum_build)(internet_protocol_version4_context_t *, const uint8_t *, uint64_t);
};

extern internet_protocol_version4_context_t * internet_protocol_version4_context_gen(internet_protocol_version4_module_t * module, protocol_context_t * parent, internet_protocol_version4_packet_t * datagram, uint64_t datagramlen, uint64_t bufferlen);

#define internet_protocol_version4_context_rem(context)                                     ((context)->func->rem(context))
#define internet_protocol_version4_context_valid(context)                                   ((context)->func->valid(context))
#define internet_protocol_version4_context_addrptr(context, type)                           ((context)->func->addrptr(context, type))
#define internet_protocol_version4_context_checksum_build(context, pseudo, pseudolen)       ((context)->func->checksum_build(context, pseudo, pseudolen))
#define internet_protocol_version4_context_checksum_cal(context)                            (internet_protocol_version4_checksum_cal((context)->packet, (context)->packetlen))

#define internet_protocol_version4_context_datagram_get(context)                            ((context)->packet)
#define internet_protocol_version4_context_datagramlen_get(context)                         ((context)->packetlen)

#define internet_protocol_version4_context_error_set(context, v)                            ((context)->error = v)
#define internet_protocol_version4_context_error_get(context)                               ((context)->error)
#define internet_protocol_version4_context_packetlen_set(context, v)                        ((context)->packetlen = v)
#define internet_protocol_version4_context_packetlen_get(context)                           ((context)->packetlen)
#define internet_protocol_version4_context_checksumcal_get(context)                         ((context)->checksumcal)
#define internet_protocol_version4_context_checksumcal_set(context, v)                      ((context)->checksumcal = v)
// #define internet_protocol_version4_context_direction_get(context)                           ((context)->direction)
// #define internet_protocol_version4_context_direction_set(context, v)                        ((context)->direction = v)

#define internet_protocol_version4_context_total_set(context, v)                            ((context)->packet->total = ntohs(v))
#define internet_protocol_version4_context_total_get(context)                               (htons((context)->packet->total))
#define internet_protocol_version4_context_checksum_set(context, v)                         ((context)->packet->checksum = ntohs(v))
#define internet_protocol_version4_context_checksum_get(context)                            (htons((context)->packet->checksum))
#define internet_protocol_version4_context_identification_set(context, v)                   ((context)->packet->identification = ntohs(v))
#define internet_protocol_version4_context_identification_get(context)                      (htons((context)->packet->identification))
#define internet_protocol_version4_context_fragment_set(context, v)                         ((context)->packet->fragment = ntohs(v))
#define internet_protocol_version4_context_fragment_get(context)                            (htons((context)->packet->fragment))
// TODO: MUST UPGRADE START
// #define internet_protocol_version4_context_fragment_offset_set(context, v)  ((context)->fragment.detail.offset = v)
// #define internet_protocol_version4_context_fragment_offset_get(context)     ((context)->fragment.detail.offset)
// #define internet_protocol_version4_context_fragment_df_set(context, v)      ((context)->fragment.detail.df = v)
// #define internet_protocol_version4_context_fragment_df_get(context)         ((context)->fragment.detail.df)
// #define internet_protocol_version4_context_fragment_mf_set(context, v)      ((context)->fragment.detail.mf = v)
// #define internet_protocol_version4_context_fragment_mf_get(context)         ((context)->fragment.detail.mf)
// TODO: MUST UPGRADE END
#define internet_protocol_version4_context_source_set(context, v)                           ((context)->packet->source = htonl(v))
#define internet_protocol_version4_context_source_get(context)                              (ntohl((context)->packet->source))
#define internet_protocol_version4_context_source_ptr_get(context)                          ((uint8_t *) (&((context)->packet->source)))
#define internet_protocol_version4_context_destination_set(context, v)                      ((context)->packet->destination = htonl(v))
#define internet_protocol_version4_context_destination_get(context)                         (ntohl((context)->packet->destination))
#define internet_protocol_version4_context_destination_ptr_get(context)                     ((uint8_t *) (&((context)->packet->destination)))
#define internet_protocol_version4_context_option_set(context, v)                           ((context)->option = ((internet_protocol_version4_option_t *) v))
#define internet_protocol_version4_context_option_get(context)                              ((context)->option)

#define internet_protocol_version4_context_segment_set(context, v)                          ((context)->segment = ((internet_protocol_version4_segment_t *) v))
#define internet_protocol_version4_context_segment_get(context)                             ((context)->segment)
#define internet_protocol_version4_context_segmentlen_set(context, v)                       ((context)->segmentlen = v)
#define internet_protocol_version4_context_segmentlen_get(context)                          ((context)->segmentlen)

#define internet_protocol_version4_context_version_set(context, v)                          ((context)->packet->version = v)
#define internet_protocol_version4_context_version_get(context)                             ((context)->packet->version)
#define internet_protocol_version4_context_length_set(context, v)                           ((context)->packet->length = v)
#define internet_protocol_version4_context_length_get(context)                              ((context)->packet->length)
#define internet_protocol_version4_context_service_set(context, v)                          ((context)->packet->service = v)
#define internet_protocol_version4_context_service_get(context)                             ((context)->packet->service)
#define internet_protocol_version4_context_ttl_set(context, v)                              ((context)->packet->ttl = v)
#define internet_protocol_version4_context_ttl_get(context)                                 ((context)->packet->ttl)
#define internet_protocol_version4_context_protocol_set(context, v)                         ((context)->packet->protocol = v)
#define internet_protocol_version4_context_protocol_get(context)                            ((context)->packet->protocol)

#define internet_protocol_version4_context_pseudo_set(context, v, len)                      (((context)->pseudolen = len), ((context)->pseudo = v))
#define internet_protocol_version4_context_pseudo_get(context)                              ((context)->pseudo)
#define internet_protocol_version4_context_pseudolen_get(context)                           ((context)->pseudolen)

#define internet_protocol_version4_context_segment_length_cal(context)                      (internet_protocol_version4_context_total_get(context) - internet_protocol_version4_module_header_length_cal((context)->packet))

#define internet_protocol_version4_context_option_offset_next(option)                       ((*(option) == 0 || *(option) == 1) ? (option) + 1 : (option) + (option)[1])

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION4__H__
