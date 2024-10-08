/**
 * @file        snorlax/protocol/internet/transmission/control.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
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
#include <snorlax/socket/server.h>
#include <snorlax/socket/server/event/subscription.h>

/**
 * 
 */
#define transmission_control_maximum_segment_lifetime               (2 * 60 * 1000)

/**
 * 
 * The problem is that the recovering host may not know for how long it was down between rebooting nor does it know whether there are still old duplicates in the system from earlier connection incarnations.
 * 
 * One way to deal with this problem is to deliberately delay emitting segments for one MSL after recovery from a reboot -- this is the "quiet time" specification.
 * Hosts that prefer to avoid waiting and are willing to risk possible confusion of old and new packets at a given destination may choose not to wait for the "quiet time".
 * Implementers may provide TCP users with the ability to select on a connection-by-connection basis whether to wait after a reboot,
 * or may informally implement the "quiet time" for all connections.
 * Obviously, even where a user selects to "wait", this is not necessary after the host has been "up" for at least MSL seconds.
 * 
 * To summarize: every segment emitted occupied one or more sequence numbers in the sequence space, and the numbers occupied by a segment are "busy" or "in use" until MSL seconds have passed.
 * Upon rebooting, a block of space-time is occupied by the octets and SYN and FIN flags of any potentially still in-flight segments.
 * If a new connection is started too soon and uses any of the sequence numbers in the space-time footprint of those potentially still in-flight segments of the previous connection incarnation,
 * there is a potential sequence number overlap area that could cause confusion at the receiver.
 * 
 * @see         [3.4.3. The TCP Quiet Time Concept](https://www.ietf.org/rfc/rfc9293.html)
 */
#define transmission_control_quiet_time                             (transmission_control_maximum_segment_lifetime)

#define transmission_control_state_avail_in                         (0x8000u)
#define transmission_control_state_avail_out                        (0x4000u)
#define transmission_control_state_avail_accept                     (0x2000u)
#define transmission_control_state_finishing                        (0x1000u)
#define transmission_control_state_avail_io                         (transmission_control_state_avail_in | transmission_control_state_avail_out)

/**
 * Represents no connection state at all.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_closed                           (transmission_control_state_finishing    |  0)

/**
 * Represents waiting for a connection request from any remote Transmission Control Protocol <sup>TCP</sup> peer and port.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_listen                           (transmission_control_state_avail_accept |  1)

/**
 * Represents waiting for a matching connection request after having sent a connection request.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_synchronize_sequence_sent        (transmission_control_state_avail_io     |  2)

/**
 * Represents waiting for a conforming connection request acknowledgment after having both received and sent a connection request.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_synchronize_sequence_recv        (transmission_control_state_avail_io     |  3)

/**
 * Represents an open connection, data received can be delivered to the user.
 * 
 * The normal state for the data transfer phase of the connection.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_established                      (transmission_control_state_avail_io     |  4)

/**
 * Represents waiting for a connection termination request from the remote Transmission Control Protocol <sup>TCP</sup> peer, or an acknowledgment of the connection termination request previously sent.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_finish_wait_first                (transmission_control_state_finishing    |  5)

/**
 * Represents waiting for a connection termination request from the remote Transmission Control Protocol <sup>TCP</sup> peer.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_finish_wait_second               (transmission_control_state_finishing    |  6)

/**
 * Represents waiting for a connection termination request from the local user.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_close_wait                       (transmission_control_state_finishing    |  7)

/**
 * Represents waiting for a connection termination request from the remote Transmission Control Protocol <sup>TCP</sup> peer.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_closing                          (transmission_control_state_finishing    |  8)

/**
 * Represents waiting for an acknowledgment of the connection termination request previously sent to the remote Transmission Control Protocol <sup>TCP</sup> peer.
 * 
 * This termination request sent to the remote Transmission Control Protocol <sup>TCP</sup> peer already included an acknowledgment of the termination request sent from the remote Transmission Control Protocol <sup>TCP</sup> peer.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_last_acknowledge                 (transmission_control_state_finishing    |  9)

/**
 * Represents waiting for enough time to pass to be sure the remote Transmission Control Protocol <sup>TCP</sup> peer received the acknowledgment of its connection termination request and to avoid new connections being impacted by delayed segments from previous connections.
 * 
 * @see     [3.3.2. State Machine Overview](https://www.ietf.org/rfc/rfc9293.html#section-3.3.2)
 */
