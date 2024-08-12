/**
 * @file        snorlax/protocol/internet/version6/control/message.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 5, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_VERSION6_CONTROL_MESSAGE__H__
#define   __SNORLAX__PROTOCOL_INTERNET_VERSION6_CONTROL_MESSAGE__H__

#include <snorlax.h>
#include <snorlax/protocol.h>

struct internet_protocol_version6_module;
struct internet_protocol_version6_context;

#define internet_control_message_protocol_version6_message_length_min                           4

#define internet_control_message_protocol_version6_message_type_destination_unreachable         1
#define internet_control_message_protocol_version6_message_type_packet_too_big                  2
#define internet_control_message_protocol_version6_message_type_time_exceeded                   3
#define internet_control_message_protocol_version6_message_type_parameter_problem               4
#define internet_control_message_protocol_version6_message_type_echo_request                    128
#define internet_control_message_protocol_version6_message_type_echo_reply                      129

#define internet_control_message_protocol_version6_message_type_router_solicitation             133

struct internet_control_message_protocol_version6_packet;
struct internet_control_message_protocol_version6_destination_unreachable;
struct internet_control_message_protocol_version6_packet_too_big;
struct internet_control_message_protocol_version6_time_exceeded;
struct internet_control_message_protocol_version6_parameter_problem;
struct internet_control_message_protocol_version6_echo;
struct internet_control_message_protocol_version6_router_solicitation;

struct internet_control_message_protocol_version6_module;
struct internet_control_message_protocol_version6_module_func;
struct internet_control_message_protocol_version6_context;
struct internet_control_message_protocol_version6_context_func;

struct internet_control_message_protocol_version6_context_destination_unreachable;
struct internet_control_message_protocol_version6_context_destination_unreachable_func;
struct internet_control_message_protocol_version6_context_packet_too_big;
struct internet_control_message_protocol_version6_context_packet_too_big_func;
struct internet_control_message_protocol_version6_context_time_exceeded;
struct internet_control_message_protocol_version6_context_time_exceeded_func;
struct internet_control_message_protocol_version6_context_parameter_problem;
struct internet_control_message_protocol_version6_context_parameter_problem_func;
struct internet_control_message_protocol_version6_context_echo;
struct internet_control_message_protocol_version6_context_echo_func;
struct internet_control_message_protocol_version6_context_router_solicitation;
struct internet_control_message_protocol_version6_context_router_solicitation_func;

typedef struct internet_protocol_version6_module internet_protocol_version6_module_t;
typedef struct internet_protocol_version6_context internet_protocol_version6_context_t;

typedef struct internet_control_message_protocol_version6_packet internet_control_message_protocol_version6_packet_t;
typedef struct internet_control_message_protocol_version6_destination_unreachable internet_control_message_protocol_version6_destination_unreachable_t;
typedef struct internet_control_message_protocol_version6_packet_too_big internet_control_message_protocol_version6_packet_too_big_t;
typedef struct internet_control_message_protocol_version6_time_exceeded internet_control_message_protocol_version6_time_exceeded_t;
typedef struct internet_control_message_protocol_version6_parameter_problem internet_control_message_protocol_version6_parameter_problem_t;
typedef struct internet_control_message_protocol_version6_echo internet_control_message_protocol_version6_echo_t;
typedef struct internet_control_message_protocol_version6_router_solicitation internet_control_message_protocol_version6_router_solicitation_t;

typedef struct internet_control_message_protocol_version6_module internet_control_message_protocol_version6_module_t;
typedef struct internet_control_message_protocol_version6_module_func internet_control_message_protocol_version6_module_func_t;
typedef struct internet_control_message_protocol_version6_context internet_control_message_protocol_version6_context_t;
typedef struct internet_control_message_protocol_version6_context_func internet_control_message_protocol_version6_context_func_t;

typedef struct internet_control_message_protocol_version6_context_destination_unreachable internet_control_message_protocol_version6_context_destination_unreachable_t;
typedef struct internet_control_message_protocol_version6_context_destination_unreachable_func internet_control_message_protocol_version6_context_destination_unreachable_func_t;
typedef struct internet_control_message_protocol_version6_context_packet_too_big internet_control_message_protocol_version6_context_packet_too_big_t;
typedef struct internet_control_message_protocol_version6_context_packet_too_big_func internet_control_message_protocol_version6_context_packet_too_big_func_t;
typedef struct internet_control_message_protocol_version6_context_time_exceeded internet_control_message_protocol_version6_context_time_exceeded_t;
typedef struct internet_control_message_protocol_version6_context_time_exceeded_func internet_control_message_protocol_version6_context_time_exceeded_func_t;
typedef struct internet_control_message_protocol_version6_context_parameter_problem internet_control_message_protocol_version6_context_parameter_problem_t;
typedef struct internet_control_message_protocol_version6_context_parameter_problem_func internet_control_message_protocol_version6_context_parameter_problem_func_t;
typedef struct internet_control_message_protocol_version6_context_echo internet_control_message_protocol_version6_context_echo_t;
typedef struct internet_control_message_protocol_version6_context_echo_func internet_control_message_protocol_version6_context_echo_func_t;
typedef struct internet_control_message_protocol_version6_context_router_solicitation internet_control_message_protocol_version6_context_router_solicitation_t;
typedef struct internet_control_message_protocol_version6_context_router_solicitation_func internet_control_message_protocol_version6_context_router_solicitation_func_t;


struct internet_control_message_protocol_version6_packet {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
};

extern int32_t internet_control_message_protocol_version6_length_validate(uint8_t type, uint64_t packetlen);

#define internet_control_message_protocol_version6_code_destination_unreachable_no_route_to_destination                                         0
#define internet_control_message_protocol_version6_code_destination_unreachable_communication_with_destination_administratively_prohibited      1
#define internet_control_message_protocol_version6_code_destination_unreachable_beyond_scope_of_source_address                                  2
#define internet_control_message_protocol_version6_code_destination_unreachable_address_unreachable                                             3
#define internet_control_message_protocol_version6_code_destination_unreachable_port_unreachable                                                4
#define internet_control_message_protocol_version6_code_destination_unreachable_source_address_failed_ingress_egress_policy                     5
#define internet_control_message_protocol_version6_code_destination_unreachable_reject_route_to_destination                                     6

struct internet_control_message_protocol_version6_destination_unreachable {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t unused;
};

#define internet_control_message_protocol_version6_code_packet_too_big                                                                          0

struct internet_control_message_protocol_version6_packet_too_big {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t mtu;
};

struct internet_control_message_protocol_version6_time_exceeded {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t unused;
};

#define internet_control_message_protocol_version6_code_time_exceeded_hop_limit_exceeded                                                        0
#define internet_control_message_protocol_version6_code_time_exceeded_fragment_reassembly_time_exceeded                                         1

struct internet_control_message_protocol_version6_parameter_problem {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t pointer;
};

#define internet_control_message_protocol_version6_code_parameter_problem_erroneous_header_field                                                0
#define internet_control_message_protocol_version6_code_parameter_problem_unrecognized_next_header_type                                         1
#define internet_control_message_protocol_version6_code_parameter_problem_unrecognized_internet_protocol_version6_option                        2

struct internet_control_message_protocol_version6_echo {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

struct internet_control_message_protocol_version6_router_solicitation {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t reserved;
};

#define internet_control_message_protocol_version6_code_echo_message                                                                                    0

typedef uint64_t (*internet_control_message_protocol_version6_context_handler_t)(void);

struct internet_control_message_protocol_version6_module {
    internet_control_message_protocol_version6_module_func_t * func;
    sync_t * sync;
    ___reference protocol_module_map_t * map;
};

struct internet_control_message_protocol_version6_module_func {
    internet_control_message_protocol_version6_module_t * (*rem)(internet_control_message_protocol_version6_module_t *);
    int32_t (*deserialize)(internet_control_message_protocol_version6_module_t *, protocol_packet_t *, uint32_t, internet_protocol_version6_context_t *, internet_control_message_protocol_version6_context_t **);
    int32_t (*serialize)(internet_control_message_protocol_version6_module_t *, internet_protocol_version6_context_t *, internet_control_message_protocol_version6_context_t *, protocol_packet_t **, uint32_t *);
    void (*debug)(internet_control_message_protocol_version6_module_t *, FILE *, internet_control_message_protocol_version6_context_t *);
};

extern internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6_module_gen(void);

#define internet_control_message_protocol_version6_module_rem(module)                                                   ((module)->func->rem(module))
#define internet_control_message_protocol_version6_module_deserialize(module, packet, packetlen, parent, context)       ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_control_message_protocol_version6_module_serialize(module, parent, context, packet, packetlen)         ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_control_message_protocol_version6_module_debug(module, stream, context)                                ((module)->func->debug(module, stream, context))

struct internet_control_message_protocol_version6_context {
    internet_control_message_protocol_version6_context_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_packet_t * packet;
    uint64_t packetlen;

// union {
        
//          * destination_unreachable;
//         internet_control_message_protocol_version6_packet_too_big_t * packet_too_big;
//         internet_control_message_protocol_version6_time_exceeded_t * time_exceeded;
//         internet_control_message_protocol_version6_parameter_problem_t * parameter_problem;
//         internet_control_message_protocol_version6_echo_t * echo;
//         internet_control_message_protocol_version6_router_solicitation_t * router_solicitation;
//     } message;
};

struct internet_control_message_protocol_version6_context_func {
    internet_control_message_protocol_version6_context_t * (*rem)(internet_control_message_protocol_version6_context_t *);
};

extern internet_control_message_protocol_version6_context_t * internet_control_message_protocol_version6_context_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_packet_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_rem(context)                                 ((context)->func->rem(context))

#define internet_control_message_protocol_version6_context_type_get(context)                            ((context)->packet->type)
#define internet_control_message_protocol_version6_context_type_set(context, v)                         ((context)->packet->type = v)
#define internet_control_message_protocol_version6_context_code_get(context)                            ((context)->packet->code)
#define internet_control_message_protocol_version6_context_code_set(context, v)                         ((context)->packet->code = v)
#define internet_control_message_protocol_version6_context_checksum_get(context)                        ((context)->packet->checksum)
#define internet_control_message_protocol_version6_context_checksum_set(context, v)                     ((context)->packet->checksum = v)
#define internet_control_message_protocol_version6_context_error_get(context)                           ((context)->error)
#define internet_control_message_protocol_version6_context_error_set(context, v)                        ((context)->error = v)

struct internet_control_message_protocol_version6_context_destination_unreachable {
    internet_control_message_protocol_version6_context_destination_unreachable_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_destination_unreachable_t * packet;
    uint64_t packetlen;
};

struct internet_control_message_protocol_version6_context_destination_unreachable_func {
    internet_control_message_protocol_version6_context_destination_unreachable_t * (*rem)(internet_control_message_protocol_version6_context_destination_unreachable_t *);
};

extern internet_control_message_protocol_version6_context_destination_unreachable_t * internet_control_message_protocol_version6_context_destination_unreachable_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_destination_unreachable_t * packet, uint64_t packetlen);

struct internet_control_message_protocol_version6_context_packet_too_big {
    internet_control_message_protocol_version6_context_packet_too_big_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_packet_too_big_t * packet;
    uint64_t packetlen;
};

struct internet_control_message_protocol_version6_context_packet_too_big_func {
    internet_control_message_protocol_version6_context_packet_too_big_t * (*rem)(internet_control_message_protocol_version6_context_packet_too_big_t *);
};

extern internet_control_message_protocol_version6_context_packet_too_big_t * internet_control_message_protocol_version6_context_packet_too_big_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_packet_too_big_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_maximum_transmission_unit_get(context)       ((context)->packet->mtu)
#define internet_control_message_protocol_version6_context_maximum_transmission_unit_set(context, v)    ((context)->packet->mtu = v)

struct internet_control_message_protocol_version6_context_time_exceeded {
    internet_control_message_protocol_version6_context_time_exceeded_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_time_exceeded_t * packet;
    uint64_t packetlen;
};

struct internet_control_message_protocol_version6_context_time_exceeded_func {
    internet_control_message_protocol_version6_context_time_exceeded_t * (*rem)(internet_control_message_protocol_version6_context_time_exceeded_t *);
};

extern internet_control_message_protocol_version6_context_time_exceeded_t * internet_control_message_protocol_version6_context_time_exceeded_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_time_exceeded_t * packet, uint64_t packetlen);

struct internet_control_message_protocol_version6_context_parameter_problem {
    internet_control_message_protocol_version6_context_parameter_problem_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_parameter_problem_t * packet;
    uint64_t packetlen;
};

struct internet_control_message_protocol_version6_context_parameter_problem_func {
    internet_control_message_protocol_version6_context_parameter_problem_t * (*rem)(internet_control_message_protocol_version6_context_parameter_problem_t *);
};

extern internet_control_message_protocol_version6_context_parameter_problem_t * internet_control_message_protocol_version6_context_parameter_problem_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_parameter_problem_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_pointer_get(context)                         ((context)->packet->pointer)
#define internet_control_message_protocol_version6_context_pointer_set(context, v)                      ((context)->packet->pointer = v)

struct internet_control_message_protocol_version6_context_echo {
    internet_control_message_protocol_version6_context_echo_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_echo_t * packet;
    uint64_t packetlen;
};

struct internet_control_message_protocol_version6_context_echo_func {
    internet_control_message_protocol_version6_context_echo_t * (*rem)(internet_control_message_protocol_version6_context_echo_t *);
};

extern internet_control_message_protocol_version6_context_echo_t * internet_control_message_protocol_version6_context_echo_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_echo_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_identifier_get(context)                      ((context)->packet->identifier)
#define internet_control_message_protocol_version6_context_identifier_set(context, v)                   ((context)->packet->identifier = v)
#define internet_control_message_protocol_version6_context_sequence_get(context)                        ((context)->packet->sequence)
#define internet_control_message_protocol_version6_context_sequence_set(context, v)                     ((context)->packet->sequence = v)

// router_solicitation
struct internet_control_message_protocol_version6_context_router_solicitation {
    internet_control_message_protocol_version6_context_router_solicitation_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_router_solicitation_t * packet;
    uint64_t packetlen;
};

struct internet_control_message_protocol_version6_context_router_solicitation_func {
    internet_control_message_protocol_version6_context_router_solicitation_t * (*rem)(internet_control_message_protocol_version6_context_router_solicitation_t *);
};

extern internet_control_message_protocol_version6_context_router_solicitation_t * internet_control_message_protocol_version6_context_router_solicitation_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_router_solicitation_t * packet, uint64_t packetlen);

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION6_CONTROL_MESSAGE__H__
