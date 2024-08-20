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
#include <snorlax/protocol/internet/version6.h>

struct internet_protocol_version6_module;
struct internet_protocol_version6_context;

#define internet_control_message_protocol_version6_length_min                           4

#define internet_control_message_protocol_version6_type_destination_unreachable         1
#define internet_control_message_protocol_version6_type_packet_too_big                  2
#define internet_control_message_protocol_version6_type_time_exceeded                   3
#define internet_control_message_protocol_version6_type_parameter_problem               4
#define internet_control_message_protocol_version6_type_echo_request                    128
#define internet_control_message_protocol_version6_type_echo_reply                      129

#define internet_control_message_protocol_version6_type_router_solicitation             133
#define internet_control_message_protocol_version6_type_router_advertisement            134
#define internet_control_message_protocol_version6_type_neighbor_solicitation           135
#define internet_control_message_protocol_version6_type_neighbor_advertisement          136
#define internet_control_message_protocol_version6_type_redirect                        137

struct internet_control_message_protocol_version6_packet;
struct internet_control_message_protocol_version6_destination_unreachable;
struct internet_control_message_protocol_version6_packet_too_big;
struct internet_control_message_protocol_version6_time_exceeded;
struct internet_control_message_protocol_version6_parameter_problem;
struct internet_control_message_protocol_version6_echo;
struct internet_control_message_protocol_version6_router_solicitation;
struct internet_control_message_protocol_version6_router_advertisement;
struct internet_control_message_protocol_version6_neighbor_solicitation;
struct internet_control_message_protocol_version6_neighbor_advertisement;
struct internet_control_message_protocol_version6_redirect;

struct internet_control_message_protocol_version6_neighbor_discovery_option;
struct internet_control_message_protocol_version6_neighbor_discovery_option_link_layer_address;
struct internet_control_message_protocol_version6_neighbor_discovery_option_prefix_information;
struct internet_control_message_protocol_version6_neighbor_discovery_option_redirect_header;
struct internet_control_message_protocol_version6_neighbor_discovery_option_maximum_transmission_unit;
struct internet_control_message_protocol_version6_link_layer_address;
struct internet_control_message_protocol_version6_link_layer_address_ethernet;

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
struct internet_control_message_protocol_version6_context_router_advertisement;
struct internet_control_message_protocol_version6_context_router_advertisement_func;
struct internet_control_message_protocol_version6_context_neighbor_solicitation;
struct internet_control_message_protocol_version6_context_neighbor_solicitation_func;
struct internet_control_message_protocol_version6_context_neighbor_advertisement;
struct internet_control_message_protocol_version6_context_neighbor_advertisement_func;
struct internet_control_message_protocol_version6_context_redirect;
struct internet_control_message_protocol_version6_context_redirect_func;

typedef struct internet_protocol_version6_module internet_protocol_version6_module_t;
typedef struct internet_protocol_version6_context internet_protocol_version6_context_t;

typedef struct internet_control_message_protocol_version6_packet internet_control_message_protocol_version6_packet_t;
typedef struct internet_control_message_protocol_version6_destination_unreachable internet_control_message_protocol_version6_destination_unreachable_t;
typedef struct internet_control_message_protocol_version6_packet_too_big internet_control_message_protocol_version6_packet_too_big_t;
typedef struct internet_control_message_protocol_version6_time_exceeded internet_control_message_protocol_version6_time_exceeded_t;
typedef struct internet_control_message_protocol_version6_parameter_problem internet_control_message_protocol_version6_parameter_problem_t;
typedef struct internet_control_message_protocol_version6_echo internet_control_message_protocol_version6_echo_t;
typedef struct internet_control_message_protocol_version6_router_solicitation internet_control_message_protocol_version6_router_solicitation_t;
typedef struct internet_control_message_protocol_version6_router_advertisement internet_control_message_protocol_version6_router_advertisement_t;
typedef struct internet_control_message_protocol_version6_neighbor_solicitation internet_control_message_protocol_version6_neighbor_solicitation_t;
typedef struct internet_control_message_protocol_version6_neighbor_advertisement internet_control_message_protocol_version6_neighbor_advertisement_t;
typedef struct internet_control_message_protocol_version6_redirect internet_control_message_protocol_version6_redirect_t;

