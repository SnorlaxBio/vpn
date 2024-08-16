#include "../../message.h"

typedef internet_control_message_protocol_version4_context_information_t * (*internet_control_message_protocol_version4_context_information_func_rem_t)(internet_control_message_protocol_version4_context_information_t *);
typedef int32_t (*internet_control_message_protocol_version4_context_information_func_valid_t)(internet_control_message_protocol_version4_context_information_t *);

static internet_control_message_protocol_version4_context_information_func_t func = {
    (internet_control_message_protocol_version4_context_information_func_rem_t) internet_control_message_protocol_version4_context_func_rem,
    (internet_control_message_protocol_version4_context_information_func_valid_t) internet_control_message_protocol_version4_context_func_valid,
};

extern internet_control_message_protocol_version4_context_information_t * internet_control_message_protocol_version4_context_information_gen(internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_information_t * packet, uint64_t packetlen) {
    internet_control_message_protocol_version4_context_information_t * context = (internet_control_message_protocol_version4_context_information_t *) calloc(1, sizeof(internet_control_message_protocol_version4_context_information_t));

    context->func = address_of(func);
    context->children = nil;
    context->parent = parent;
    context->message = packet;
    context->messagelen = packetlen;

    return context;
}
