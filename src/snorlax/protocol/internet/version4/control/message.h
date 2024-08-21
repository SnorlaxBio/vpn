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

#define internet_control_message_protocol_version4_length_min                       8

#define internet_control_message_protocol_version4_type_echo_reply                  0
#define internet_control_message_protocol_version4_type_destination_unreachable     3
#define internet_control_message_protocol_version4_type_source_quench               4
#define internet_control_message_protocol_version4_type_redirect                    5
#define internet_control_message_protocol_version4_type_echo                        8
#define internet_control_message_protocol_version4_type_time_exceeded               11
#define internet_control_message_protocol_version4_type_parameter_problem           12
#define internet_control_message_protocol_version4_type_timestamp                   13
#define internet_control_message_protocol_version4_type_timestamp_reply             14
#define internet_control_message_protocol_version4_type_information_request         15
#define internet_control_message_protocol_version4_type_information_reply           16

struct internet_control_message_protocol_version4_packet;
struct internet_control_message_protocol_version4_destination_unreachable;
struct internet_control_message_protocol_version4_time_exceeded;
struct internet_control_message_protocol_version4_parameter_problem;
struct internet_control_message_protocol_version4_source_quench;
struct internet_control_message_protocol_version4_redirect;
struct internet_control_message_protocol_version4_echo;
struct internet_control_message_protocol_version4_timestamp;
struct internet_control_message_protocol_version4_information;

struct internet_control_message_protocol_version4_module;
struct internet_control_message_protocol_version4_module_func;
struct internet_control_message_protocol_version4_context;
struct internet_control_message_protocol_version4_context_func;

struct internet_control_message_protocol_version4_context;
struct internet_control_message_protocol_version4_context_func;
struct internet_control_message_protocol_version4_context_destination_unreachable;
struct internet_control_message_protocol_version4_context_destination_unreachable_func;
struct internet_control_message_protocol_version4_context_time_exceeded;
struct internet_control_message_protocol_version4_context_time_exceeded_func;
struct internet_control_message_protocol_version4_context_parameter_problem;
struct internet_control_message_protocol_version4_context_parameter_problem_func;
struct internet_control_message_protocol_version4_context_source_quench;
struct internet_control_message_protocol_version4_context_source_quench_func;
struct internet_control_message_protocol_version4_context_redirect;
struct internet_control_message_protocol_version4_context_redirect_func;
struct internet_control_message_protocol_version4_context_echo;
struct internet_control_message_protocol_version4_context_echo_func;
struct internet_control_message_protocol_version4_context_timestamp;
struct internet_control_message_protocol_version4_context_timestamp_func;
struct internet_control_message_protocol_version4_context_information;
struct internet_control_message_protocol_version4_context_information_func;

typedef struct internet_control_message_protocol_version4_packet                                internet_control_message_protocol_version4_packet_t;
typedef struct internet_control_message_protocol_version4_destination_unreachable               internet_control_message_protocol_version4_destination_unreachable_t;
typedef struct internet_control_message_protocol_version4_time_exceeded                         internet_control_message_protocol_version4_time_exceeded_t;
typedef struct internet_control_message_protocol_version4_parameter_problem                     internet_control_message_protocol_version4_parameter_problem_t;
typedef struct internet_control_message_protocol_version4_source_quench                         internet_control_message_protocol_version4_source_quench_t;
typedef struct internet_control_message_protocol_version4_redirect                              internet_control_message_protocol_version4_redirect_t;
typedef struct internet_control_message_protocol_version4_echo                                  internet_control_message_protocol_version4_echo_t;
typedef struct internet_control_message_protocol_version4_timestamp                             internet_control_message_protocol_version4_timestamp_t;
typedef struct internet_control_message_protocol_version4_information                           internet_control_message_protocol_version4_information_t;

