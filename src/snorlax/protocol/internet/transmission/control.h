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
struct transmission_control_block_agent;
struct transmission_control_block_agent_func;

typedef hashtable_t transmission_control_block_map_t;

struct transmission_control_protocol_packet;
union transmission_control_protocol_address_pair;

struct transmission_control_protocol_module;
struct transmission_control_protocol_module_func;
struct transmission_control_protocol_context;
struct transmission_control_protocol_context_func;

typedef struct transmission_control_block               transmission_control_block_t;
typedef struct transmission_control_block_func          transmission_control_block_func_t;
typedef struct transmission_control_block_agent         transmission_control_block_agent_t;
typedef struct transmission_control_block_agent_func    transmission_control_block_agent_func_t;

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
    uint32_t acknowledge;
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t reserved:4;
    uint8_t offset:4;
    union {
        struct {
            uint8_t fin:1;
            uint8_t syn:1;
            uint8_t rst:1;
            uint8_t psh:1;
            uint8_t ack:1;
            uint8_t urg:1;
            uint8_t ece:1;
            uint8_t cwr:1;
        } bit;
        uint8_t flags;
    } control;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t offset:4;
    uint8_t reserved:4;
    union {
        uint8_t flags;
        struct {
            uint8_t cwr:1;
            uint8_t ece:1;
            uint8_t urg:1;
            uint8_t ack:1;
            uint8_t psh:1;
            uint8_t rst:1;
            uint8_t syn:1;
            uint8_t fin:1;
        } bit;
    } control;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint16_t window;
    uint16_t checksum;
    uint16_t pointer;
};

// 필요한지 고민해보자.
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

extern uint8_t * transmission_control_protocol_packet_reserve_header(uint8_t * buffer, uint64_t * bufferlen);