#define transmission_control_state_time_wait                        (transmission_control_state_finishing    | 10)

struct transmission_control_protocol_option_maximum_segment_size;
struct transmission_control_protocol_option_window_scale;

struct transmission_control_block;
struct transmission_control_block_func;
struct transmission_control_block_agent;
struct transmission_control_block_agent_func;
struct transmission_control_block_client;
struct transmission_control_block_client_func;
struct transmission_control_block_server;
struct transmission_control_block_server_func;

struct transmission_control_buffer;
struct transmission_control_buffer_func;
struct transmission_control_buffer_node;
struct transmission_control_buffer_node_func;

struct transmission_control_buffer_in;
struct transmission_control_buffer_in_func;
struct transmission_control_buffer_in_node;
struct transmission_control_buffer_in_node_func;

struct transmission_control_buffer_out;
struct transmission_control_buffer_out_func;
struct transmission_control_buffer_out_node;
struct transmission_control_buffer_out_node_func;

typedef hashtable_t transmission_control_block_map_t;

struct transmission_control_protocol_packet;

struct transmission_control_protocol_module;
struct transmission_control_protocol_module_func;
struct transmission_control_protocol_context;
struct transmission_control_protocol_context_func;

typedef struct transmission_control_block                               transmission_control_block_t;
typedef struct transmission_control_block_func                          transmission_control_block_func_t;
typedef struct transmission_control_block_agent                         transmission_control_block_agent_t;
typedef struct transmission_control_block_agent_func                    transmission_control_block_agent_func_t;
typedef struct transmission_control_block_client                        transmission_control_block_client_t;
typedef struct transmission_control_block_client_func                   transmission_control_block_client_func_t;
typedef struct transmission_control_block_server                        transmission_control_block_server_t;
typedef struct transmission_control_block_server_func                   transmission_control_block_server_func_t;

typedef struct transmission_control_buffer                                          transmission_control_buffer_t;
typedef struct transmission_control_buffer_func                                     transmission_control_buffer_func_t;
typedef struct transmission_control_buffer_node                                     transmission_control_buffer_node_t;
typedef struct transmission_control_buffer_node_func                                transmission_control_buffer_node_func_t;

typedef struct transmission_control_buffer_in                                       transmission_control_buffer_in_t;
typedef struct transmission_control_buffer_in_func                                  transmission_control_buffer_in_func_t;
typedef struct transmission_control_buffer_in_node                                  transmission_control_buffer_in_node_t;
typedef struct transmission_control_buffer_in_node_func                             transmission_control_buffer_in_node_func_t;

typedef struct transmission_control_buffer_out                                      transmission_control_buffer_out_t;
typedef struct transmission_control_buffer_out_func                                 transmission_control_buffer_out_func_t;
typedef struct transmission_control_buffer_out_node                                 transmission_control_buffer_out_node_t;
typedef struct transmission_control_buffer_out_node_func                            transmission_control_buffer_out_node_func_t;

typedef transmission_control_buffer_t                                               transmission_control_buffer_in_t;
typedef transmission_control_buffer_t                                               transmission_control_buffer_out_t;

typedef transmission_control_buffer_node_t                                          transmission_control_buffer_node_in_t;
typedef transmission_control_buffer_node_t                                          transmission_control_buffer_node_out_t;

typedef struct transmission_control_protocol_packet                                 transmission_control_protocol_packet_t;
typedef uint8_t                                                                     transmission_control_protocol_option_t;
typedef struct transmission_control_protocol_option_maximum_segment_size            transmission_control_protocol_option_maximum_segment_size_t;
typedef struct transmission_control_protocol_option_window_scale                    transmission_control_protocol_option_window_scale_t;

typedef struct transmission_control_protocol_module                                 transmission_control_protocol_module_t;
typedef struct transmission_control_protocol_module_func                            transmission_control_protocol_module_func_t;
typedef struct transmission_control_protocol_context                                transmission_control_protocol_context_t;
typedef struct transmission_control_protocol_context_func                           transmission_control_protocol_context_func_t;

#define transmission_control_protocol_window_cal(window, shift)                     ((uint32_t)(window) * (uint32_t)(shift))
#define transmission_control_protocol_maximum_window_cal(window, factor)            (transmission_control_protocol_window_cal(window, 1u << (factor)))

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

