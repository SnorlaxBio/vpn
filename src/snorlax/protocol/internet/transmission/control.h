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
#include <snorlax/nanosecond.h>
#include <snorlax/buffer/list.h>
#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

#include <snorlax/socket.h>
#include <snorlax/socket/event/subscription.h>
#include <snorlax/socket/client.h>
#include <snorlax/socket/client/event/subscription.h>

struct transmission_control_block;
struct transmission_control_block_func;
struct transmission_control_block_agent;
struct transmission_control_block_agent_func;
struct transmission_control_block_client;
struct transmission_control_block_client_func;
struct transmission_control_block_buffer_in;
struct transmission_control_block_buffer_in_func;
struct transmission_control_block_buffer_in_node;
struct transmission_control_block_buffer_in_node_func;
struct transmission_control_block_buffer_out;
struct transmission_control_block_buffer_out_func;
struct transmission_control_block_buffer_out_node;
struct transmission_control_block_buffer_out_node_func;

typedef hashtable_t transmission_control_block_map_t;

struct transmission_control_protocol_packet;

struct transmission_control_protocol_module;
struct transmission_control_protocol_module_func;
struct transmission_control_protocol_context;
struct transmission_control_protocol_context_func;

typedef struct transmission_control_block                           transmission_control_block_t;
typedef struct transmission_control_block_func                      transmission_control_block_func_t;
typedef struct transmission_control_block_agent                     transmission_control_block_agent_t;
typedef struct transmission_control_block_agent_func                transmission_control_block_agent_func_t;
typedef struct transmission_control_block_client                    transmission_control_block_client_t;
typedef struct transmission_control_block_client_func               transmission_control_block_client_func_t;
typedef struct transmission_control_block_buffer_in                 transmission_control_block_buffer_in_t;
typedef struct transmission_control_block_buffer_in_func            transmission_control_block_buffer_in_func_t;
typedef struct transmission_control_block_buffer_in_node            transmission_control_block_buffer_in_node_t;
typedef struct transmission_control_block_buffer_in_node_func       transmission_control_block_buffer_in_node_func_t;

typedef struct transmission_control_block_buffer_out                transmission_control_block_buffer_out_t;
typedef struct transmission_control_block_buffer_out_func           transmission_control_block_buffer_out_func_t;
typedef struct transmission_control_block_buffer_out_node           transmission_control_block_buffer_out_node_t;
typedef struct transmission_control_block_buffer_out_node_func      transmission_control_block_buffer_out_node_func_t;

typedef struct transmission_control_protocol_packet                 transmission_control_protocol_packet_t;
typedef uint8_t                                                     transmission_control_protocol_option_t;

typedef struct transmission_control_protocol_module                 transmission_control_protocol_module_t;
typedef struct transmission_control_protocol_module_func            transmission_control_protocol_module_func_t;
typedef struct transmission_control_protocol_context                transmission_control_protocol_context_t;
typedef struct transmission_control_protocol_context_func           transmission_control_protocol_context_func_t;

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


extern uint8_t * transmission_control_protocol_packet_reserve_header(uint8_t * buffer, uint64_t * bufferlen);

extern uint16_t transmission_control_protocol_checksum_cal(transmission_control_protocol_packet_t * segment, uint64_t segmentlen, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen);

#define transmission_control_protocol_default_max_segment_size              1024

#define transmission_control_protocol_packet_length_min                     20

#define transmission_control_protocol_option_type_end                       0
#define transmission_control_protocol_option_type_no_operation              1
#define transmission_control_protocol_option_type_maximum_segment_size      2

#define transmission_control_protocol_option_length_get(option)             ((*(option) == 0 || *(option) == 1) ? 1 : *(option)[1])

#define transmission_control_protocol_to_port(addr)                         (*((uint16_t *) (addr)))

#define transmission_control_block_agent_event_type_subscription    0
#define transmission_control_block_agent_event_type_open            1
#define transmission_control_block_agent_event_type_read            2
#define transmission_control_block_agent_event_type_write           3
#define transmission_control_block_agent_event_type_close           4
#define transmission_control_block_agent_event_type_exception       5
#define transmission_control_block_agent_event_type_in              6
#define transmission_control_block_agent_event_type_out             7
#define transmission_control_block_agent_event_type_max             8

typedef void (*transmission_control_block_agent_handler_t)(transmission_control_block_agent_t *, uint32_t, void *);

struct transmission_control_block_agent {
    transmission_control_block_agent_func_t * func;
    sync_t * sync;
    ___reference transmission_control_block_t * block;
    socket_event_subscription_t * subscription;
    transmission_control_block_agent_handler_t on;
};

/**
 * TODO: ### 20240825 | transmission_control_block_agent::open
 * TODO: ### 20240825 | transmission_control_block_agent::recv
 * TODO: ### 20240825 | transmission_control_block_agent::close
 * TODO: ### 20240825 | transmission_control_block_agent::shutdown
 * TODO: ### 20240825 | transmission_control_block_agent::in
 * TODO: ### 20240825 | transmission_control_block_agent::out
 */
struct transmission_control_block_agent_func {
    transmission_control_block_agent_t * (*rem)(transmission_control_block_agent_t *);

    int32_t (*open)(transmission_control_block_agent_t *);
    int64_t (*send)(transmission_control_block_agent_t *, transmission_control_block_buffer_out_node_t *, transmission_control_block_buffer_out_node_t *);
    int64_t (*recv)(transmission_control_block_agent_t *);
    int32_t (*close)(transmission_control_block_agent_t *);
    int32_t (*shutdown)(transmission_control_block_agent_t *, uint32_t);