typedef struct internet_control_message_protocol_version4_module                                internet_control_message_protocol_version4_module_t;
typedef struct internet_control_message_protocol_version4_module_func                           internet_control_message_protocol_version4_module_func_t;
typedef struct internet_control_message_protocol_version4_context                               internet_control_message_protocol_version4_context_t;
typedef struct internet_control_message_protocol_version4_context_func                          internet_control_message_protocol_version4_context_func_t;
typedef struct internet_control_message_protocol_version4_context_destination_unreachable       internet_control_message_protocol_version4_context_destination_unreachable_t;
typedef struct internet_control_message_protocol_version4_context_destination_unreachable_func  internet_control_message_protocol_version4_context_destination_unreachable_func_t;
typedef struct internet_control_message_protocol_version4_context_time_exceeded                 internet_control_message_protocol_version4_context_time_exceeded_t;
typedef struct internet_control_message_protocol_version4_context_time_exceeded_func            internet_control_message_protocol_version4_context_time_exceeded_func_t;
typedef struct internet_control_message_protocol_version4_context_parameter_problem             internet_control_message_protocol_version4_context_parameter_problem_t;
typedef struct internet_control_message_protocol_version4_context_parameter_problem_func        internet_control_message_protocol_version4_context_parameter_problem_func_t;
typedef struct internet_control_message_protocol_version4_context_source_quench                 internet_control_message_protocol_version4_context_source_quench_t;
typedef struct internet_control_message_protocol_version4_context_source_quench_func            internet_control_message_protocol_version4_context_source_quench_func_t;
typedef struct internet_control_message_protocol_version4_context_redirect                      internet_control_message_protocol_version4_context_redirect_t;
typedef struct internet_control_message_protocol_version4_context_redirect_func                 internet_control_message_protocol_version4_context_redirect_func_t;
typedef struct internet_control_message_protocol_version4_context_echo                          internet_control_message_protocol_version4_context_echo_t;
typedef struct internet_control_message_protocol_version4_context_echo_func                     internet_control_message_protocol_version4_context_echo_func_t;
typedef struct internet_control_message_protocol_version4_context_timestamp                     internet_control_message_protocol_version4_context_timestamp_t;
typedef struct internet_control_message_protocol_version4_context_timestamp_func                internet_control_message_protocol_version4_context_timestamp_func_t;
typedef struct internet_control_message_protocol_version4_context_information                   internet_control_message_protocol_version4_context_information_t;
typedef struct internet_control_message_protocol_version4_context_information_func              internet_control_message_protocol_version4_context_information_func_t;

struct internet_control_message_protocol_version4_packet {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
};

struct internet_control_message_protocol_version4_destination_unreachable {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t unused;
};

struct internet_control_message_protocol_version4_time_exceeded {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t used;
};

struct internet_control_message_protocol_version4_parameter_problem {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint8_t pointer;
    uint32_t unused:24;
};

struct internet_control_message_protocol_version4_source_quench {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t used;
};

struct internet_control_message_protocol_version4_redirect {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t gateway;
};

struct internet_control_message_protocol_version4_echo {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

struct internet_control_message_protocol_version4_timestamp {
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

struct internet_control_message_protocol_version4_information {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

// TODO: UPGRADE: 이름이 별로 마음에 들지 않는다. 위치도 별로 마음에 들지 않는다.
extern int32_t internet_control_message_protocol_version4_length_validate(uint8_t type, uint64_t packetlen);

typedef int32_t (*internet_control_message_protocol_version4_context_handler_t)(internet_control_message_protocol_version4_module_t *, uint32_t, internet_protocol_version4_context_t *, internet_control_message_protocol_version4_context_t *);

struct internet_control_message_protocol_version4_module {
    internet_control_message_protocol_version4_module_func_t * func;
    sync_t * sync;
    uint16_t type;
    uint16_t addrlen;
    ___reference protocol_module_map_t * map;

