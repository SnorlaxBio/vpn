#include "../../message.h"

typedef internet_control_message_protocol_version4_context_information_t * (*internet_control_message_protocol_version4_context_information_func_rem_t)(internet_control_message_protocol_version4_context_information_t *);
typedef int32_t (*internet_control_message_protocol_version4_context_information_func_valid_t)(internet_control_message_protocol_version4_context_information_t *);
typedef uint8_t * (*internet_control_message_protocol_version4_context_information_func_addrptr_t)(internet_control_message_protocol_version4_context_information_t *, uint32_t);
typedef void (*internet_control_message_protocol_version4_context_information_func_checksum_build_t)(internet_control_message_protocol_version4_context_information_t *, const uint8_t *, uint64_t);

static internet_control_message_protocol_version4_context_information_func_t func = {
    (internet_control_message_protocol_version4_context_information_func_rem_t) internet_control_message_protocol_version4_context_func_rem,
    (internet_control_message_protocol_version4_context_information_func_valid_t) internet_control_message_protocol_version4_context_func_valid,
    (internet_control_message_protocol_version4_context_information_func_addrptr_t) protocol_context_func_addrptr,
    (internet_control_message_protocol_version4_context_information_func_checksum_build_t) protocol_context_func_checksum_build
};

extern internet_control_message_protocol_version4_context_information_t * internet_control_message_protocol_version4_context_information_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_information_t * packet, uint64_t packetlen, uint64_t * bufferlen) {
    internet_control_message_protocol_version4_context_information_t * context = (internet_control_message_protocol_version4_context_information_t *) calloc(1, sizeof(internet_control_message_protocol_version4_context_information_t));

    context->func = address_of(func);
    context->module = module;
    context->children = nil;
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;
    context->bufferlen = bufferlen;

    return context;
}