    int32_t (*in)(transmission_control_block_agent_t *, transmission_control_protocol_context_t *);
    int32_t (*out)(transmission_control_block_agent_t *);
};

#define transmission_control_block_agent_rem(agent)                 ((agent)->func->rem(agent))
#define transmission_control_block_agent_open(agent)                ((agent)->func->open(agent))
#define transmission_control_block_agent_send(agent)                ((agent)->func->send(agent))
#define transmission_control_block_agent_recv(agent)                ((agent)->func->recv(agent))
#define transmission_control_block_agent_close(agent)               ((agent)->func->close(agent))
#define transmission_control_block_agent_shutdown(agent, how)       ((agent)->func->shutdown(agent, how))
#define transmission_control_block_agent_in(agent, context)         ((agent)->func->in(agent, context))

typedef socket_client_t * (*socket_client_factory_t)(int32_t, int32_t, int32_t, void *, uint64_t);    // TODO: MOVE 
typedef void (*transmission_control_block_client_handler_t)(transmission_control_block_client_t *, uint32_t, void *);

struct transmission_control_block_client {
    transmission_control_block_client_func_t * func;
    sync_t * sync;
    ___reference transmission_control_block_t * block;
    socket_client_event_subscription_t * subscription;
    transmission_control_block_client_handler_t on;
};

struct transmission_control_block_client_func {
    transmission_control_block_client_t * (*rem)(transmission_control_block_client_t *);

    int32_t (*open)(transmission_control_block_client_t *, socket_client_factory_t, event_engine_t *);
    int64_t (*send)(transmission_control_block_client_t *, transmission_control_block_buffer_out_node_t *, transmission_control_block_buffer_out_node_t *);
    int64_t (*recv)(transmission_control_block_client_t *);
    int32_t (*close)(transmission_control_block_client_t *);
    int32_t (*shutdown)(transmission_control_block_client_t *, uint32_t);

    int32_t (*in)(transmission_control_block_client_t *, transmission_control_protocol_context_t *);
    int32_t (*out)(transmission_control_block_client_t *);
};


extern socket_client_event_subscription_handler_t * transmission_control_block_client_handler_get(void);

extern transmission_control_block_client_t * transmission_control_block_client_gen(___notnull transmission_control_block_t * block, transmission_control_block_client_handler_t on);

#define transmission_control_block_client_rem(agent)                    ((agent)->func->rem(agent))
#define transmission_control_block_client_open(agent, gen, engine)      ((agent)->func->open(agent, gen, engine))
#define transmission_control_block_client_send(agent)                   ((agent)->func->send(agent))
#define transmission_control_block_client_recv(agent)                   ((agent)->func->recv(agent))
#define transmission_control_block_client_close(agent)                  ((agent)->func->close(agent))
#define transmission_control_block_client_shutdown(agent, how)          ((agent)->func->shutdown(agent, how))
#define transmission_control_block_client_in(agent, context)            ((agent)->func->in(agent, context))

#define transmission_control_block_client_on(agent, type, node)         ((agent)->on ? ((agent)->on(agent, type, node), success) : ((agent)->on(agent, type, node), fail))

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
    transmission_control_protocol_module_t * module;

    uint8_t version;
    struct {
        uint16_t prev;
        uint16_t current;
    } state;
    uint32_t sequence;
    uint32_t acknowledge;
    uint16_t window;
    struct {
        uint32_t sequence;
        uint32_t acknowledge;
        uint16_t window;
    } remote;

    struct {
        transmission_control_block_buffer_in_t * in;       // HOLE 을 지원하는 버퍼를 만들고, 한 번에 SEND 하도록 혹은 버퍼 노드 교체만 이루어지도록 ,...
        transmission_control_block_buffer_out_t * out;      // SEGMENT 크기로 자를 수 있는 버퍼, 하나의 의미 있는 IP 패킷을 담는다.
    } buffer;
    
    transmission_control_block_agent_t * agent;
};

struct transmission_control_block_func {
    transmission_control_block_t * (*rem)(transmission_control_block_t *);

    int32_t (*open)(transmission_control_block_t *);
    int32_t (*send)(transmission_control_block_t *, const uint8_t *, uint64_t);
    int32_t (*recv)(transmission_control_block_t *);
    int32_t (*close)(transmission_control_block_t *);
    int32_t (*listen)(transmission_control_block_t *);

    int32_t (*in)(transmission_control_block_t *, transmission_control_protocol_context_t *);
    int32_t (*complete_in)(transmission_control_block_t *, transmission_control_protocol_context_t *);
    
    int32_t (*out)(transmission_control_block_t *, transmission_control_block_buffer_out_node_t *);
};