typedef struct internet_control_message_protocol_version6_neighbor_discovery_option internet_control_message_protocol_version6_neighbor_discovery_option_t;
typedef struct internet_control_message_protocol_version6_neighbor_discovery_option_link_layer_address internet_control_message_protocol_version6_neighbor_discovery_option_link_layer_address_t;
typedef struct internet_control_message_protocol_version6_neighbor_discovery_option_prefix_information internet_control_message_protocol_version6_neighbor_discovery_option_prefix_information_t;
typedef struct internet_control_message_protocol_version6_neighbor_discovery_option_redirect_header internet_control_message_protocol_version6_neighbor_discovery_option_redirect_header_t;
typedef struct internet_control_message_protocol_version6_neighbor_discovery_option_maximum_transmission_unit internet_control_message_protocol_version6_neighbor_discovery_option_maximum_transmission_unit_t;

typedef struct internet_control_message_protocol_version6_link_layer_address internet_control_message_protocol_version6_link_layer_address_t;
typedef struct internet_control_message_protocol_version6_link_layer_address_ethernet internet_control_message_protocol_version6_link_layer_address_ethernet_t;

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
typedef struct internet_control_message_protocol_version6_context_router_advertisement internet_control_message_protocol_version6_context_router_advertisement_t;
typedef struct internet_control_message_protocol_version6_context_router_advertisement_func internet_control_message_protocol_version6_context_router_advertisement_func_t;
typedef struct internet_control_message_protocol_version6_context_neighbor_solicitation internet_control_message_protocol_version6_context_neighbor_solicitation_t;
typedef struct internet_control_message_protocol_version6_context_neighbor_solicitation_func internet_control_message_protocol_version6_context_neighbor_solicitation_func_t;
typedef struct internet_control_message_protocol_version6_context_neighbor_advertisement internet_control_message_protocol_version6_context_neighbor_advertisement_t;
typedef struct internet_control_message_protocol_version6_context_neighbor_advertisement_func internet_control_message_protocol_version6_context_neighbor_advertisement_func_t;
typedef struct internet_control_message_protocol_version6_context_redirect internet_control_message_protocol_version6_context_redirect_t;
typedef struct internet_control_message_protocol_version6_context_redirect_func internet_control_message_protocol_version6_context_redirect_func_t;

