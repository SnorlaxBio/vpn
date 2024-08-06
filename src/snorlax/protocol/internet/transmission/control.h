/**
 * @file        snorlax/protocol/internet/transmission/control.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 8, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_TRANSMISSION_CONTROL__H__
#define   __SNORLAX__PROTOCOL_INTERNET_TRANSMISSION_CONTROL__H__

#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

struct transmission_control_protocol_packet;

struct transmission_control_protocol_module;
struct transmission_control_protocol_module_func;
struct transmission_control_protocol_context;
struct transmission_control_protocol_context_func;

typedef struct transmission_control_protocol_packet transmission_control_protocol_packet_t;
typedef uint8_t transmission_control_protocol_option_t;

typedef struct transmission_control_protocol_module transmission_control_protocol_module_t;
typedef struct transmission_control_protocol_module_func transmission_control_protocol_module_func_t;
typedef struct transmission_control_protocol_context transmission_control_protocol_context_t;
typedef struct transmission_control_protocol_context_func transmission_control_protocol_context_func_t;

struct transmission_control_protocol_packet {
    uint16_t source;
    uint16_t destination;
    uint32_t sequence;
    uint32_t acknowledgment;
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t reserved:4;
    uint8_t offset:4;
    uint8_t fin:1;
    uint8_t syn:1;
    uint8_t rst:1;
    uint8_t psh:1;
    uint8_t ack:1;
    uint8_t urg:1;
    uint8_t ece:1;
    uint8_t cwr:1;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t offset:4;
    uint8_t reserved:4;
    uint8_t cwr:1;
    uint8_t ece:1;
    uint8_t urg:1;
    uint8_t ack:1;
    uint8_t psh:1;
    uint8_t rst:1;
    uint8_t syn:1;
    uint8_t fin:1;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint16_t window;
    uint16_t checksum;
    uint16_t pointer;
};

#define transmission_control_protocol_packet_length_min                     20

extern uint16_t transmission_control_protocol_checksum_cal(transmission_control_protocol_packet_t * segment, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen);

#define transmission_control_protocol_option_type_end                       0
#define transmission_control_protocol_option_type_no_operation              1
#define transmission_control_protocol_option_type_maximum_segment_size      2

#define transmission_control_protocol_option_length_get(option)             ((*(option) == 0 || *(option) == 1) ? 1 : *(option)[1])

struct transmission_control_protocol_module {
    transmission_control_protocol_module_func_t * func;
    sync_t * sync;
    internet_protocol_module_t * parent;
    protocol_module_map_t * map;
};

struct transmission_control_protocol_module_func {
    transmission_control_protocol_module_t * (*rem)(transmission_control_protocol_module_t *);
    int32_t (*deserialize)(transmission_control_protocol_module_t *, protocol_packet_t *, uint32_t, internet_protocol_context_t *, transmission_control_protocol_context_t **);
    int32_t (*serialize)(transmission_control_protocol_module_t *, internet_protocol_context_t *, transmission_control_protocol_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(transmission_control_protocol_module_t *, FILE *, transmission_control_protocol_context_t *);
};

extern transmission_control_protocol_module_t * transmission_control_protocol_module_gen(internet_protocol_module_t * parent, protocol_module_t ** children, uint64_t childrenlen, protocol_module_map_index_t index);

#define transmission_control_protocol_module_rem(module)                                                     ((module)->func->rem(module))
#define transmission_control_protocol_module_deserialize(module, packet, packetlen, parent, context)         ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define transmission_control_protocol_module_serialize(module, parent, context, packet, len)                 ((module)->func->serialize(module, parent, context, packet, len))
#define transmission_control_protocol_module_debug(module, stream, context)                                  ((module)->func->debug(module, stream, context))

struct transmission_control_protocol_context {
    transmission_control_protocol_context_func_t * func;
    sync_t * sync;
    internet_protocol_context_t * parent;
    protocol_context_t * subcontext;
    int32_t error;
    transmission_control_protocol_packet_t * packet;
    uint64_t packetlen;
    internet_protocol_pseudo_t * pseudo;
    uint64_t pseudolen;

    uint16_t source;
    uint16_t destination;
    uint32_t sequence;
    uint32_t acknowledgment;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent;

    uint32_t headerlen;
    uint32_t datalen;

    transmission_control_protocol_option_t * option;
    uint8_t * data;
    
};

struct transmission_control_protocol_context_func {
    transmission_control_protocol_context_t * (*rem)(transmission_control_protocol_context_t *); 
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen);

#define transmission_control_protocol_context_rem(context)                      ((context)->func->rem(context))

#define transmission_control_protocol_context_error_get(context)                ((context)->error)
#define transmission_control_protocol_context_error_set(context, v)             ((context)->error = v)
#define transmission_control_protocol_context_packetlen_get(context)            ((context)->packetlen)
#define transmission_control_protocol_context_headerlen_get(context)            ((context)->headerlen)
#define transmission_control_protocol_context_headerlen_set(context, v)         ((context)->headerlen = v)
#define transmission_control_protocol_context_datalen_get(context)              ((context)->datalen)
#define transmission_control_protocol_context_datalen_set(context, v)           ((context)->datalen = v)
#define transmission_control_protocol_context_source_get(context)               ((context)->source)
#define transmission_control_protocol_context_source_set(context, v)            ((context)->source = v)
#define transmission_control_protocol_context_destination_get(context)          ((context)->destination)
#define transmission_control_protocol_context_destination_set(context, v)       ((context)->destination = v)
#define transmission_control_protocol_context_sequence_get(context)             ((context)->sequence)
#define transmission_control_protocol_context_sequence_set(context, v)          ((context)->sequence = v)
#define transmission_control_protocol_context_acknowledgment_get(context)       ((context)->acknowledgment)
#define transmission_control_protocol_context_acknowledgment_set(context, v)    ((context)->acknowledgment = v)
#define transmission_control_protocol_context_offset_get(context)               ((context)->packet->offset)
#define transmission_control_protocol_context_offset_set(context, v)            ((context)->packet->offset = v)
#define transmission_control_protocol_context_cwr_get(context)                  ((context)->packet->cwr)
#define transmission_control_protocol_context_cwr_on(context)                   ((context)->packet->cwr = 1)
#define transmission_control_protocol_context_cwr_off(context)                  ((context)->packet->cwr = 0)
#define transmission_control_protocol_context_ece_get(context)                  ((context)->packet->ece)
#define transmission_control_protocol_context_ece_on(context)                   ((context)->packet->ece = 1)
#define transmission_control_protocol_context_ece_off(context)                  ((context)->packet->ece = 0)
#define transmission_control_protocol_context_urg_get(context)                  ((context)->packet->urg)
#define transmission_control_protocol_context_urg_on(context)                   ((context)->packet->urg = 1)
#define transmission_control_protocol_context_urg_off(context)                  ((context)->packet->urg = 0)
#define transmission_control_protocol_context_ack_get(context)                  ((context)->packet->ack)
#define transmission_control_protocol_context_ack_on(context)                   ((context)->packet->ack = 1)
#define transmission_control_protocol_context_ack_off(context)                  ((context)->packet->ack = 0)
#define transmission_control_protocol_context_psh_get(context)                  ((context)->packet->psh)
#define transmission_control_protocol_context_psh_on(context)                   ((context)->packet->psh = 1)
#define transmission_control_protocol_context_psh_off(context)                  ((context)->packet->psh = 0)
#define transmission_control_protocol_context_rst_get(context)                  ((context)->packet->rst)
#define transmission_control_protocol_context_rst_on(context)                   ((context)->packet->rst = 1)
#define transmission_control_protocol_context_rst_off(context)                  ((context)->packet->rst = 0)
#define transmission_control_protocol_context_syn_get(context)                  ((context)->packet->syn)
#define transmission_control_protocol_context_syn_on(context)                   ((context)->packet->syn = 1)
#define transmission_control_protocol_context_syn_off(context)                  ((context)->packet->syn = 0)
#define transmission_control_protocol_context_fin_get(context)                  ((context)->packet->fin)
#define transmission_control_protocol_context_fin_on(context)                   ((context)->packet->fin = 1)
#define transmission_control_protocol_context_fin_off(context)                  ((context)->packet->fin = 0)
#define transmission_control_protocol_context_window_get(context)               ((context)->window)
#define transmission_control_protocol_context_window_set(context, v)            ((context)->window = v)
#define transmission_control_protocol_context_checksum_get(context)             ((context)->checksum)
#define transmission_control_protocol_context_checksum_set(context, v)          ((context)->checksum = v)
#define transmission_control_protocol_context_urgent_get(context)               ((context)->urgent)
#define transmission_control_protocol_context_urgent_set(context, v)            ((context)->urgent = v)
#define transmission_control_protocol_context_option_get(context)               ((context)->option)
#define transmission_control_protocol_context_option_set(context, v)            ((context)->option = v)
#define transmission_control_protocol_context_data_get(context)                 ((context)->data)
#define transmission_control_protocol_context_data_set(context, v)              ((context)->data = v)

#define transmission_control_protocol_context_data_cal(context)                 (transmission_control_protocol_context_headerlen_get(context) == transmission_control_protocol_context_packetlen_get(context) ? nil : (&((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)]))
#define transmission_control_protocol_context_option_cal(context)               (transmission_control_protocol_context_headerlen_get(context) == (transmission_control_protocol_context_offset_get(context) * 4) ? nil : &((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)])

#endif // __SNORLAX__PROTOCOL_INTERNET_TRANSMISSION_CONTROL__H__