/**
 * Check segment acceptability.
 * 
 * When data is received, the following comparison are needed:
 * 
 * - Receive Next <sup>RCV.NXT</sup> = Next sequence number expected on an incoming segment, and is the left or lower edge of the receive window.
 * - Receive Window <sup>RCV.NXT</sup> + Receive Window <sup>RCV.WND</sup> - 1 = Last sequence number expected on an incoming segment, and is the right or upper edge of the receive window.
 * - Segment Sequence <sup>SEG.SEQ</sup> = First sequence number occupied by the incoming segment.
 * - Segment Sequence <sup>SEG.SEQ</sup> + Segment Length <sup>SEG.LEN</sup> - 1 = Last sequence number occupied by the incoming segment.
 * 
 * A segment is judged to occupy a portion of valid receive sequence space if
 * 
 * Receive Next <sup>RCV.NXT</sup> =< Segment Sequence <sup>SEG.SEQ</sup> < Receive Next <sup>RCV.NXT</sup> + Receive Window <sup>RCV.WND</sup>
 * 
 * or
 * 
 * Receive Next <sup>RCV.NXT</sup> =< Segment Sequence <sup>SEG.SEQ</sup> + Segment Length <sup>SEG.LEN</sup> - 1 < Receive Next <sup>RCV.NXT</sup> + Receive Window <sup>RCV.WND</sup>
 * 
 * Actually, it is a little more complicated than this. Due to zero windows and zero length segments, we have four cases for the acceptability of an incoming segment:
 * 
 * | Segment Length     | Receive Window     | Test                                                                                                                                         |
 * | ------------------ | ------------------ | -------------------------------------------------------------------------------------------------------------------------------------------- |
 * | 0                  | 0                  | Segment Sequence <sup>SEG.SEQ</sup> = Receive Next <sup>RCV.NXT</sup>                                                                        |
 * | 0                  | Receive Window > 0 | Receive Next <sup>RCV.NXT</sup> =< Segment Sequence <sup>SEG.SEQ</sup> < Receive Next <sup>RCV.NXT</sup> + Receive Window <sup>RCV.WND</sup> |
 * | Segment Length > 0 | 0                  | Not acceptable                                                                                                                               |
 * | Segment Length > 0 | Receive Window > 0 | Receive Next <sup>RCV.NXT</sup> =< Segment Sequence <sup>SEG.SEQ</sup> < Receive Next <sup>RCV.NXT</sup> + Receive Window <sup>RCV.WND</sup><br />Receive Next <sup>RCV.NXT</sup> =< Segment Sequence <sup>SEG.SEQ</sup> + Segment Length <sup>SEG.LEN</sup> - 1 < Receive Next <sup>RCV.NXT</sup> + Receive Window <sup>RCV.WND</sup> |
 * 
 * Note that when the receive window is zero no segments should be acceptable except Acknowledgment <sup>ACK</sup> segments.
 * 
 * @param in    sequence    | uint32_t | Receive Next <sup>RCV.NXT</sup> = Next sequence number expected on an incoming segment, and is the left or lower edge of the receive window.
 * @param in    window      | uint32_t | Receive Window <sup>RCV.WND</sup> = Receive Window
 * @param in    n           | uint32_t | Segment Sequence <sup>SEG.SEQ</sup> = First sequence number of a segment.
 * @param in    length      | uint32_t | Segment Length <sup>SEG.LEN</sup> = The number of octets occupied by the data in the segment (counting Synchronize Sequence Number <sup>SYN</sup> and Finish <sup>FIN</sup>)
 * 
 * @return      bool        | If return true, segment is acceptable, otherwise, segment is not acceptable.
 * 
 * @see         [3.4. Sequence Numbers](https://www.ietf.org/rfc/rfc9293.html)
 */
extern int32_t transmission_control_func_check_acceptable_seq(uint32_t sequence, uint32_t window, uint32_t n, uint32_t length);

extern uint32_t transmission_control_func_sequence_gen(uint8_t version, uint8_t * remote, uint8_t * local, uint32_t ports, uint32_t secret);

#define transmission_control_check_out_of_window(sequence, window, n)                   ((window) <= (n) - (sequence))       // check ((n) - (sequence) <= (window))

// #define transmission_control_check_acceptable_seq(sequence, window, n, length)