extern int32_t transmission_control_protocol_address_pair_init(transmission_control_protocol_address_pair_t * pair, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
extern uint16_t transmission_control_protocol_checksum_cal(transmission_control_protocol_packet_t * segment, uint64_t segmentlen, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen);

#define transmission_control_protocol_packet_length_min                     20

#define transmission_control_protocol_option_type_end                       0
#define transmission_control_protocol_option_type_no_operation              1
#define transmission_control_protocol_option_type_maximum_segment_size      2

#define transmission_control_protocol_option_length_get(option)             ((*(option) == 0 || *(option) == 1) ? 1 : *(option)[1])

#define transmission_control_protocol_to_port(addr)                         (*((uint16_t *) (addr)))

struct transmission_control_block_agent {
    transmission_control_block_agent_func_t * func;
    sync_t * sync;

    ___reference transmission_control_block_t * block;
};

struct transmission_control_block_agent_func {
    transmission_control_block_agent_t * (*rem)(transmission_control_block_agent_t *);

    int32_t (*open)(transmission_control_block_agent_t *);
    int32_t (*send)(transmission_control_block_agent_t *);
    int32_t (*recv)(transmission_control_block_agent_t *);
    int32_t (*close)(transmission_control_block_agent_t *);
};

#define transmission_control_block_agent_rem(agent)             ((agent)->func->rem(agent))
#define transmission_control_block_agent_open(agent)            ((agent)->func->open(agent))
#define transmission_control_block_agent_send(agent)            ((agent)->func->send(agent))
#define transmission_control_block_agent_recv(agent)            ((agent)->func->recv(agent))
#define transmission_control_block_agent_close(agent)           ((agent)->func->close(agent))

/**
 * Inherited hashtable_node_t
 */
struct transmission_control_block {
    transmission_control_block_func_t * func;
    sync_t * sync;
    hashtable_list_t * collection;
    hashtable_node_t * prev;
    hashtable_node_t * next;
    hashtable_node_key_t key;

    protocol_path_t * path;

    uint8_t version;
    uint32_t state;
    uint32_t sequence;
    uint32_t acknowledge;
    uint16_t window;

    transmission_control_block_agent_t * agent;
};

struct transmission_control_block_func {
    transmission_control_block_t * (*rem)(transmission_control_block_t *);

    int32_t (*open)(transmission_control_block_t *);
    int32_t (*send)(transmission_control_block_t *);
    int32_t (*recv)(transmission_control_block_t *);
    int32_t (*close)(transmission_control_block_t *);
    int32_t (*listen)(transmission_control_block_t *);
};

#define transmission_control_block_state_get(block)                 ((block)->state)
#define transmission_control_block_state_set(block, v)              ((block)->state = v)

#define transmission_control_window_size_init                       (65536 / 2)

#define transmission_control_state_none                             0
#define transmission_control_state_listen                           1
#define transmission_control_state_syn_sent                         2
#define transmission_control_state_syn_rcvd                         3
#define transmission_control_state_est                              4
#define transmission_control_state_fin_wait_1                       5
#define transmission_control_state_fin_wait_2                       6
#define transmission_control_state_close_wait                       7
#define transmission_control_state_closing                          8
#define transmission_control_state_last_ack                         9
#define transmission_control_state_time_wait                        10
#define transmission_control_state_closed                           0

#define transmission_control_flag_control_cwr                       (0x01u << 7u)
#define transmission_control_flag_control_ece                       (0x01u << 6u)
#define transmission_control_flag_control_urg                       (0x01u << 5u)
#define transmission_control_flag_control_ack                       (0x01u << 4u)
#define transmission_control_flag_control_psh                       (0x01u << 3u)
#define transmission_control_flag_control_rst                       (0x01u << 2u)
#define transmission_control_flag_control_syn                       (0x01u << 1u)
#define transmission_control_flag_control_fin                       (0x01u << 0u)

#define transmission_control_flag_control_synack                    (transmission_control_flag_control_syn | transmission_control_flag_control_ack)

#define transmission_control_protocol_header_len                    20

extern transmission_control_block_t * transmission_control_block_gen(hashtable_node_key_t * key);

extern transmission_control_protocol_context_t * transmission_control_block_context_gen_connect_synack(transmission_control_block_t * block, uint8_t * buffer, uint64_t bufferlen);

#define transmission_control_block_sequence_set(block, v)           ((block)->sequence = v)
#define transmission_control_block_sequence_get(block)              ((block)->sequence)
#define transmission_control_block_acknowledge_set(block, v)        ((block)->acknowledge = v)
#define transmission_control_block_acknowledge_get(block)           ((block)->acknowledge)
#define transmission_control_block_window_set(block, v)             ((block)->window = v)
#define transmission_control_block_window_get(block)                ((block)->window)
#define transmission_control_block_version_set(block, v)            ((block)->version = v)
#define transmission_control_block_version_get(block)               ((block)->version)

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
    uint16_t type;
    uint16_t addrlen;
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
    int32_t (*out)(transmission_control_protocol_module_t *, protocol_path_node_t *, protocol_context_t *);
    transmission_control_protocol_context_t * (*context_gen)(transmission_control_protocol_module_t *, protocol_path_node_t *, protocol_context_t *);
    transmission_control_protocol_context_t * (*reply_gen)(transmission_control_protocol_module_t *, transmission_control_protocol_context_t *);

    int32_t (*blockon)(transmission_control_protocol_module_t *, uint32_t, internet_protocol_context_t *, transmission_control_protocol_context_t *);
    uint32_t (*sequence_gen)(transmission_control_protocol_module_t *, internet_protocol_context_t *, transmission_control_protocol_context_t *);
};

