/**
 * @file        snorlax/protocol/internet/version4/control/message.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 4, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_VERSION4_CONTROL_MESSAGE__H__
#define   __SNORLAX__PROTOCOL_INTERNET_VERSION4_CONTROL_MESSAGE__H__

#include <snorlax.h>
#include <snorlax/protocol.h>

struct internet_protocol_version4_context;
struct internet_protocol_version4_module;
typedef struct internet_protocol_version4_context internet_protocol_version4_context_t;
typedef struct internet_protocol_version4_module internet_protocol_version4_module_t;

#define internet_control_message_protocol_version4_message_length_min                       8

#define internet_control_message_protocol_version4_message_type_echo_reply                  0
#define internet_control_message_protocol_version4_message_type_destination_unreachable     3
#define internet_control_message_protocol_version4_message_type_source_quench               4
#define internet_control_message_protocol_version4_message_type_redirect                    5
#define internet_control_message_protocol_version4_message_type_echo                        8
#define internet_control_message_protocol_version4_message_type_time_exceeded               11
#define internet_control_message_protocol_version4_message_type_parameter_problem           12
#define internet_control_message_protocol_version4_message_type_timestamp                   13
#define internet_control_message_protocol_version4_message_type_timestamp_reply             14
#define internet_control_message_protocol_version4_message_type_information_request         15
#define internet_control_message_protocol_version4_message_type_information_reply           16

struct internet_control_message_protocol_version4_packet;
struct internet_control_message_protocol_version4_destination_unreachable_message;
struct internet_control_message_protocol_version4_time_exceeded_message;
struct internet_control_message_protocol_version4_parameter_problem_message;
struct internet_control_message_protocol_version4_source_quench_message;
struct internet_control_message_protocol_version4_redirect_message;
struct internet_control_message_protocol_version4_echo_message;
struct internet_control_message_protocol_version4_timestamp_message;
struct internet_control_message_protocol_version4_information_message;

struct internet_control_message_protocol_version4_module;
struct internet_control_message_protocol_version4_module_func;
struct internet_control_message_protocol_version4_context;
struct internet_control_message_protocol_version4_context_func;

typedef struct internet_control_message_protocol_version4_packet internet_control_message_protocol_version4_packet_t;
typedef struct internet_control_message_protocol_version4_destination_unreachable_message internet_control_message_protocol_version4_destination_unreachable_message_t;
typedef struct internet_control_message_protocol_version4_time_exceeded_message internet_control_message_protocol_version4_time_exceeded_message_t;
typedef struct internet_control_message_protocol_version4_parameter_problem_message internet_control_message_protocol_version4_parameter_problem_message_t;
typedef struct internet_control_message_protocol_version4_source_quench_message internet_control_message_protocol_version4_source_quench_message_t;
typedef struct internet_control_message_protocol_version4_redirect_message internet_control_message_protocol_version4_redirect_message_t;
typedef struct internet_control_message_protocol_version4_echo_message internet_control_message_protocol_version4_echo_message_t;
typedef struct internet_control_message_protocol_version4_timestamp_message internet_control_message_protocol_version4_timestamp_message_t;
typedef struct internet_control_message_protocol_version4_information_message internet_control_message_protocol_version4_information_message_t;

typedef struct internet_control_message_protocol_version4_module internet_control_message_protocol_version4_module_t;
typedef struct internet_control_message_protocol_version4_module_func internet_control_message_protocol_version4_module_func_t;
typedef struct internet_control_message_protocol_version4_context internet_control_message_protocol_version4_context_t;
typedef struct internet_control_message_protocol_version4_context_func internet_control_message_protocol_version4_context_func_t;

struct internet_control_message_protocol_version4_packet {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
};

struct internet_control_message_protocol_version4_destination_unreachable_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t unused;
};

struct internet_control_message_protocol_version4_time_exceeded_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t used;
};

struct internet_control_message_protocol_version4_parameter_problem_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint8_t pointer;
    uint32_t unused:24;
};

struct internet_control_message_protocol_version4_source_quench_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t used;
};

struct internet_control_message_protocol_version4_redirect_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t gateway;
};

struct internet_control_message_protocol_version4_echo_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

struct internet_control_message_protocol_version4_timestamp_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
    struct {
        uint32_t originate;
        uint32_t receive;
        uint32_t transmit;
    } timestamp;
};

struct internet_control_message_protocol_version4_information_message {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

extern int32_t internet_control_message_protocol_version4_message_length_validate(uint8_t type, uint64_t packetlen);

typedef uint64_t (*internet_control_message_protocol_version4_context_handler_t)(void);

struct internet_control_message_protocol_version4_module {
    internet_control_message_protocol_version4_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;
};

struct internet_control_message_protocol_version4_module_func {
    internet_control_message_protocol_version4_module_t * (*rem)(internet_control_message_protocol_version4_module_t *);
    int32_t (*deserialize)(internet_control_message_protocol_version4_module_t *, protocol_packet_t *, uint32_t, internet_protocol_version4_context_t *, internet_control_message_protocol_version4_context_t **);
    int32_t (*serialize)(internet_control_message_protocol_version4_module_t *, internet_protocol_version4_context_t *, internet_control_message_protocol_version4_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(internet_control_message_protocol_version4_module_t *, FILE *, internet_control_message_protocol_version4_context_t *);
};

extern internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4_module_gen(void);

#define internet_control_message_protocol_version4_module_rem(module)                                                  ((module)->func->rem(module))
#define internet_control_message_protocol_version4_module_deserialize(module, packet, packetlen, parent, context)      ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_control_message_protocol_version4_module_serialize(module, parent, context, packet, packetlen)        ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_control_message_protocol_version4_module_debug(module, stream, context)                               ((module)->func->debug(module, stream, context))

struct internet_control_message_protocol_version4_context {
    internet_control_message_protocol_version4_context_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    union {
        internet_control_message_protocol_version4_packet_t * packet;
        internet_control_message_protocol_version4_destination_unreachable_message_t * destination_unreachable;
        internet_control_message_protocol_version4_time_exceeded_message_t * time_exceeded;
        internet_control_message_protocol_version4_parameter_problem_message_t * parameter_problem;
        internet_control_message_protocol_version4_source_quench_message_t * source_quench;
        internet_control_message_protocol_version4_redirect_message_t * redirect;
        internet_control_message_protocol_version4_echo_message_t * echo;
        internet_control_message_protocol_version4_timestamp_message_t * timestamp;
        internet_control_message_protocol_version4_information_message_t * information;
    } message;
    
    uint64_t packetlen;
};

struct internet_control_message_protocol_version4_context_func {
    internet_control_message_protocol_version4_context_t * (*rem)(internet_control_message_protocol_version4_context_t *);
};

extern internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_gen(internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_packet_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_rem(context)     ((context)->func->rem(context))

#define internet_control_message_protocol_version4_context_error_set(context, v)        ((context)->error = v)
#define internet_control_message_protocol_version4_context_error_get(context)           ((context)->error)

#define internet_control_message_protocol_version4_context_type_get(context)            ((context)->message.packet->type)

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION4_CONTROL_MESSAGE__H__