/**
 * Check segment acknowledgment acceptability.
 * 
 * @param in    acknowledge | uint32_t | Send Unacknowledge <sup>SND.UNA</sup> = Oldest unacknowledged sequence number.
 * @param in    sequence    | uint32_t | Send Next <sup>SND.NXT</sup> = Next sequence number to be sent.
 * @param in    n           | uint32_t | Segment Acknowledge <sup>SEG.ACK</sup> = Acknowledgment from the receiving Transmission Control Protocol <sup>TCP</sup> peer (next sequence number expected by the receiving Transmission Control Protocol <sup>TCP</sup> peer)
 * 
 * @return      bool        | If return ture, segment acknowledge is acceptable, otherwise, segment acknowledge is not acceptable.
 * 
 * @see         [3.4. Sequence Numbers](https://www.ietf.org/rfc/rfc9293.html)
 */
#define transmission_control_check_acceptable_ack(acknowledge, sequence, n)     (((n) - (acknowledge)) <= (((sequence)) - (n)))

/**
 * Check segment sequence acceptability.
 * 
 * 
 * 
 * @param in    sequence    | uint32_t | Receive Next <sup>RCV.NXT</sup> = Next sequence number expected on an incoming segment, and is the left or lower edge of the receive window.
 * @param in    window      | uint32_t | Receive Window <sup>RCV.WND</sup> = Receive Window
 * @param in    n           | uint32_t | Segment Sequence <sup>SEG.SEQ</sup> = First sequence number of a segment.
 * @param in    length      | uint32_t | Segment Length <sup>SEG.LEN</sup> = The number of octets occupied by the data in the segment (counting Synchronize Sequence Number <sup>SYN</sup> and Finish <sup>FIN</sup>)
 * 
 * @return      bool        | If return true, segment sequence is acceptable, otherwise, segment sequence is not acceptable.
 * 
 * @see         [3.4. Sequence Numbers](https://www.ietf.org/rfc/rfc9293.html)
 */
#define transmission_control_check_acceptable_seq(sequence, window, n, length)          (transmission_control_func_check_acceptable_seq(sequence, window, n, length))



// (((n) - (sequence) < (window)) || (((n) + (length)) - (sequence) < (window)))
// #define transmission_control_check_valid_ack()



// ((((n) - (acknowledge)) <= ((sequence) + (length)) - (acknowledge)) && ((((sequence) + (length)) - (n)) <= (((sequence) + (length)) - (acknowledge))))




// length == 0 ? ((((sequence) + (length)) - (acknowledge))) <= ((n) - (acknowledge)) : 
// (n) - (acknowledge) 


#define transmission_control_protocol_default_max_segment_size              1024

#define transmission_control_protocol_packet_length_min                     20

#define transmission_control_protocol_option_type_end                       0
#define transmission_control_protocol_option_type_no_operation              1
#define transmission_control_protocol_option_type_maximum_segment_size      2
#define transmission_control_protocol_option_type_window_scale              3

#define transmission_control_protocol_option_length_get(option)             ((*(option) == 0 || *(option) == 1) ? 1 : *(option)[1])

#define transmission_control_protocol_to_port(addr)                         (*((uint16_t *) (addr)))

#define transmission_control_block_agent_event_type_subscription            0
#define transmission_control_block_agent_event_type_open                    1
#define transmission_control_block_agent_event_type_read                    2
#define transmission_control_block_agent_event_type_write                   3
#define transmission_control_block_agent_event_type_close                   4
#define transmission_control_block_agent_event_type_exception               5
#define transmission_control_block_agent_event_type_in                      6
#define transmission_control_block_agent_event_type_out                     7
#define transmission_control_block_agent_event_type_max                     8

typedef void (*transmission_control_block_agent_handler_t)(transmission_control_block_agent_t *, uint32_t, void *);

struct transmission_control_block_agent {
    transmission_control_block_agent_func_t * func;
    sync_t * sync;
    ___reference transmission_control_block_t * block;
    socket_event_subscription_t * subscription;
    transmission_control_block_agent_handler_t on;
};

struct transmission_control_block_agent_func {
    transmission_control_block_agent_t * (*rem)(transmission_control_block_agent_t *);

    int32_t (*open)(transmission_control_block_agent_t *);
    int64_t (*send)(transmission_control_block_agent_t *, transmission_control_buffer_out_t *, transmission_control_buffer_out_t *);
    int64_t (*recv)(transmission_control_block_agent_t *);
    int32_t (*close)(transmission_control_block_agent_t *);
    int32_t (*abort)(transmission_control_block_agent_t *);
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

___extend(transmission_control_block_agent_t)
struct transmission_control_block_client {
    transmission_control_block_client_func_t * func;
    sync_t * sync;
    ___reference transmission_control_block_t * block;
    socket_client_event_subscription_t * subscription;
    transmission_control_block_client_handler_t on;
};

struct transmission_control_block_client_func {
    transmission_control_block_client_t * (*rem)(transmission_control_block_client_t *);