extern transmission_control_protocol_module_t * transmission_control_protocol_module_gen(protocol_module_map_t * map, transmission_control_protocol_context_handler_t on);
extern int32_t transmission_control_protocol_module_func_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_protocol_module_func_blockon(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

extern uint32_t transmission_control_protocol_module_func_sequence_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

#define transmission_control_protocol_module_addrlen_get(module)                                                ((module)->addrlen)

#define transmission_control_protocol_module_rem(module)                                                        ((module)->func->rem(module))
#define transmission_control_protocol_module_deserialize(module, packet, packetlen, parent, context)            ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define transmission_control_protocol_module_serialize(module, parent, context, packet, len)                    ((module)->func->serialize(module, parent, context, packet, len))
#define transmission_control_protocol_module_debug(module, stream, context)                                     ((module)->func->debug(module, stream, context))
#define transmission_control_protocol_module_in(module, packet, packetlen, parent, context)                     ((module)->func->in(module, packet, packetlen, parent, context))
#define transmission_control_protocol_module_out(module, node, child)                                           ((module)->func->out(module, node, child))
#define transmission_control_protocol_module_context_gen(module, node, child)                                   ((module)->func->context_gen(module, node, child))
#define transmission_control_protocol_module_reply_gen(module, request)                                         ((module)->func->reply_gen(module, request))

#define transmission_control_protocol_module_blockon(module, type, parent, context)                             ((module)->func->blockon(module, type, parent, context))
#define transmission_control_protocol_module_seqeuence_gen(module, parent, context)                             ((module)->func->sequence_gen(module, parent, context))
// #define transmission_control_protocol_module_blockon(module, parent, context)                                   ((module)->func->blockon(module, parent, context))

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
    uint64_t bufferlen;

    internet_protocol_pseudo_t * pseudo;
    uint64_t pseudolen;

    uint16_t checksum;

    uint32_t headerlen;
    uint32_t datalen;

    transmission_control_protocol_option_t * option;
    uint8_t * data;

    hashtable_node_key_t key;                                   // 중복적으로 키가 발생한다. 불필요한 공간인가? 아니면 조금 더 메모리를 줄일 수 있는가?
    transmission_control_block_t * block;
};

struct transmission_control_protocol_context_func {
    transmission_control_protocol_context_t * (*rem)(transmission_control_protocol_context_t *);
    int32_t (*valid)(transmission_control_protocol_context_t *);
    uint8_t * (*addrptr)(transmission_control_protocol_context_t *, uint32_t);
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen, uint64_t bufferlen);

extern int32_t transmission_control_protocol_context_key_gen(transmission_control_protocol_context_t * context);
extern uint32_t transmission_control_protocol_direction_cal(transmission_control_protocol_context_t * context);

extern int32_t transmission_control_protocol_context_is_connect_syn(transmission_control_protocol_context_t * context);
extern int32_t transmssion_control_protocol_context_is_accept_syn(transmission_control_protocol_context_t * context);

// extern void transmission_control_protocol_context_func_buffer_reserve(transmission_control_protocol_context_t * context, uint64_t n);

#define transmission_control_protocol_context_buffer_reserve(context, n)        (protocol_context_buffer_reserve_reversal((protocol_context_t *) (context), n))

#define transmission_control_protocol_context_rem(context)                      ((context)->func->rem(context))
#define transmission_control_protocol_context_valid(context)                    ((context)->func->valid(context))
#define transmission_control_protocol_context_addrptr(context, type)            ((context)->func->addrptr(context, type))