    internet_control_message_protocol_version4_context_handler_t on;
};

struct internet_control_message_protocol_version4_module_func {
    internet_control_message_protocol_version4_module_t * (*rem)(internet_control_message_protocol_version4_module_t *);
    int32_t (*deserialize)(internet_control_message_protocol_version4_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version4_context_t *, internet_control_message_protocol_version4_context_t **);
    int32_t (*serialize)(internet_control_message_protocol_version4_module_t *, internet_protocol_version4_context_t *, internet_control_message_protocol_version4_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_control_message_protocol_version4_module_t *, FILE *, internet_control_message_protocol_version4_context_t *);
    int32_t (*in)(internet_control_message_protocol_version4_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version4_context_t *, internet_control_message_protocol_version4_context_t **);
    int32_t (*out)(internet_control_message_protocol_version4_module_t *, internet_control_message_protocol_version4_context_t *, protocol_path_node_t *);
};

extern internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4_module_gen(internet_control_message_protocol_version4_context_handler_t on);
extern int32_t internet_control_message_protocol_version4_module_func_on(internet_control_message_protocol_version4_module_t * module, uint32_t type, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t * context);

#define internet_control_message_protocol_version4_module_addrlen_get(module)                                           ((module)->addrlen)

#define internet_control_message_protocol_version4_module_rem(module)                                                   ((module)->func->rem(module))
#define internet_control_message_protocol_version4_module_deserialize(module, packet, packetlen, parent, context)       ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_control_message_protocol_version4_module_serialize(module, parent, context, packet, packetlen)         ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_control_message_protocol_version4_module_debug(module, stream, context)                                ((module)->func->debug(module, stream, context))
#define internet_control_message_protocol_version4_module_in(module, packet, packetlen, parent, context)                ((module)->func->in(module, packet, packetlen, parent, context))
#define internet_control_message_protocol_version4_module_out(module, context, node)                                    ((module)->func->out(module, context, node))

#define internet_control_message_protocol_version4_module_on(module, type, parent, context)                             ((module)->on(module, type, parent, context))

struct internet_control_message_protocol_version4_context {
    internet_control_message_protocol_version4_context_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_packet_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_func {
    internet_control_message_protocol_version4_context_t * (*rem)(internet_control_message_protocol_version4_context_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_packet_t * packet, uint64_t packetlen);
extern internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_func_rem(internet_control_message_protocol_version4_context_t * context);
extern int32_t internet_control_message_protocol_version4_context_func_valid(internet_control_message_protocol_version4_context_t * context);

#define internet_control_message_protocol_version4_context_rem(context)                 ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_valid(context)               ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_addrptr(context, type)       ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_error_set(context, v)        ((context)->error = v)
#define internet_control_message_protocol_version4_context_error_get(context)           ((context)->error)

#define internet_control_message_protocol_version4_context_type_get(context)            ((context)->message->type)

struct internet_control_message_protocol_version4_context_destination_unreachable {
    internet_control_message_protocol_version4_context_destination_unreachable_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_destination_unreachable_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_destination_unreachable_func {
    internet_control_message_protocol_version4_context_destination_unreachable_t * (*rem)(internet_control_message_protocol_version4_context_destination_unreachable_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_destination_unreachable_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_destination_unreachable_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_destination_unreachable_t * internet_control_message_protocol_version4_context_destination_unreachable_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_destination_unreachable_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_destination_unreachable_rem(context)             ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_destination_unreachable_valid(context)           ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_destination_unreachable_addrptr(context, type)   ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_destination_unreachable_error_set(context, v)    ((context)->error = v)
#define internet_control_message_protocol_version4_context_destination_unreachable_error_get(context)       ((context)->error)

#define internet_control_message_protocol_version4_context_destination_unreachable_type_get(context)        ((context)->message->type)

struct internet_control_message_protocol_version4_context_time_exceeded {
    internet_control_message_protocol_version4_context_time_exceeded_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_time_exceeded_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_time_exceeded_func {
    internet_control_message_protocol_version4_context_time_exceeded_t * (*rem)(internet_control_message_protocol_version4_context_time_exceeded_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_time_exceeded_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_time_exceeded_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_time_exceeded_t * internet_control_message_protocol_version4_context_time_exceeded_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_time_exceeded_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_time_exceeded_rem(context)               ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_time_exceeded_valid(context)             ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_time_exceeded_addrptr(context, type)     ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_time_exceeded_error_set(context, v)      ((context)->error = v)
#define internet_control_message_protocol_version4_context_time_exceeded_error_get(context)         ((context)->error)

#define internet_control_message_protocol_version4_context_time_exceeded_type_get(context)          ((context)->message->type)

struct internet_control_message_protocol_version4_context_parameter_problem {
    internet_control_message_protocol_version4_context_parameter_problem_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_parameter_problem_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_parameter_problem_func {
    internet_control_message_protocol_version4_context_parameter_problem_t * (*rem)(internet_control_message_protocol_version4_context_parameter_problem_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_parameter_problem_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_parameter_problem_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_parameter_problem_t * internet_control_message_protocol_version4_context_parameter_problem_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_parameter_problem_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_parameter_problem_rem(context)               ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_parameter_problem_valid(context)             ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_parameter_problem_addrptr(context, type)     ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_parameter_problem_error_set(context, v)      ((context)->error = v)
#define internet_control_message_protocol_version4_context_parameter_problem_error_get(context)         ((context)->error)

#define internet_control_message_protocol_version4_context_parameter_problem_type_get(context)          ((context)->message->type)

struct internet_control_message_protocol_version4_context_source_quench {
    internet_control_message_protocol_version4_context_source_quench_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_source_quench_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_source_quench_func {
    internet_control_message_protocol_version4_context_source_quench_t * (*rem)(internet_control_message_protocol_version4_context_source_quench_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_source_quench_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_source_quench_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_source_quench_t * internet_control_message_protocol_version4_context_source_quench_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_source_quench_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_source_quench_rem(context)               ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_source_quench_valid(context)             ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_source_quench_addrptr(context, type)     ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_source_quench_error_set(context, v)      ((context)->error = v)
#define internet_control_message_protocol_version4_context_source_quench_error_get(context)         ((context)->error)

#define internet_control_message_protocol_version4_context_source_quench_type_get(context)          ((context)->message->type)

struct internet_control_message_protocol_version4_context_redirect {
    internet_control_message_protocol_version4_context_redirect_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_redirect_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_redirect_func {
    internet_control_message_protocol_version4_context_redirect_t * (*rem)(internet_control_message_protocol_version4_context_redirect_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_redirect_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_redirect_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_redirect_t * internet_control_message_protocol_version4_context_redirect_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_redirect_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_redirect_rem(context)                ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_redirect_valid(context)              ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_redirect_addrptr(context, type)      ((context)->func->addrptr(context))

#define internet_control_message_protocol_version4_context_redirect_error_set(context, v)       ((context)->error = v)
#define internet_control_message_protocol_version4_context_redirect_error_get(context)          ((context)->error)

#define internet_control_message_protocol_version4_context_redirect_type_get(context)           ((context)->message->type)

struct internet_control_message_protocol_version4_context_echo {
    internet_control_message_protocol_version4_context_echo_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_echo_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_echo_func {
    internet_control_message_protocol_version4_context_echo_t * (*rem)(internet_control_message_protocol_version4_context_echo_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_echo_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_echo_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_echo_t * internet_control_message_protocol_version4_context_echo_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_echo_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_echo_rem(context)                ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_echo_valid(context)              ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_echo_addrptr(context, type)      ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_echo_error_set(context, v)       ((context)->error = v)
#define internet_control_message_protocol_version4_context_echo_error_get(context)          ((context)->error)

#define internet_control_message_protocol_version4_context_echo_type_get(context)           ((context)->message->type)

struct internet_control_message_protocol_version4_context_timestamp {
    internet_control_message_protocol_version4_context_timestamp_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_timestamp_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_timestamp_func {
    internet_control_message_protocol_version4_context_timestamp_t * (*rem)(internet_control_message_protocol_version4_context_timestamp_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_timestamp_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_timestamp_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_timestamp_t * internet_control_message_protocol_version4_context_timestamp_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_timestamp_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_timestamp_rem(context)               ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_timestamp_valid(context)             ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_timestamp_addrptr(context, type)     ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_timestamp_error_set(context, v)      ((context)->error = v)
#define internet_control_message_protocol_version4_context_timestamp_error_get(context)         ((context)->error)

#define internet_control_message_protocol_version4_context_timestamp_type_get(context)          ((context)->message->type)

struct internet_control_message_protocol_version4_context_information {
    internet_control_message_protocol_version4_context_information_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version4_module_t * module;
    internet_protocol_version4_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version4_information_t * message;
    uint64_t messagelen;
    uint64_t bufferlen;
};

struct internet_control_message_protocol_version4_context_information_func {
    internet_control_message_protocol_version4_context_information_t * (*rem)(internet_control_message_protocol_version4_context_information_t *);
    int32_t (*valid)(internet_control_message_protocol_version4_context_information_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version4_context_information_t *, uint32_t);
};

extern internet_control_message_protocol_version4_context_information_t * internet_control_message_protocol_version4_context_information_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_information_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version4_context_information_rem(context)                 ((context)->func->rem(context))
#define internet_control_message_protocol_version4_context_information_valid(context)               ((context)->func->valid(context))
#define internet_control_message_protocol_version4_context_information_addrptr(context, type)       ((context)->func->addrptr(context, type))

#define internet_control_message_protocol_version4_context_information_error_set(context, v)        ((context)->error = v)
#define internet_control_message_protocol_version4_context_information_error_get(context)           ((context)->error)

#define internet_control_message_protocol_version4_context_information_type_get(context)            ((context)->message->type)

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION4_CONTROL_MESSAGE__H__