    int32_t (*open)(transmission_control_block_client_t *, socket_client_factory_t, event_engine_t *);      // active open / connect
    int64_t (*send)(transmission_control_block_client_t *, transmission_control_buffer_out_t *, transmission_control_buffer_out_t *);
    int64_t (*recv)(transmission_control_block_client_t *);
    int32_t (*close)(transmission_control_block_client_t *);
    int32_t (*abort)(transmission_control_block_client_t *);
    int32_t (*shutdown)(transmission_control_block_client_t *, uint32_t);

    int32_t (*in)(transmission_control_block_client_t *, transmission_control_protocol_context_t *);
    int32_t (*out)(transmission_control_block_client_t *);
};

/**
 * 임시적으로 정의하였다. 필요하면 구현하자.
 */
typedef socket_client_t * (*socket_server_factory_t)(int32_t, int32_t, int32_t, void *, uint64_t);    // TODO: MOVE 
typedef void (*transmission_control_block_server_handler_t)(transmission_control_block_server_t *, uint32_t, void *);

___extend(transmission_control_block_agent_t)
struct transmission_control_block_server {
    transmission_control_block_server_func_t * func;
    sync_t * sync;
    ___reference transmission_control_block_t * block;
    socket_server_event_subscription_t * subscription;
    transmission_control_block_server_handler_t on;
};

struct transmission_control_block_server_func {
    transmission_control_block_server_t * (*rem)(transmission_control_block_server_t *);

    int32_t (*open)(transmission_control_block_server_t *, socket_server_factory_t, event_engine_t *);      // active open
    int64_t (*send)(transmission_control_block_server_t *, transmission_control_buffer_out_t *, transmission_control_buffer_out_t *);
    int64_t (*recv)(transmission_control_block_server_t *);
    int32_t (*close)(transmission_control_block_server_t *);
    int32_t (*abort)(transmission_control_block_server_t *);
    int32_t (*shutdown)(transmission_control_block_server_t *, uint32_t);

    int32_t (*in)(transmission_control_block_server_t *, transmission_control_protocol_context_t *);
    int32_t (*out)(transmission_control_block_server_t *);
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

typedef transmission_control_buffer_node_t * (*transmission_control_buffer_node_factory_t)(transmission_control_buffer_t *, const void *, uint64_t);

/**
 * 
 * @var transmission_control_buffer::sequence
 * 
 * uint32_t
 * 
 * transmission_control_buffer::sequence = SND.UNA
 * 
 * Send Unacknowledged <sup>SND.UNA</sup> = Oldest unacknowledged sequence number.
 * 
 * @var transmission_control_buffer::acknowledge
 * 
 * uint32_t 
 * 
 * Send Next <sup>SND.NXT</sup> = Next sequence number to be sent.
 */
struct transmission_control_buffer {
    transmission_control_buffer_func_t *        func;
    sync_t *                                    sync;
    uint64_t                                    size;
    transmission_control_buffer_node_t *        head;
    transmission_control_buffer_node_t *        tail;
    transmission_control_buffer_node_t *        front;
    uint64_t                                    page;               // maximum segment size
    transmission_control_buffer_node_factory_t  nodegen;