struct internet_control_message_protocol_version6_packet {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_neighbor_discovery_option {
    uint8_t type;
    uint8_t length;
};

struct internet_control_message_protocol_version6_neighbor_discovery_option_link_layer_address {
    uint8_t type;
    uint8_t length;
};

struct internet_control_message_protocol_version6_neighbor_discovery_option_prefix_information {
    uint8_t type;
    uint8_t length;
    uint8_t prefixlen;
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t reserved1:6;
    uint8_t a:1;
    uint8_t l:1;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t l:1;
    uint8_t a:1;
    uint8_t reserved1:6;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    struct {
        uint32_t valid;
        uint32_t preferred;
    } lifetime;
    uint32_t reserved2;
    uint8_t prefix[16];
};

struct internet_control_message_protocol_version6_neighbor_discovery_option_redirect_header {
    uint8_t type;
    uint8_t length;
    uint64_t reserved:48;
    internet_protocol_version6_packet_t packet;
};

struct internet_control_message_protocol_version6_neighbor_discovery_option_maximum_transmission_unit {
    uint8_t type;
    uint8_t length;
    uint16_t reserved;
    uint32_t mtu;
};

struct internet_control_message_protocol_version6_link_layer_address {
    uint8_t value[8];
};

struct internet_control_message_protocol_version6_link_layer_address_ethernet {
    uint64_t value:48;
    uint64_t reserved:16;
};

#define internet_control_message_protocol_version6_neighbor_discovery_option_type_source_link_layer_address                                     1
#define internet_control_message_protocol_version6_neighbor_discovery_option_type_target_link_layer_address                                     2
#define internet_control_message_protocol_version6_neighbor_discovery_option_type_prefix_information                                            3
#define internet_control_message_protocol_version6_neighbor_discovery_option_type_redirect_header                                               4
#define internet_control_message_protocol_version6_neighbor_discovery_option_type_maximum_transmission_unit                                     5

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

#define internet_control_message_protocol_version6_code_echo_message                                                                                    0

struct internet_control_message_protocol_version6_router_solicitation {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t reserved;
};

struct internet_control_message_protocol_version6_router_advertisement {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint8_t curhoplimit;
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t reserved:6;
    uint8_t o:1;
    uint8_t m:1;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t m:1;
    uint8_t o:1;
    uint8_t reserved:6;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint16_t lifetime;
    uint32_t reachable;
    uint32_t retrans;
};

struct internet_control_message_protocol_version6_neighbor_solicitation {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t reserved;
    uint8_t target[16];
};

struct internet_control_message_protocol_version6_neighbor_advertisement {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint32_t reserved:29;
    uint8_t o:1;
    uint8_t s:1;
    uint8_t r:1;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t r:1;
    uint8_t s:1;
    uint8_t o:1;
    uint32_t reserved:29;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t target[16];
};

struct internet_control_message_protocol_version6_redirect {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t reserved;
    uint8_t target[16];
    uint8_t destination[16];
};

typedef int32_t (*internet_control_message_protocol_version6_context_handler_t)(internet_control_message_protocol_version6_module_t *, uint32_t, internet_protocol_version6_context_t *, internet_control_message_protocol_version6_context_t *);

struct internet_control_message_protocol_version6_module {
    internet_control_message_protocol_version6_module_func_t * func;
    sync_t * sync;
    uint16_t addrlen;
    ___reference protocol_module_map_t * map;