#define transmission_control_protocol_context_bufferlen_set(context, len)       ((context)->bufferlen = len)
#define transmission_control_protocol_context_bufferlen_get(context)            ((context)->bufferlen)

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
#define transmission_control_protocol_context_source_get(context)               (ntohs((context)->packet->source))
#define transmission_control_protocol_context_source_set(context, v)            ((context)->packet->source = htons(v))
#define transmission_control_protocol_context_destination_get(context)          (ntohs((context)->packet->destination))
#define transmission_control_protocol_context_destination_set(context, v)       ((context)->packet->destination = htons(v))
#define transmission_control_protocol_context_sequence_get(context)             (ntohl((context)->packet->sequence))
#define transmission_control_protocol_context_sequence_set(context, v)          ((context)->packet->sequence = htonl(v))
#define transmission_control_protocol_context_acknowledge_get(context)          (ntohl((context)->packet->acknowledge))
#define transmission_control_protocol_context_acknowledge_set(context, v)       ((context)->packet->acknowledge = htonl(v))
#define transmission_control_protocol_context_offset_get(context)               ((context)->packet->offset)
#define transmission_control_protocol_context_offset_set(context, v)            ((context)->packet->offset = v)
#define transmission_control_protocol_context_cwr_get(context)                  ((context)->packet->control.bit.cwr)
#define transmission_control_protocol_context_cwr_on(context)                   ((context)->packet->control.bit.cwr = 1)
#define transmission_control_protocol_context_cwr_off(context)                  ((context)->packet->control.bit.cwr = 0)
#define transmission_control_protocol_context_ece_get(context)                  ((context)->packet->control.bit.ece)
#define transmission_control_protocol_context_ece_on(context)                   ((context)->packet->control.bit.ece = 1)
#define transmission_control_protocol_context_ece_off(context)                  ((context)->packet->control.bit.ece = 0)
#define transmission_control_protocol_context_urg_get(context)                  ((context)->packet->control.bit.urg)
#define transmission_control_protocol_context_urg_on(context)                   ((context)->packet->control.bit.urg = 1)
#define transmission_control_protocol_context_urg_off(context)                  ((context)->packet->control.bit.urg = 0)
#define transmission_control_protocol_context_ack_get(context)                  ((context)->packet->control.bit.ack)
#define transmission_control_protocol_context_ack_on(context)                   ((context)->packet->control.bit.ack = 1)
#define transmission_control_protocol_context_ack_off(context)                  ((context)->packet->control.bit.ack = 0)
#define transmission_control_protocol_context_psh_get(context)                  ((context)->packet->control.bit.psh)
#define transmission_control_protocol_context_psh_on(context)                   ((context)->packet->control.bit.psh = 1)
#define transmission_control_protocol_context_psh_off(context)                  ((context)->packet->control.bit.psh = 0)
#define transmission_control_protocol_context_rst_get(context)                  ((context)->packet->control.bit.rst)
#define transmission_control_protocol_context_rst_on(context)                   ((context)->packet->control.bit.rst = 1)
#define transmission_control_protocol_context_rst_off(context)                  ((context)->packet->control.bit.rst = 0)
#define transmission_control_protocol_context_syn_get(context)                  ((context)->packet->control.bit.syn)
#define transmission_control_protocol_context_syn_on(context)                   ((context)->packet->control.bit.syn = 1)
#define transmission_control_protocol_context_syn_off(context)                  ((context)->packet->control.bit.syn = 0)
#define transmission_control_protocol_context_fin_get(context)                  ((context)->packet->control.bit.fin)
#define transmission_control_protocol_context_fin_on(context)                   ((context)->packet->control.bit.fin = 1)
#define transmission_control_protocol_context_fin_off(context)                  ((context)->packet->control.bit.fin = 0)
#define transmission_control_protocol_context_flags_get(context)                ((context)->packet->control.flags)
#define transmission_control_protocol_context_flags_set(context, v)             ((context)->packet->control.flags = v)
#define transmission_control_protocol_context_window_get(context)               (ntohs((context)->packet->window))
#define transmission_control_protocol_context_window_set(context, v)            ((context)->packet->window = htons(v))
#define transmission_control_protocol_context_checksum_get(context)             (ntohs((context)->packet->checksum))
#define transmission_control_protocol_context_checksum_set(context, v)          ((context)->packet->checksum = htons(v))
#define transmission_control_protocol_context_urgent_get(context)               (ntohs((context)->packet->pointer))
#define transmission_control_protocol_context_urgent_set(context, v)            ((context)->packet->pointer = htons(v))
#define transmission_control_protocol_context_option_get(context)               ((context)->option)
#define transmission_control_protocol_context_option_set(context, v)            ((context)->option = v)
#define transmission_control_protocol_context_data_get(context)                 ((context)->data)
#define transmission_control_protocol_context_data_set(context, v)              ((context)->data = v)

#define transmission_control_protocol_context_block_set(context, v)             ((context)->block = v)
#define transmission_control_protocol_context_block_get(context)                ((context)->block)

#define transmission_control_protocol_context_data_cal(context)                 (transmission_control_protocol_context_headerlen_get(context) == transmission_control_protocol_context_packetlen_get(context) ? nil : (&((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)]))
#define transmission_control_protocol_context_option_cal(context)               (transmission_control_protocol_context_headerlen_get(context) == (transmission_control_protocol_context_offset_get(context) * 4) ? nil : (&((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)]))

#define transmission_control_protocol_context_key_get(context)                  (address_of((context)->key))

#define transmission_control_protocol_context_key_has(context)                  ((context)->key.value != nil)

#endif // __SNORLAX__PROTOCOL_INTERNET_TRANSMISSION_CONTROL__H__