    uint32_t                                    sequence;
    uint32_t                                    acknowledge;
    uint16_t                                    window;
    uint8_t                                     scale;
    uint16_t                                    shift;
};

struct transmission_control_buffer_func {
    transmission_control_buffer_t * (*rem)(transmission_control_buffer_t *);
    void (*push)(transmission_control_buffer_t *, const void *, uint64_t);
    void (*pop)(transmission_control_buffer_t *, uint64_t);
    void (*clear)(transmission_control_buffer_t *);
    void (*shrink)(transmission_control_buffer_t *);
    transmission_control_buffer_node_t * (*front)(transmission_control_buffer_t *);
    transmission_control_buffer_node_t * (*back)(transmission_control_buffer_t *, uint64_t);
    transmission_control_buffer_node_t * (*head)(transmission_control_buffer_t *);
    transmission_control_buffer_node_t * (*add)(transmission_control_buffer_t *, transmission_control_buffer_node_t *);
    transmission_control_buffer_node_t * (*del)(transmission_control_buffer_t *, transmission_control_buffer_node_t *);
};

extern transmission_control_buffer_t * transmission_control_buffer_gen(transmission_control_buffer_node_factory_t nodegen, transmission_control_protocol_module_t * module);

#define transmission_control_buffer_window_cal(buffer)                      ((uint32_t) ((buffer)->window)) * (1u << ((buffer)->scale)))

#define transmission_control_buffer_rem(buffer)                             ((buffer)->func->rem(buffer))
#define transmission_control_buffer_push(buffer, data, n)                   ((buffer)->func->push(buffer, data, n))
#define transmission_control_buffer_pop(buffer, n)                          ((buffer)->func->pop(buffer, n))
#define transmission_control_buffer_clear(buffer)                           ((buffer)->func->clear(buffer))
#define transmission_control_buffer_front(buffer)                           ((buffer)->func->front(buffer))
#define transmission_control_buffer_back(buffer, hint)                      ((buffer)->func->back(buffer, hint))
#define transmission_control_buffer_add(buffer, node)                       ((buffer)->func->add(buffer, node))
#define transmission_control_buffer_del(buffer, node)                       ((buffer)->func->del(buffer, node))
#define transmission_control_buffer_maximum_size_set(buffer, v)             ((buffer)->page = v)
#define transmission_control_buffer_maximum_size_get(buffer)                ((uint16_t)((buffer)->page))

#define transmission_control_buffer_nodegen(buffer, data, n)                ((buffer)->nodegen(buffer, data, n))

// #define transmission_control_buffer_acceptable(buffer, )





___extend(buffer_list_node_t)
struct transmission_control_buffer_node {
    transmission_control_buffer_node_func_t *   func;
    sync_t *                                    sync;
    buffer_list_t *                             collection;
    transmission_control_buffer_node_t *        prev;
    transmission_control_buffer_node_t *        next;
    uint64_t                                    position;
    uint64_t                                    size;
    uint64_t                                    capacity;
    void *                                      mem;

    ___reference uint8_t *                      segment;
    nanosecond_t                                time;

    struct {
        nanosecond_t                            time;
        uint8_t                                 count;
    } transmit;

