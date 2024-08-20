#include "../../message.h"

typedef internet_control_message_protocol_version4_context_timestamp_t * (*internet_control_message_protocol_version4_context_timestamp_func_rem_t)(internet_control_message_protocol_version4_context_timestamp_t *);
typedef int32_t (*internet_control_message_protocol_version4_context_timestamp_func_valid_t)(internet_control_message_protocol_version4_context_timestamp_t *);
typedef uint8_t * (*internet_control_message_protocol_version4_context_timestamp_func_addrptr_t)(internet_control_message_protocol_version4_context_timestamp_t *, uint32_t);

static internet_control_message_protocol_version4_context_timestamp_func_t func = {
    (internet_control_message_protocol_version4_context_timestamp_func_rem_t) internet_control_message_protocol_version4_context_func_rem,
    (internet_control_message_protocol_version4_context_timestamp_func_valid_t) internet_control_message_protocol_version4_context_func_valid,
    (internet_control_message_protocol_version4_context_timestamp_func_addrptr_t) protocol_context_func_addrptr
};

extern internet_control_message_protocol_version4_context_timestamp_t * internet_control_message_protocol_version4_context_timestamp_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_timestamp_t * packet, uint64_t packetlen) {
    internet_control_message_protocol_version4_context_timestamp_t * context = (internet_control_message_protocol_version4_context_timestamp_t *) calloc(1, sizeof(internet_control_message_protocol_version4_context_timestamp_t));

    context->func = address_of(func);
    context->module = module;
    context->children = nil;
    context->parent = parent;
    context->message = packet;
    context->messagelen = packetlen;

    return context;
}