    internet_control_message_protocol_version6_context_handler_t on;
};

struct internet_control_message_protocol_version6_module_func {
    internet_control_message_protocol_version6_module_t * (*rem)(internet_control_message_protocol_version6_module_t *);
    int32_t (*deserialize)(internet_control_message_protocol_version6_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_control_message_protocol_version6_context_t **);
    int32_t (*serialize)(internet_control_message_protocol_version6_module_t *, internet_protocol_version6_context_t *, internet_control_message_protocol_version6_context_t *, protocol_packet_t **, uint64_t *);
    void (*debug)(internet_control_message_protocol_version6_module_t *, FILE *, internet_control_message_protocol_version6_context_t *);
    int32_t (*in)(internet_control_message_protocol_version6_module_t *, protocol_packet_t *, uint64_t, internet_protocol_version6_context_t *, internet_control_message_protocol_version6_context_t **);
//    int32_t (*out)(internet_control_message_protocol_version6_module_t *, internet_protocol_version6_context_t *, internet_control_message_protocol_version6_context_t *, protocol_packet_t **, uint64_t *);
};

extern internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6_module_gen(internet_control_message_protocol_version6_context_handler_t on);
extern int32_t internet_control_message_protocol_version6_module_func_on(internet_control_message_protocol_version6_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t * context);

#define internet_control_message_protocol_version6_module_addrlen_get(module)                                           ((module)->addrlen)

#define internet_control_message_protocol_version6_module_rem(module)                                                   ((module)->func->rem(module))
#define internet_control_message_protocol_version6_module_deserialize(module, packet, packetlen, parent, context)       ((module)->func->deserialize(module, packet, packetlen, parent, context))
#define internet_control_message_protocol_version6_module_serialize(module, parent, context, packet, packetlen)         ((module)->func->serialize(module, parent, context, packet, packetlen))
#define internet_control_message_protocol_version6_module_debug(module, stream, context)                                ((module)->func->debug(module, stream, context))
#define internet_control_message_protocol_version6_module_in(module, packet, packetlen, parent, context)                ((module)->func->in(module, packet, packetlen, parent, context))

#define internet_control_message_protocol_version6_module_on(module, type, parent, context)                             ((module)->on(module, type, parent, context))

struct internet_control_message_protocol_version6_context {
    internet_control_message_protocol_version6_context_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_packet_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_func {
    internet_control_message_protocol_version6_context_t * (*rem)(internet_control_message_protocol_version6_context_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_t * internet_control_message_protocol_version6_context_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_packet_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_rem(context)                                 ((context)->func->rem(context))
#define internet_control_message_protocol_version6_context_valid(context)                               ((context)->func->valid(context))
#define internet_control_message_protocol_version6_context_addrptr(context, type)                       ((context)->func->addrptr(context))

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
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_destination_unreachable_func {
    internet_control_message_protocol_version6_context_destination_unreachable_t * (*rem)(internet_control_message_protocol_version6_context_destination_unreachable_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_destination_unreachable_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_destination_unreachable_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_destination_unreachable_t * internet_control_message_protocol_version6_context_destination_unreachable_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_destination_unreachable_t * packet, uint64_t packetlen);

struct internet_control_message_protocol_version6_context_packet_too_big {
    internet_control_message_protocol_version6_context_packet_too_big_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_packet_too_big_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_packet_too_big_func {
    internet_control_message_protocol_version6_context_packet_too_big_t * (*rem)(internet_control_message_protocol_version6_context_packet_too_big_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_packet_too_big_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_packet_too_big_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_packet_too_big_t * internet_control_message_protocol_version6_context_packet_too_big_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_packet_too_big_t * packet, uint64_t packetlen);

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
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_time_exceeded_func {
    internet_control_message_protocol_version6_context_time_exceeded_t * (*rem)(internet_control_message_protocol_version6_context_time_exceeded_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_time_exceeded_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_time_exceeded_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_time_exceeded_t * internet_control_message_protocol_version6_context_time_exceeded_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_time_exceeded_t * packet, uint64_t packetlen);

struct internet_control_message_protocol_version6_context_parameter_problem {
    internet_control_message_protocol_version6_context_parameter_problem_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_parameter_problem_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_parameter_problem_func {
    internet_control_message_protocol_version6_context_parameter_problem_t * (*rem)(internet_control_message_protocol_version6_context_parameter_problem_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_parameter_problem_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_parameter_problem_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_parameter_problem_t * internet_control_message_protocol_version6_context_parameter_problem_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_parameter_problem_t * packet, uint64_t packetlen);

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
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_echo_func {
    internet_control_message_protocol_version6_context_echo_t * (*rem)(internet_control_message_protocol_version6_context_echo_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_echo_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_echo_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_echo_t * internet_control_message_protocol_version6_context_echo_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_echo_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_identifier_get(context)                      ((context)->packet->identifier)
#define internet_control_message_protocol_version6_context_identifier_set(context, v)                   ((context)->packet->identifier = v)
#define internet_control_message_protocol_version6_context_sequence_get(context)                        ((context)->packet->sequence)
#define internet_control_message_protocol_version6_context_sequence_set(context, v)                     ((context)->packet->sequence = v)

struct internet_control_message_protocol_version6_context_router_solicitation {
    internet_control_message_protocol_version6_context_router_solicitation_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_router_solicitation_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_router_solicitation_func {
    internet_control_message_protocol_version6_context_router_solicitation_t * (*rem)(internet_control_message_protocol_version6_context_router_solicitation_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_router_solicitation_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_router_solicitation_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_router_solicitation_t * internet_control_message_protocol_version6_context_router_solicitation_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_router_solicitation_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_router_solicitation_checksum_valid(context)      ((context)->checksum == (context)->packet->checksum)
#define internet_control_message_protocol_version6_context_router_solicitation_code_get(context)            ((context)->packet->code)
#define internet_control_message_protocol_version6_context_router_solicitation_length(context)              ((context)->packetlen)

struct internet_control_message_protocol_version6_context_router_advertisement {
    internet_control_message_protocol_version6_context_router_advertisement_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_router_advertisement_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_router_advertisement_func {
    internet_control_message_protocol_version6_context_router_advertisement_t * (*rem)(internet_control_message_protocol_version6_context_router_advertisement_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_router_advertisement_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_router_advertisement_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_router_advertisement_t * internet_control_message_protocol_version6_context_router_advertisemen_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_router_advertisement_t * packet, uint64_t packetlen);

#define internet_control_message_protocol_version6_context_router_advertisement_checksum_valid(context)             ((context)->checksum == (context)->packet->checksum)
#define internet_control_message_protocol_version6_context_router_advertisement_code_get(context)                   ((context)->packet->code)
#define internet_control_message_protocol_version6_context_router_advertisement_length(context)                     ((context)->packetlen)

#define internet_control_message_protocol_version6_context_router_advertisement_current_hop_limit_get(context)      ((context)->packet->curhoplimit)
#define internet_control_message_protocol_version6_context_router_advertisement_current_hop_limit_set(context, v)   ((context)->packet->curhoplimit = v)

struct internet_control_message_protocol_version6_context_neighbor_solicitation {
    internet_control_message_protocol_version6_context_neighbor_solicitation_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_neighbor_solicitation_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_neighbor_solicitation_func {
    internet_control_message_protocol_version6_context_neighbor_solicitation_t * (*rem)(internet_control_message_protocol_version6_context_neighbor_solicitation_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_neighbor_solicitation_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_neighbor_solicitation_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_neighbor_solicitation_t * internet_control_message_protocol_version6_context_neighbor_solicitation_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_neighbor_solicitation_t * packet, uint64_t packetlen);

struct internet_control_message_protocol_version6_context_neighbor_advertisement {
    internet_control_message_protocol_version6_context_neighbor_advertisement_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_neighbor_advertisement_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_neighbor_advertisement_func {
    internet_control_message_protocol_version6_context_neighbor_advertisement_t * (*rem)(internet_control_message_protocol_version6_context_neighbor_advertisement_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_neighbor_advertisement_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_neighbor_advertisement_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_neighbor_advertisement_t * internet_control_message_protocol_version6_context_neighbor_advertisement_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_neighbor_advertisement_t * packet, uint64_t packetlen);

struct internet_control_message_protocol_version6_context_redirect {
    internet_control_message_protocol_version6_context_redirect_func_t * func;
    sync_t * sync;
    internet_control_message_protocol_version6_module_t * module;
    internet_protocol_version6_context_t * parent;
    protocol_context_array_t * children;
    int32_t error;
    internet_control_message_protocol_version6_redirect_t * packet;
    uint64_t packetlen;
    uint64_t bufferlen;
    uint16_t checksum;
};

struct internet_control_message_protocol_version6_context_redirect_func {
    internet_control_message_protocol_version6_context_redirect_t * (*rem)(internet_control_message_protocol_version6_context_redirect_t *);
    int32_t (*valid)(internet_control_message_protocol_version6_context_redirect_t *);
    uint8_t * (*addrptr)(internet_control_message_protocol_version6_context_redirect_t *, uint32_t);
};

extern internet_control_message_protocol_version6_context_redirect_t * internet_control_message_protocol_version6_context_redirect_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_redirect_t * packet, uint64_t packetlen);

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION6_CONTROL_MESSAGE__H__