extern int32_t transmission_control_block_in_closed(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_listen(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_synchronize_sequence_sent(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_synchronize_sequence_recv(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_establish(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_finish_wait_first(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_finish_wait_second(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_close_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_closing(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_last_acknowledge(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_time_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_in_exception(transmission_control_block_t * block, transmission_control_protocol_context_t * context);

extern int32_t transmission_control_block_complete_in_closed(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_listen(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_synchronize_sequence_sent(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_synchronize_sequence_recv(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_establish(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_finish_wait_first(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_finish_wait_second(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_close_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_closing(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_last_acknowledge(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_time_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
extern int32_t transmission_control_block_complete_in_exception(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_event_in_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_event_out_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_event_exception_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_event_complete_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_event_complete_in_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_event_complete_out_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_event_none_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

// extern int32_t transmission_control_block_state_listen_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_synchronize_sequence_sent_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_synchronize_sequence_recv_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_establish_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_finish_wait_frist_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_finish_wait_second_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_close_wait_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_closing_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_last_acknowledge_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_time_wait_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_closed_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_exception_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

// extern int32_t transmission_control_block_state_listen_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_synchronize_sequence_sent_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_synchronize_sequence_recv_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_establish_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_finish_wait_frist_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_finish_wait_second_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_close_wait_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_closing_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_last_acknowledge_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_time_wait_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_closed_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
// extern int32_t transmission_control_block_state_exception_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

#define transmission_control_window_size_init                       (65536 / 2)

#define transmission_control_state_avail_in                         (0x8000u)
#define transmission_control_state_avail_out                        (0x4000u)
#define transmission_control_state_avail_accept                     (0x2000u)
#define transmission_control_state_finishing                        (0x1000u)
#define transmission_control_state_avail_io                         (transmission_control_state_avail_in | transmission_control_state_avail_out)

#define transmission_control_state_closed                           (transmission_control_state_finishing    |  0)
#define transmission_control_state_listen                           (transmission_control_state_avail_accept |  1)
#define transmission_control_state_synchronize_sequence_sent        (transmission_control_state_avail_io     |  2)
#define transmission_control_state_synchronize_sequence_recv        (transmission_control_state_avail_io     |  3)
#define transmission_control_state_establish                        (transmission_control_state_avail_io     |  4)
#define transmission_control_state_finish_wait_first                (transmission_control_state_finishing    |  5)
#define transmission_control_state_finish_wait_second               (transmission_control_state_finishing    |  6)
#define transmission_control_state_close_wait                       (transmission_control_state_finishing    |  7)
#define transmission_control_state_closing                          (transmission_control_state_finishing    |  8)
#define transmission_control_state_last_acknowledge                 (transmission_control_state_finishing    |  9)
#define transmission_control_state_time_wait                        (transmission_control_state_finishing    | 10)

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

extern transmission_control_block_t * transmission_control_block_gen(hashtable_node_key_t * key, transmission_control_protocol_module_t * module);

extern int32_t transmission_control_block_func_number_update(uint32_t * field, uint32_t no, uint32_t n);        // @deprecated

extern transmission_control_protocol_context_t * transmission_control_block_context_gen_connect_synack(transmission_control_block_t * block, uint8_t * buffer, uint64_t bufferlen);

// ___implement extern transmission_control_protocol_context_t * transmission_control_block_func_context_gen_transmit_segment(transmission_control_block_t * block, transmission_control_block_buffer_node_t * node, uint8_t flags, uint8_t * buffer, uint64_t bufferlen);
// ___implement extern int32_t transmission_control_block_func_check_window_remote(transmission_control_block_t * block, transmission_control_block_buffer_node_t * node);

#define transmission_control_block_sequence_set(block, v)               ((block)->sequence = v)
#define transmission_control_block_sequence_get(block)                  ((block)->sequence)
#define transmission_control_block_acknowledge_set(block, v)            ((block)->acknowledge = v)
#define transmission_control_block_acknowledge_get(block)               ((block)->acknowledge)

#define transmission_control_block_remote_sequence_set(block, v)        ((block)->remote.sequence = v)
#define transmission_control_block_remote_sequence_get(block)           ((block)->remote.sequence)
#define transmission_control_block_remote_acknowledge_set(block, v)     ((block)->remote.acknowledge = v)
#define transmission_control_block_remote_acknowledge_get(block)        ((block)->remote.acknowledge)
#define transmission_control_block_remote_window_set(block, v)          ((block)->remote.window = v)
#define transmission_control_block_remote_window_get(block)             ((block)->remote.window)
#define transmission_control_block_window_set(block, v)                 ((block)->window = v)
#define transmission_control_block_window_get(block)                    ((block)->window)
#define transmission_control_block_version_set(block, v)                ((block)->version = v)
#define transmission_control_block_version_get(block)                   ((block)->version)
#define transmission_control_block_state_get(block)                     ((block)->state.current)
#define transmission_control_block_state_set(block, v)                  ((block)->state.current = v)
#define transmission_control_block_state_has(block, v)                  ((block)->state.current & v)
#define transmission_control_block_state_prev_get(block)                ((block)->state.prev)
#define transmission_control_block_state_prev_set(block, v)             ((block)->state.prev = v)
#define transmission_control_block_state_is_changed(block)              ((block)->state.prev != (block)->state.current)
#define transmission_control_block_path_set(block, v)                   ((block)->path = v)
#define transmission_control_block_path_get(block)                      ((block)->path)
#define transmission_control_block_agent_set(block, v)                  ((block)->agent = v)
#define transmission_control_block_agent_get(block)                     ((block)->agent)

#define transmission_control_block_avail_io(block)                      (transmission_control_block_state_get(block) & transmission_control_state_avail_io)
#define transmission_control_block_avail_in(block)                      (transmission_control_block_state_get(block) & transmission_control_state_avail_in)
#define transmission_control_block_avail_out(block)                     (transmission_control_block_state_get(block) & transmission_control_state_avail_out)
#define transmission_control_block_is_finishing(block)                  (transmission_control_block_state_get(block) & transmission_control_state_finishing)

#define transmission_control_block_func_hash                            internet_protocol_version_hash

#define transmission_control_block_rem(block)                           ((block)->func->rem(block))
#define transmission_control_block_open(block)                          ((block)->func->open(block))
#define transmission_control_block_send(block, data, datalen)           ((block)->func->send(block, data, datalen))
#define transmission_control_block_recv(block, context)                 ((block)->func->recv(block, context))
#define transmission_control_block_close(block)                         ((block)->func->close(block))
#define transmission_control_block_in(block, context)                   ((block)->func->in(block, context))
#define transmission_control_block_complete_in(block, context)          ((block)->func->complete_in(block, context))
#define transmission_control_block_out(block, node)                     ((block)->func->out(block, node))

#define transmission_control_block_check_window_remote                  transmission_control_block_func_check_window_remote
#define transmission_control_block_context_gen_transmit_segment         transmission_control_block_func_context_gen_transmit_segment

typedef transmission_control_block_buffer_out_node_t * (*transmission_control_block_buffer_out_node_factory_t)(transmission_control_block_buffer_out_t *, const void *, uint64_t);

struct transmission_control_block_buffer_out {
    transmission_control_block_buffer_out_func_t * func;
    sync_t * sync;
    uint64_t size;
    transmission_control_block_buffer_out_node_t * head;
    transmission_control_block_buffer_out_node_t * tail;
    transmission_control_block_buffer_out_node_t * front;

    uint64_t page;
    transmission_control_block_buffer_out_node_factory_t nodegen;
};

struct transmission_control_block_buffer_out_func {
    transmission_control_block_buffer_out_t * (*rem)(transmission_control_block_buffer_out_t *);
    void (*push)(transmission_control_block_buffer_out_t *, const void *, uint64_t);
    void (*pop)(transmission_control_block_buffer_out_t *, uint64_t);
    void (*clear)(transmission_control_block_buffer_out_t *);
    void (*shrink)(transmission_control_block_buffer_out_t *);
    transmission_control_block_buffer_out_node_t * (*front)(transmission_control_block_buffer_out_t *);
    transmission_control_block_buffer_out_node_t * (*back)(transmission_control_block_buffer_out_t *, uint64_t);
    transmission_control_block_buffer_out_node_t * (*head)(transmission_control_block_buffer_out_t *);

    transmission_control_block_buffer_out_node_t * (*add)(transmission_control_block_buffer_out_t *, transmission_control_block_buffer_out_node_t *);
    transmission_control_block_buffer_out_node_t * (*del)(transmission_control_block_buffer_out_t *, transmission_control_block_buffer_out_node_t *);
};

extern transmission_control_block_buffer_out_t * transmission_control_block_buffer_out_gen(transmission_control_block_buffer_out_node_factory_t nodegen, uint64_t page);

extern void transmission_control_block_buffer_out_func_transmit_on(transmission_control_block_buffer_out_t * buffer, transmission_control_block_buffer_out_node_t * node);

#define transmission_control_block_buffer_out_rem(buffer)                           ((buffer)->func->rem(buffer))
#define transmission_control_block_buffer_out_push(buffer, data, n)                 ((buffer)->func->push(buffer, data, n))
#define transmission_control_block_buffer_out_pop(buffer, n)                        ((buffer)->func->pop(buffer, n))
#define transmission_control_block_buffer_out_clear(buffer)                         ((buffer)->func->clear(buffer))
#define transmission_control_block_buffer_out_front(buffer)                         ((buffer)->func->front(buffer))
#define transmission_control_block_buffer_out_back(buffer, hint)                    ((buffer)->func->back(buffer, hint))
#define transmission_control_block_buffer_out_add(buffer, node)                     ((buffer)->func->add(buffer, node))
#define transmission_control_block_buffer_out_del(buffer, node)                     ((buffer)->func->del(buffer, node))

#define transmission_control_block_buffer_out_nodegen(buffer, data, n)              ((buffer)->nodegen(buffer, data, n))

#define transmission_control_block_buffer_out_transmit_on                           transmission_control_block_buffer_func_transmit_on

#define transmission_control_block_buffer_out_head(buffer)                          ((buffer)->head)
#define transmission_control_block_buffer_out_tail(buffer)                          ((buffer)->tail)

struct transmission_control_block_buffer_out_node {
    transmission_control_block_buffer_out_node_func_t * func;
    sync_t * sync;
    buffer_list_t * collection;
    transmission_control_block_buffer_out_node_t * prev;
    transmission_control_block_buffer_out_node_t * next;
    uint64_t position;
    uint64_t size;
    uint64_t capacity;
    void * mem;

    ___reference uint8_t * segment;
    uint32_t sequence;              // @deprecated
    uint32_t acknowledge;           // @deprecated

    struct {
        nanosecond_t time;
        uint8_t count;
    } transmit;

    nanosecond_t time;
};

struct transmission_control_block_buffer_out_node_func {
    transmission_control_block_buffer_out_node_t * (*rem)(transmission_control_block_buffer_out_node_t *);
    void * (*front)(transmission_control_block_buffer_out_node_t *);
    void * (*back)(transmission_control_block_buffer_out_node_t *);
    int32_t (*shrink)(transmission_control_block_buffer_out_node_t *);
    uint64_t (*length)(transmission_control_block_buffer_out_node_t *);
    uint64_t (*remain)(transmission_control_block_buffer_out_node_t *);
    uint64_t (*position_get)(transmission_control_block_buffer_out_node_t *);
    void (*position_set)(transmission_control_block_buffer_out_node_t *, uint64_t);
    uint64_t (*size_get)(transmission_control_block_buffer_out_node_t *);
    void (*size_set)(transmission_control_block_buffer_out_node_t *, uint64_t);
    uint64_t (*capacity_get)(transmission_control_block_buffer_out_node_t *);
    void (*capacity_set)(transmission_control_block_buffer_out_node_t *, uint64_t);
    void (*clear)(transmission_control_block_buffer_out_node_t *);
};

extern transmission_control_block_buffer_out_node_t * transmission_control_block_buffer_out_node_gen(transmission_control_block_buffer_out_t * buffer, const void * data, uint64_t n);

#define transmission_control_block_buffer_out_node_rem(node)                            ((node)->func->rem(node))
#define transmission_control_block_buffer_out_node_front(node)                          ((node)->func->front(node))
#define transmission_control_block_buffer_out_node_back(node)                           ((node)->func->back(node))
#define transmission_control_block_buffer_out_node_shrink(node)                         ((node)->func->shrink(node))
#define transmission_control_block_buffer_out_node_length(node)                         ((node) ? (node)->func->length(node) : 0)
#define transmission_control_block_buffer_out_node_remain(node)                         ((node) ? (node)->func->remain(node) : 0)
#define transmission_control_block_buffer_out_node_position_get(node)                   ((node)->func->position_get(node))
#define transmission_control_block_buffer_out_node_position_set(node, n)                ((node)->func->position_set(node, n))
#define transmission_control_block_buffer_out_node_size_get(node)                       ((node)->func->size_get(node))
#define transmission_control_block_buffer_out_node_size_set(node, n)                    ((node)->func->size_set(node, n))
#define transmission_control_block_buffer_out_node_capacity_get(node)                   ((node)->func->capacity_get(node))
#define transmission_control_block_buffer_out_node_capacity_set(node, n)                ((node)->func->capacity_set(node, n))
#define transmission_control_block_buffer_out_node_clear(node)                          ((node)->func->clear(node))

#define transmission_control_block_buffer_out_node_transmit_count_get(node)             ((node)->transmit.count)

#define transmission_control_block_buffer_out_node_segment_set(node, v)                 ((node)->segment = v)
#define transmission_control_block_buffer_out_node_segment_get(node)                    ((node)->segment)

// @deprecated
#define transmission_control_block_buffer_out_node_sequence_set(node, v)                ((node)->sequence = v)
// @deprecated
#define transmission_control_block_buffer_out_node_sequence_get(node)                   ((node)->sequence + (uint32_t)((node)->position))

#define transmission_control_block_buffer_out_node_retransmission_increase(node)        (nanosecond_get(address_of((node)->transmit.time)), ((node)->transmit.count = (node)->transmit.count + 1))

typedef transmission_control_block_buffer_in_node_t * (*transmission_control_block_buffer_in_node_factory_t)(transmission_control_block_buffer_in_t *, const void *, uint64_t);

struct transmission_control_block_buffer_in {
    transmission_control_block_buffer_in_func_t * func;
    sync_t * sync;
    uint64_t size;
    transmission_control_block_buffer_in_node_t * head;
    transmission_control_block_buffer_in_node_t * tail;
    transmission_control_block_buffer_in_node_t * front;

    uint64_t page;
    transmission_control_block_buffer_in_node_factory_t nodegen;
};

struct transmission_control_block_buffer_in_func {
    transmission_control_block_buffer_in_t * (*rem)(transmission_control_block_buffer_in_t *);
    void (*push)(transmission_control_block_buffer_in_t *, const void *, uint64_t);
    void (*pop)(transmission_control_block_buffer_in_t *, uint64_t);
    void (*clear)(transmission_control_block_buffer_in_t *);
    void (*shrink)(transmission_control_block_buffer_in_t *);
    transmission_control_block_buffer_in_node_t * (*front)(transmission_control_block_buffer_in_t *);
    transmission_control_block_buffer_in_node_t * (*back)(transmission_control_block_buffer_in_t *, uint64_t);
    transmission_control_block_buffer_in_node_t * (*head)(transmission_control_block_buffer_in_t *);

    transmission_control_block_buffer_in_node_t * (*add)(transmission_control_block_buffer_in_t *, transmission_control_block_buffer_in_node_t *);
    transmission_control_block_buffer_in_node_t * (*del)(transmission_control_block_buffer_in_t *, transmission_control_block_buffer_in_node_t *);
};

extern transmission_control_block_buffer_in_t * transmission_control_block_buffer_in_gen(transmission_control_block_buffer_in_node_factory_t nodegen, uint64_t page);

extern void transmission_control_block_buffer_in_func_transmit_on(transmission_control_block_buffer_in_t * buffer, transmission_control_block_buffer_in_node_t * node);

#define transmission_control_block_buffer_in_rem(buffer)                           ((buffer)->func->rem(buffer))
#define transmission_control_block_buffer_in_push(buffer, data, n)                 ((buffer)->func->push(buffer, data, n))
#define transmission_control_block_buffer_in_pop(buffer, n)                        ((buffer)->func->pop(buffer, n))
#define transmission_control_block_buffer_in_clear(buffer)                         ((buffer)->func->clear(buffer))
#define transmission_control_block_buffer_in_front(buffer)                         ((buffer)->func->front(buffer))
#define transmission_control_block_buffer_in_back(buffer, hint)                    ((buffer)->func->back(buffer, hint))
#define transmission_control_block_buffer_in_add(buffer, node)                     ((buffer)->func->add(buffer, node))
#define transmission_control_block_buffer_in_del(buffer, node)                     ((buffer)->func->del(buffer, node))

#define transmission_control_block_buffer_in_nodegen(buffer, data, n)              ((buffer)->nodegen(buffer, data, n))

#define transmission_control_block_buffer_in_transmit_on                           transmission_control_block_buffer_func_transmit_on

#define transmission_control_block_buffer_in_head(buffer)                          ((buffer)->head)
#define transmission_control_block_buffer_in_tail(buffer)                          ((buffer)->tail)

struct transmission_control_block_buffer_in_node {
    transmission_control_block_buffer_in_node_func_t * func;
    sync_t * sync;
    buffer_list_t * collection;
    transmission_control_block_buffer_in_node_t * prev;
    transmission_control_block_buffer_in_node_t * next;
    uint64_t position;
    uint64_t size;
    uint64_t capacity;
    void * mem;

    uint32_t sequence;
    uint32_t acknowledge;

    struct {
        nanosecond_t time;
        uint8_t count;
    } transmit;

    nanosecond_t time;
};

struct transmission_control_block_buffer_in_node_func {
    transmission_control_block_buffer_in_node_t * (*rem)(transmission_control_block_buffer_in_node_t *);
    void * (*front)(transmission_control_block_buffer_in_node_t *);
    void * (*back)(transmission_control_block_buffer_in_node_t *);
    int32_t (*shrink)(transmission_control_block_buffer_in_node_t *);
    uint64_t (*length)(transmission_control_block_buffer_in_node_t *);
    uint64_t (*remain)(transmission_control_block_buffer_in_node_t *);
    uint64_t (*position_get)(transmission_control_block_buffer_in_node_t *);
    void (*position_set)(transmission_control_block_buffer_in_node_t *, uint64_t);
    uint64_t (*size_get)(transmission_control_block_buffer_in_node_t *);
    void (*size_set)(transmission_control_block_buffer_in_node_t *, uint64_t);
    uint64_t (*capacity_get)(transmission_control_block_buffer_in_node_t *);
    void (*capacity_set)(transmission_control_block_buffer_in_node_t *, uint64_t);
    void (*clear)(transmission_control_block_buffer_in_node_t *);
};

extern transmission_control_block_buffer_in_node_t * transmission_control_block_buffer_in_node_gen(transmission_control_block_buffer_in_t * buffer, const void * data, uint64_t n);

#define transmission_control_block_buffer_in_node_rem(node)                            ((node)->func->rem(node))
#define transmission_control_block_buffer_in_node_front(node)                          ((node)->func->front(node))
#define transmission_control_block_buffer_in_node_back(node)                           ((node)->func->back(node))
#define transmission_control_block_buffer_in_node_shrink(node)                         ((node)->func->shrink(node))
#define transmission_control_block_buffer_in_node_length(node)                         ((node) ? (node)->func->length(node) : 0)
#define transmission_control_block_buffer_in_node_remain(node)                         ((node) ? (node)->func->remain(node) : 0)
#define transmission_control_block_buffer_in_node_position_get(node)                   ((node)->func->position_get(node))
#define transmission_control_block_buffer_in_node_position_set(node, n)                ((node)->func->position_set(node, n))
#define transmission_control_block_buffer_in_node_size_get(node)                       ((node)->func->size_get(node))
#define transmission_control_block_buffer_in_node_size_set(node, n)                    ((node)->func->size_set(node, n))
#define transmission_control_block_buffer_in_node_capacity_get(node)                   ((node)->func->capacity_get(node))
#define transmission_control_block_buffer_in_node_capacity_set(node, n)                ((node)->func->capacity_set(node, n))
#define transmission_control_block_buffer_in_node_clear(node)                          ((node)->func->clear(node))

#define transmission_control_block_buffer_in_node_transmit_count_get(node)             ((node)->transmit.count)
#define transmission_control_block_buffer_in_node_sequence_set(node, v)                ((node)->sequence = v)
#define transmission_control_block_buffer_in_node_sequence_get(node)                   ((node)->sequence + (uint32_t)((node)->position))

#define transmission_control_block_buffer_in_node_retransmission_increase(node)        (nanosecond_get(address_of((node)->transmit.time)), ((node)->transmit.count = (node)->transmit.count + 1))

typedef int32_t (*transmission_control_protocol_context_handler_t)(transmission_control_protocol_module_t *, uint32_t, internet_protocol_context_t *, transmission_control_protocol_context_t *);

struct transmission_control_protocol_module {
    transmission_control_protocol_module_func_t * func;
    sync_t * sync;
    uint16_t type;
    uint16_t addrlen;
    ___reference protocol_module_map_t * map;

    transmission_control_protocol_context_handler_t on;

    hashtable_t * block;
    struct {
        socket_client_event_subscription_pool_t * pool;
    } client;

    uint16_t max_segment_size;
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
    uint32_t (*sequence_gen)(transmission_control_protocol_module_t *, internet_protocol_context_t *, transmission_control_protocol_context_t *);
};

extern transmission_control_protocol_module_t * transmission_control_protocol_module_gen(protocol_module_map_t * map, transmission_control_protocol_context_handler_t on);
extern uint32_t transmission_control_protocol_module_func_sequence_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

extern int32_t transmission_control_protocol_module_func_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

#define transmission_control_protocol_module_addrlen_get(module)                                                ((module)->addrlen)
#define transmission_control_protocol_module_number_get(module)                                                 ((module)->type)

#define transmission_control_protocol_module_rem(module)                                                        ((module)->func->rem(module))
#define transmission_control_protocol_module_deserialize(module, packet, packetlen, parent, context)            ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define transmission_control_protocol_module_serialize(module, parent, context, packet, len)                    ((module)->func->serialize(module, parent, context, packet, len))
#define transmission_control_protocol_module_debug(module, stream, context)                                     ((module)->func->debug(module, stream, context))
#define transmission_control_protocol_module_in(module, packet, packetlen, parent, context)                     ((module)->func->in(module, packet, packetlen, parent, context))
#define transmission_control_protocol_module_out(module, node, child)                                           ((module)->func->out(module, node, child))
#define transmission_control_protocol_module_context_gen(module, node, child)                                   ((module)->func->context_gen(module, node, child))
#define transmission_control_protocol_module_reply_gen(module, request)                                         ((module)->func->reply_gen(module, request))
#define transmission_control_protocol_module_seqeuence_gen(module, parent, context)                             ((module)->func->sequence_gen(module, parent, context))

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
    uint64_t * bufferlen;

    internet_protocol_pseudo_t * pseudo;
    uint64_t pseudolen;

    uint16_t checksumcal;

    uint32_t headerlen;
    uint32_t datalen;

    transmission_control_protocol_option_t * option;
    uint8_t * data;

    hashtable_node_key_t key;                                   // 중복적으로 키가 발생한다. 불필요한 공간인가? 아니면 조금 더 메모리를 줄일 수 있는가?
    transmission_control_block_t * block;
    uint32_t state;
};

struct transmission_control_protocol_context_func {
    transmission_control_protocol_context_t * (*rem)(transmission_control_protocol_context_t *);
    int32_t (*valid)(transmission_control_protocol_context_t *);
    uint8_t * (*addrptr)(transmission_control_protocol_context_t *, uint32_t);
    void (*checksum_build)(transmission_control_protocol_context_t *, const uint8_t *, uint64_t);
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen, uint64_t * bufferlen);

extern int32_t transmission_control_protocol_context_key_gen(transmission_control_protocol_context_t * context);
extern uint32_t transmission_control_protocol_direction_cal(transmission_control_protocol_context_t * context);

// SINGLE METHOD ...
extern int32_t transmission_control_protocol_context_is_connect_syn(transmission_control_protocol_context_t * context);
extern int32_t transmssion_control_protocol_context_is_connect_ack(transmission_control_protocol_context_t * context);

// extern int32_t transmssion_control_protocol_context_is_accept_syn(transmission_control_protocol_context_t * context);
// extern void transmission_control_protocol_context_func_buffer_reserve(transmission_control_protocol_context_t * context, uint64_t n);

#define transmission_control_protocol_context_buffer_reversal_reserve(context, n)               (protocol_context_buffer_reversal_reserve((protocol_context_t *) (context), n))
#define transmission_control_protocol_context_buffer_reversal_push(context, data, datalen)      (protocol_context_buffer_reversal_push((protocol_context_t *) (context), data, datalen))

#define transmission_control_protocol_context_rem(context)                                      ((context)->func->rem(context))
#define transmission_control_protocol_context_valid(context)                                    ((context)->func->valid(context))
#define transmission_control_protocol_context_addrptr(context, type)                            ((context)->func->addrptr(context, type))
#define transmission_control_protocol_context_checksum_build(context, pseudo, pseudolen)        ((context)->func->checksum_build(context, pseudo, pseudolen))

#define transmission_control_protocol_context_bufferlen_set(context, len)                       ((context)->bufferlen = len)
#define transmission_control_protocol_context_bufferlen_get(context)                            ((context)->bufferlen)

#define transmission_control_protocol_context_error_get(context)                                ((context)->error)
#define transmission_control_protocol_context_error_set(context, v)                             ((context)->error = v)
#define transmission_control_protocol_context_packetlen_get(context)                            ((context)->packetlen)
#define transmission_control_protocol_context_packetlen_set(context)                            ((context)->packetlen = v)
#define transmission_control_protocol_context_headerlen_get(context)                            ((context)->headerlen)
#define transmission_control_protocol_context_headerlen_set(context, v)                         ((context)->headerlen = v)
#define transmission_control_protocol_context_headerlen_add(context, v)                         ((context)->headerlen = (context)->headerlen + v)
#define transmission_control_protocol_context_datalen_get(context)                              ((context)->datalen)
#define transmission_control_protocol_context_datalen_set(context, v)                           ((context)->datalen = v)
#define transmission_control_protocol_context_checksumcal_get(context)                          ((context)->checksumcal)
#define transmission_control_protocol_context_checksumcal_set(context, v)                       ((context)->checksumcal =  v)
#define transmission_control_protocol_context_source_get(context)                               (ntohs((context)->packet->source))
#define transmission_control_protocol_context_source_set(context, v)                            ((context)->packet->source = htons(v))
#define transmission_control_protocol_context_destination_get(context)                          (ntohs((context)->packet->destination))
#define transmission_control_protocol_context_destination_set(context, v)                       ((context)->packet->destination = htons(v))
#define transmission_control_protocol_context_sequence_get(context)                             (ntohl((context)->packet->sequence))
#define transmission_control_protocol_context_sequence_set(context, v)                          ((context)->packet->sequence = htonl(v))
#define transmission_control_protocol_context_acknowledge_get(context)                          (ntohl((context)->packet->acknowledge))
#define transmission_control_protocol_context_acknowledge_set(context, v)                       ((context)->packet->acknowledge = htonl(v))
#define transmission_control_protocol_context_offset_get(context)                               ((context)->packet->offset)
#define transmission_control_protocol_context_offset_set(context, v)                            ((context)->packet->offset = v)
#define transmission_control_protocol_context_cwr_get(context)                                  ((context)->packet->control.bit.cwr)
#define transmission_control_protocol_context_cwr_on(context)                                   ((context)->packet->control.bit.cwr = 1)
#define transmission_control_protocol_context_cwr_off(context)                                  ((context)->packet->control.bit.cwr = 0)
#define transmission_control_protocol_context_ece_get(context)                                  ((context)->packet->control.bit.ece)
#define transmission_control_protocol_context_ece_on(context)                                   ((context)->packet->control.bit.ece = 1)
#define transmission_control_protocol_context_ece_off(context)                                  ((context)->packet->control.bit.ece = 0)
#define transmission_control_protocol_context_urg_get(context)                                  ((context)->packet->control.bit.urg)
#define transmission_control_protocol_context_urg_on(context)                                   ((context)->packet->control.bit.urg = 1)
#define transmission_control_protocol_context_urg_off(context)                                  ((context)->packet->control.bit.urg = 0)
#define transmission_control_protocol_context_ack_get(context)                                  ((context)->packet->control.bit.ack)
#define transmission_control_protocol_context_ack_on(context)                                   ((context)->packet->control.bit.ack = 1)
#define transmission_control_protocol_context_ack_off(context)                                  ((context)->packet->control.bit.ack = 0)
#define transmission_control_protocol_context_psh_get(context)                                  ((context)->packet->control.bit.psh)
#define transmission_control_protocol_context_psh_on(context)                                   ((context)->packet->control.bit.psh = 1)
#define transmission_control_protocol_context_psh_off(context)                                  ((context)->packet->control.bit.psh = 0)
#define transmission_control_protocol_context_rst_get(context)                                  ((context)->packet->control.bit.rst)
#define transmission_control_protocol_context_rst_on(context)                                   ((context)->packet->control.bit.rst = 1)
#define transmission_control_protocol_context_rst_off(context)                                  ((context)->packet->control.bit.rst = 0)
#define transmission_control_protocol_context_syn_get(context)                                  ((context)->packet->control.bit.syn)
#define transmission_control_protocol_context_syn_on(context)                                   ((context)->packet->control.bit.syn = 1)
#define transmission_control_protocol_context_syn_off(context)                                  ((context)->packet->control.bit.syn = 0)
#define transmission_control_protocol_context_fin_get(context)                                  ((context)->packet->control.bit.fin)
#define transmission_control_protocol_context_fin_on(context)                                   ((context)->packet->control.bit.fin = 1)
#define transmission_control_protocol_context_fin_off(context)                                  ((context)->packet->control.bit.fin = 0)
#define transmission_control_protocol_context_flags_get(context)                                ((context)->packet->control.flags)
#define transmission_control_protocol_context_flags_set(context, v)                             ((context)->packet->control.flags = v)
#define transmission_control_protocol_context_flags_has(context, v)                             ((context)->packet->control.flags & v)
#define transmission_control_protocol_context_window_get(context)                               (ntohs((context)->packet->window))
#define transmission_control_protocol_context_window_set(context, v)                            ((context)->packet->window = htons(v))
#define transmission_control_protocol_context_checksum_get(context)                             (ntohs((context)->packet->checksum))
#define transmission_control_protocol_context_checksum_set(context, v)                          ((context)->packet->checksum = htons(v))
#define transmission_control_protocol_context_urgent_get(context)                               (ntohs((context)->packet->pointer))
#define transmission_control_protocol_context_urgent_set(context, v)                            ((context)->packet->pointer = htons(v))
#define transmission_control_protocol_context_option_get(context)                               ((context)->option)
#define transmission_control_protocol_context_option_set(context, v)                            ((context)->option = v)
#define transmission_control_protocol_context_data_get(context)                                 ((context)->data)
#define transmission_control_protocol_context_data_set(context, v)                              ((context)->data = v)
#define transmission_control_protocol_context_state_get(context)                                ((context)->state)
#define transmission_control_protocol_context_state_set(context, v)                             ((context)->state = v)

#define transmission_control_protocol_context_block_set(context, v)                             ((context)->block = v)
#define transmission_control_protocol_context_block_get(context)                                ((context)->block)

#define transmission_control_protocol_context_data_cal(context)                                 (transmission_control_protocol_context_headerlen_get(context) == transmission_control_protocol_context_packetlen_get(context) ? nil : (&((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)]))
#define transmission_control_protocol_context_option_cal(context)                               (transmission_control_protocol_context_headerlen_get(context) == (transmission_control_protocol_context_offset_get(context) * 4) ? nil : (&((uint8_t *) ((context)->packet))[transmission_control_protocol_context_headerlen_get(context)]))

#define transmission_control_protocol_context_key_get(context)                                  (address_of((context)->key))

#define transmission_control_protocol_context_key_has(context)                                  ((context)->key.value != nil)

#endif // __SNORLAX__PROTOCOL_INTERNET_TRANSMISSION_CONTROL__H__