    uint32_t                                    sequence;
    uint32_t                                    acknowledge;
};

___extend(buffer_list_func_t)
struct transmission_control_buffer_node_func {
    transmission_control_buffer_node_t * (*rem)(transmission_control_buffer_node_t *);
    void * (*front)(transmission_control_buffer_node_t *);
    void * (*back)(transmission_control_buffer_node_t *);
    int32_t (*shrink)(transmission_control_buffer_node_t *);
    uint64_t (*length)(transmission_control_buffer_node_t *);
    uint64_t (*remain)(transmission_control_buffer_node_t *);
    uint64_t (*position_get)(transmission_control_buffer_node_t *);
    void (*position_set)(transmission_control_buffer_node_t *, uint64_t);
    uint64_t (*size_get)(transmission_control_buffer_node_t *);
    void (*size_set)(transmission_control_buffer_node_t *, uint64_t);
    uint64_t (*capacity_get)(transmission_control_buffer_node_t *);
    void (*capacity_set)(transmission_control_buffer_node_t *, uint64_t);
    void (*clear)(transmission_control_buffer_node_t *);
};

extern transmission_control_buffer_node_t * transmission_control_buffer_node(transmission_control_buffer_t * buffer, const void * data, uint64_t n);

// #define transmission_control_buffer_in_gen                              transmission_control_buffer_node
// #define transmission_control_buffer_out_gen                             transmission_control_buffer_node

#define transmission_control_buffer_node_rem(node)                      ((node)->func->rem(node))
#define transmission_control_buffer_node_front(node)                    ((node)->func->front(node))
#define transmission_control_buffer_node_back(node)                     ((node)->func->back(node))
#define transmission_control_buffer_node_shrink(node)                   ((node)->func->shrink(node))
#define transmission_control_buffer_node_length(node)                   ((node) ? (node)->func->length(node) : 0)
#define transmission_control_buffer_node_remain(node)                   ((node) ? (node)->func->remain(node) : 0)
#define transmission_control_buffer_node_position_get(node)             ((node)->func->position_get(node))
#define transmission_control_buffer_node_position_set(node, n)          ((node)->func->position_set(node, n))
#define transmission_control_buffer_node_size_get(node)                 ((node)->func->size_get(node))
#define transmission_control_buffer_node_size_set(node, n)              ((node)->func->size_set(node, n))
#define transmission_control_buffer_node_capacity_get(node)             ((node)->func->capacity_get(node))
#define transmission_control_buffer_node_capacity_set(node, n)          ((node)->func->capacity_set(node, n))
#define transmission_control_buffer_node_clear(node)                    ((node)->func->clear(node))
#define transmission_control_buffer_node_segment_get(node)              ((node)->segment)
#define transmission_control_buffer_node_segment_set(node, p)           ((node)->segment = p)

___implement extern void transmission_control_buffer_in_append(transmission_control_buffer_in_t * in, transmission_control_buffer_node_in_t * node);

/**
 * 전송을 위한 세그먼트에서 사용할 ACKNOWLEDGE NUMBER 를 계산한다.
 * 
 * 수신 버퍼의 `sequence` 는 리스트 버퍼의 프런트의 SEQUENCE NUMBER 로
 * 처리한 데이터의 번호다. 즉, 사용자에게 보내야 하는 번호다.
 * 
 * @param in        transmission_control_buffer_in_t    receive buffer object
 * 
 * @return          uint32_t    sequence
 */
#define transmission_control_buffer_in_acknowledge_cal(in)                      ((in)->sequence)

/**
 * 전달 받은 세그먼트의 SEQUENCE 번호에 수신받은 데이터 길이를 더하여 마지막으로 수신한 값으로 설정한다.
 * 이 함수를 호출할 때는 SEQUENCE 번호가 유효한 번호여야 한다.
 * 앞에 버퍼가 존재해야 하지만 그렇지 못하다면 홀을 만들고 버퍼의 ACKNOWEDGE 는 설정하지 않는다.
 * 
 * SEQ, ACK 번호에 문제가 발생하면 RESET 을 보내기 때문에, 이 함수가 호출되는 시점에서는 WINDOW 사이즈를 넘어가지 않는다고 판단한다.
 * 
 * @param in        transmission_control_buffer_in_t    receive buffer object
 */
#define transmission_control_buffer_in_append(in, node)                         (transmission_control_buffer_in_append(in, node))



/**
 * 
 * @todo            컨트롤 블록을 바로 삭제하지 말고, 삭제 큐에 삽입한 후에,
 *                  TCP QUIET TIME 이후에 삭제하도록 하자.
 *                  - 타이머
 *                  - 해쉬테이블 삭제 큐 노드
 *                  - 
 * 
 * Inherited hashtable_node_t
 */
___extend(hashtable_node_t)
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

    struct {
        transmission_control_buffer_t * in;      // HOLE 을 지원하는 버퍼를 만들고, 한 번에 SEND 하도록 혹은 버퍼 노드 교체만 이루어지도록 ,...
        transmission_control_buffer_t * out;     // SEGMENT 크기로 자를 수 있는 버퍼, 하나의 의미 있는 IP 패킷을 담는다.
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
    
