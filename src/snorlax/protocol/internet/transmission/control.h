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

#include <snorlax/hashtable.h>
#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

struct transmission_control_block;
struct transmission_control_block_func;

typedef hashtable_t transmission_control_block_map_t;

struct transmission_control_protocol_packet;
union transmission_control_protocol_address_pair;

struct transmission_control_protocol_module;
struct transmission_control_protocol_module_func;
struct transmission_control_protocol_context;
struct transmission_control_protocol_context_func;

typedef struct transmission_control_block transmission_control_block_t;
typedef struct transmission_control_block_func transmission_control_block_func_t;

typedef struct transmission_control_protocol_packet transmission_control_protocol_packet_t;
typedef union transmission_control_protocol_address_pair transmission_control_protocol_address_pair_t;
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

union transmission_control_protocol_address_pair {
    struct {
        struct {
            uint32_t addr;
            uint16_t port;
        } local;
        struct {
            uint32_t addr;
            uint16_t port;
        } foreign;
    } version4;
    struct {
        struct {
            uint8_t addr[16];
            uint16_t port;
        } local;
        struct {
            uint8_t addr[16];
            uint16_t port;
        } foreign;
    } version6;
};

extern int32_t transmission_control_protocol_address_pair_init(transmission_control_protocol_address_pair_t * pair, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

#define transmission_control_protocol_packet_length_min                     20

extern uint16_t transmission_control_protocol_checksum_cal(transmission_control_protocol_packet_t * segment, uint64_t segmentlen, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen);

#define transmission_control_protocol_option_type_end                       0
#define transmission_control_protocol_option_type_no_operation              1
#define transmission_control_protocol_option_type_maximum_segment_size      2

#define transmission_control_protocol_option_length_get(option)             ((*(option) == 0 || *(option) == 1) ? 1 : *(option)[1])


struct transmission_control_block {
    transmission_control_block_func_t * func;
    sync_t * sync;
    hashtable_list_t * collection;
    hashtable_node_t * prev;
    hashtable_node_t * next;
    hashtable_node_key_t key;

    uint32_t state;
    uint32_t sequence;
};

struct transmission_control_block_func {
    transmission_control_block_t * (*rem)(transmission_control_block_t *);

    int32_t (*open)(transmission_control_block_t *);
    int32_t (*send)(transmission_control_block_t *);
    int32_t (*recv)(transmission_control_block_t *);
    int32_t (*close)(transmission_control_block_t *);
    int32_t (*listen)(transmission_control_block_t *);
};

#define transmission_control_state_none                             0
#define transmission_control_state_listen                           1
#define transmission_control_state_synchronize_sent                 2
#define transmission_control_state_synchronize_received             3
#define transmission_control_state_established                      4
#define transmission_control_state_finish_wait_1                    5
#define transmission_control_state_finish_wait_2                    6
#define transmission_control_state_close_wait                       7
#define transmission_control_state_closing                          8
#define transmission_control_state_last_acknowledgment              9
#define transmission_control_state_time_wait                        10
#define transmission_control_state_closed                           0

extern transmission_control_block_t * transmission_control_block_gen(transmission_control_protocol_address_pair_t * pair);

#define transmission_control_block_func_hash                        internet_protocol_version_hash

#define transmission_control_block_rem(block)                       ((block)->func->rem(block))
#define transmission_control_block_open(block)                      ((block)->func->open(block))
#define transmission_control_block_send(block)                      ((block)->func->send(block))
#define transmission_control_block_recv(block)                      ((block)->func->recv(block))
#define transmission_control_block_close(block)                     ((block)->func->close(block))

typedef int32_t (*transmission_control_protocol_context_handler_t)(transmission_control_protocol_module_t *, uint32_t, internet_protocol_context_t *, transmission_control_protocol_context_t *);

struct transmission_control_protocol_module {
    transmission_control_protocol_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;

    transmission_control_protocol_context_handler_t on;

    hashtable_t * block;
};

struct transmission_control_protocol_module_func {
    transmission_control_protocol_module_t * (*rem)(transmission_control_protocol_module_t *);
    int32_t (*deserialize)(transmission_control_protocol_module_t *, protocol_packet_t *, uint64_t, internet_protocol_context_t *, transmission_control_protocol_context_t **);
    int32_t (*serialize)(transmission_control_protocol_module_t *, internet_protocol_context_t *, transmission_control_protocol_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(transmission_control_protocol_module_t *, FILE *, transmission_control_protocol_context_t *);
    int32_t (*in)(transmission_control_protocol_module_t *, protocol_packet_t *, uint64_t, internet_protocol_context_t *, transmission_control_protocol_context_t **);
//    int32_t (*out)(transmission_control_protocol_module_t *, internet_protocol_context_t *, transmission_control_protocol_context_t *, protocol_packet_t **, uint64_t *);

    int32_t (*blockon)(transmission_control_protocol_module_t *, uint32_t, internet_protocol_context_t *, transmission_control_protocol_context_t *);
};

extern transmission_control_protocol_module_t * transmission_control_protocol_module_gen(protocol_module_map_t * map, transmission_control_protocol_context_handler_t on);
extern int32_t transmission_control_protocol_module_func_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_protocol_module_func_blockon(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

#define transmission_control_protocol_module_rem(module)                                                        ((module)->func->rem(module))
#define transmission_control_protocol_module_deserialize(module, packet, packetlen, parent, context)            ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define transmission_control_protocol_module_serialize(module, parent, context, packet, len)                    ((module)->func->serialize(module, parent, context, packet, len))
#define transmission_control_protocol_module_debug(module, stream, context)                                     ((module)->func->debug(module, stream, context))
#define transmission_control_protocol_module_in(module, packet, packetlen, parent, context)                     ((module)->func->in(module, packet, packetlen, parent, context))
#define transmission_control_protocol_module_blockon(module, type, parent, context)                             ((module)->func->blockon(module, type, parent, context))

#define transmission_control_protocol_module_on(module, type, parent, context)                                  ((module)->on(module, type, parent, context))

struct transmission_control_protocol_context {
    transmission_control_protocol_context_func_t * func;
    sync_t * sync;
    transmission_control_protocol_module_t * module;
    internet_protocol_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    transmission_control_protocol_packet_t * packet;
    uint64_t packetlen;
    internet_protocol_pseudo_t * pseudo;
    uint64_t pseudolen;

    uint16_t checksum;

    uint32_t headerlen;
    uint32_t datalen;

    transmission_control_protocol_option_t * option;
    uint8_t * data;

    hashtable_node_key_t key;
    transmission_control_block_t * block;
};

struct transmission_control_protocol_context_func {
    transmission_control_protocol_context_t * (*rem)(transmission_control_protocol_context_t *);
    int32_t (*valid)(transmission_control_protocol_context_t *);
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen);

extern int32_t transmission_control_protocol_context_key_gen(transmission_control_protocol_context_t * context);

#define transmission_control_protocol_context_rem(context)                      ((context)->func->rem(context))
#define transmission_control_protocol_context_valid(context)                    ((context)->func->valid(context))

#define transmission_control_protocol_context_error_get(context)                ((context)->error)
#define transmission_control_protocol_context_error_set(context, v)             ((context)->error = v)
#define transmission_control_protocol_context_packetlen_get(context)            ((context)->packetlen)
#define transmission_control_protocol_context_packetlen_set(context)            ((context)->packetlen = v)
#define transmission_control_protocol_context_headerlen_get(context)            ((context)->headerlen)
#define transmission_control_protocol_context_headerlen_set(context, v)         ((context)->headerlen = v)
#define transmission_control_protocol_context_datalen_get(context)              ((context)->datalen)
#define transmission_control_protocol_context_datalen_set(context, v)           ((context)->datalen = v)
#define transmission_control_protocol_context_checksumcal_get(context)          ((context)->checksum)
#define transmission_control_protocol_context_checksumcal_set(context, v)       ((context)->checksum =  v)
#define transmission_control_protocol_context_source_get(context)               (htons((context)->packet->source))
#define transmission_control_protocol_context_source_set(context, v)            ((context)->packet->source = ntohs(v))
#define transmission_control_protocol_context_destination_get(context)          (htons((context)->packet->destination))
#define transmission_control_protocol_context_destination_set(context, v)       ((context)->packet->destination = ntohs(v))
#define transmission_control_protocol_context_sequence_get(context)             (htonl((context)->packet->sequence))
#define transmission_control_protocol_context_sequence_set(context, v)          ((context)->packet->sequence = ntohl(v))
#define transmission_control_protocol_context_acknowledgment_get(context)       (htonl((context)->packet->acknowledgment))
#define transmission_control_protocol_context_acknowledgment_set(context, v)    ((context)->packet->acknowledgment = ntohl(v))
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
#define transmission_control_protocol_context_window_get(context)               (htons((context)->packet->window))
#define transmission_control_protocol_context_window_set(context, v)            ((context)->packet->window = ntohs(v))
#define transmission_control_protocol_context_checksum_get(context)             (htons((context)->packet->checksum))
#define transmission_control_protocol_context_checksum_set(context, v)          ((context)->packet->checksum = ntohs(v))
#define transmission_control_protocol_context_urgent_get(context)               (htons((context)->packet->pointer))
#define transmission_control_protocol_context_urgent_set(context, v)            ((context)->packet->pointer = ntohs(v))
#define transmission_control_protocol_context_option_get(context)               ((context)->option)
#define transmission_control_protocol_context_option_set(context, v)            ((context)->option = v)
#define transmission_control_protocol_context_data_get(context)                 ((context)->data)
#define transmission_control_protocol_context_data_set(context, v)              ((context)->data = v)

#define transmission_control_protocol_context_data_cal(context)                 (transmission_control_protocol_context_headerlen_get(context) == transmission_control_protocol_context_packetlen_get(context) ? nil : (&((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)]))
#define transmission_control_protocol_context_option_cal(context)               (transmission_control_protocol_context_headerlen_get(context) == (transmission_control_protocol_context_offset_get(context) * 4) ? nil : (&((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)]))

#define transmission_control_protocol_context_key_get(context)                  (address_of((context)->key))

#define transmission_control_protocol_context_key_has(context)                  ((context)->key.value != nil)

#endif // __SNORLAX__PROTOCOL_INTERNET_TRANSMISSION_CONTROL__H__