    int32_t (*out)(transmission_control_block_t *, transmission_control_buffer_out_t *);
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

#define transmission_control_window_size_init                       (65536 / 2)



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

extern int32_t transmission_control_block_remote_sequence_update(transmission_control_block_t * block, transmission_control_protocol_context_t * context);

#define transmission_control_block_sequence_set(block, v)               ((block)->buffer.out->sequence = v)
#define transmission_control_block_sequence_get(block)                  ((block)->buffer.out->sequence)

/**
 * LOCAL 에서 처리한 SEQUENCE NUMBER, 이전의 값이 오면, 패킷 DROP 을 한다.
 * 다만, 데이터가 존재하고, 예전의...
 */
#define transmission_control_block_acknowledge_set(block, v)            ((block)->buffer.in->acknowledge = v)
#define transmission_control_block_acknowledge_get(block)               ((block)->buffer.in->acknowledge)

/**
 * REMOTE SEQUENCE 는 
 * 
 * 
 * @note        이 함수는 SYN 에서만 호출하도록 하자. 그 다음부터는 UPDATE 함수를 호출하도록 하여
 *              SEQUENCE NUMBER, ACKNOWLEDGE NUMBER 를 호출할 수 있도록 하자.
 * 
 * @param in    block | transmission_control_block_t *  transmission control block
 * @param in    v     | uint32_t                        remote sequence number
 * 
 * @return      uint32_t | affected remote sequence number
 */
#define transmission_control_block_remote_sequence_set(block, v)            ((block)->buffer.in->sequence = v)
#define transmission_control_block_remote_sequence_get(block)               ((block)->buffer.in->sequence)
#define transmission_control_block_remote_acknowledge_set(block, v)         ((block)->buffer.out->acknowledge = v)
#define transmission_control_block_remote_acknowledge_get(block)            ((block)->buffer.out->acknowledge)

#define transmission_control_block_window_set(block, v)                     ((block)->buffer.out->window = v)
#define transmission_control_block_window_get(block)                        ((block)->buffer.out->window)
// #define transmission_control_block_window_cal(block)                        ()
#define transmission_control_block_remote_window_set(block, v)              ((block)->buffer.in->window = v)
#define transmission_control_block_remote_window_get(block)                 ((block)->buffer.in->window)

#define transmission_control_block_maximum_segment_set(block, v)            (transmission_control_buffer_maximum_size_set((block)->buffer.out, v))
#define transmission_control_block_maximum_segment_get(block)               (transmission_control_buffer_maximum_size_get((block)->buffer.out))
#define transmission_control_block_remote_maximum_segment_set(block, v)     (transmission_control_buffer_maximum_size_set((block)->buffer.in, v))
#define transmission_control_block_remote_maximum_segment_get(block)        (transmission_control_buffer_maximum_size_get((block)->buffer.in))

#define transmission_control_block_window_scale_set(block, v)               ((block)->buffer.out->scale = ((v) > 14 ? 14 : (v)))
#define transmission_control_block_window_scale_get(block)                  ((block)->buffer.out->scale)
#define transmission_control_block_remote_window_scale_set(block, v)        ((block)->buffer.in->scale = ((v) > 14 ? 14 : (v)))
#define transmission_control_block_remote_window_scale_get(block)           ((block)->buffer.in->scale)

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

#define transmission_control_protocol_module_maximum_segment_size                       1460
#define transmission_control_protocol_module_scale_factor                               8
#define transmission_control_protocol_module_window_size                                64240

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

    struct {
        uint16_t segment;
    } maximum;

    uint8_t scale;
    uint16_t window;
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
#define transmission_control_protocol_module_maximum_segment_get(module)                                        ((module)->maximum.segment)
#define transmission_control_protocol_module_window_get(module)                                                 ((module)->window)
#define transmission_control_protocol_module_scale_get(module)                                                  ((module)->scale)

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

extern int32_t transmission_control_protocol_context_func_check_acceptable_seq(transmission_control_protocol_context_t * context);

// extern int32_t transmssion_control_protocol_context_is_accept_syn(transmission_control_protocol_context_t * context);
// extern void transmission_control_protocol_context_func_buffer_reserve(transmission_control_protocol_context_t * context, uint64_t n);

#define transmission_control_protocol_context_buffer_reversal_reserve(context, n)               (protocol_context_buffer_reversal_reserve(context, n))
#define transmission_control_protocol_context_buffer_reversal_push(context, data, datalen)      (protocol_context_buffer_reversal_push(context, data, datalen))

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

#define transmission_control_protocol_context_option_begin(context)                             ((context)->option)
#define transmission_control_protocol_context_option_end(context, option)                       (((context)->option == nil || *(option) == 0 || (((uint8_t *)((context)->packet) + ((context)->headerlen)) <= (option))) ? true : false)
#define transmission_control_protocol_context_option_next(option)                               (*(option) == 0 ? nil : (*(option) == 1 ? ((option) + 1) : (option) + *((option) + 1)))


#define transmission_control_protocol_context_check_acceptable_seq(context)                     (transmission_control_protocol_context_func_check_acceptable_seq(context))

/**
 * Check incoming segment acknowledgment acceptibility.
 * 
 * @param in        context | transmission_control_protocol_context_t * | incoming segment.
 * 
 * @return          bool    | If return true, segment acknowledgment is acceptable, otherwise, segment acknowledgment is not acceptable.
 */
#define transmission_control_protocol_context_check_acceptable_ack(context)                     transmission_control_check_acceptable_ack(transmission_control_block_remote_acknowledge_get((context)->block), transmission_control_block_sequence_get((context)->block), transmission_control_protocol_context_acknowledge_get(context))

struct transmission_control_protocol_option_maximum_segment_size {
    uint8_t kind;
    uint8_t length;
    uint16_t size;
};

struct transmission_control_protocol_option_window_scale {
    uint8_t kind;
    uint8_t length;
    uint8_t size;
    uint8_t pad;
};

#endif // __SNORLAX__PROTOCOL_INTERNET_TRANSMISSION_CONTROL__H__
