#include "../message.h"

static internet_control_message_protocol_version6_context_t * internet_control_message_protocol_version6_context_func_rem(internet_control_message_protocol_version6_context_t * context);
static int32_t internet_control_message_protocol_version6_context_func_valid(internet_control_message_protocol_version6_context_t * context);

typedef uint8_t * (*internet_control_message_protocol_version6_context_func_addrptr_t)(internet_control_message_protocol_version6_context_t *, uint32_t);
typedef void (*internet_control_message_protocol_version6_context_func_checksum_build_t)(internet_control_message_protocol_version6_context_t *, const uint8_t *, uint64_t);

static internet_control_message_protocol_version6_context_func_t func = {
    internet_control_message_protocol_version6_context_func_rem,
    internet_control_message_protocol_version6_context_func_valid,
    (internet_control_message_protocol_version6_context_func_addrptr_t) protocol_context_func_addrptr,
    (internet_control_message_protocol_version6_context_func_checksum_build_t) protocol_context_func_checksum_build
};

extern internet_control_message_protocol_version6_context_t * internet_control_message_protocol_version6_context_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_packet_t * packet, uint64_t packetlen, uint64_t * bufferlen) {
    

    if(internet_control_message_protocol_version6_length_min <= packetlen) {
        switch(packet->type) {
            case internet_control_message_protocol_version6_type_destination_unreachable:   return (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_destination_unreachable_gen(module, parent, (internet_control_message_protocol_version6_destination_unreachable_t *) packet, packetlen, bufferlen);
            case internet_control_message_protocol_version6_type_packet_too_big:            return (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_packet_too_big_gen(module, parent, (internet_control_message_protocol_version6_packet_too_big_t *) packet, packetlen, bufferlen);
            case internet_control_message_protocol_version6_type_time_exceeded:             return (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_time_exceeded_gen(module, parent, (internet_control_message_protocol_version6_time_exceeded_t *) packet, packetlen, bufferlen);
            case internet_control_message_protocol_version6_type_parameter_problem:         return (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_parameter_problem_gen(module, parent, (internet_control_message_protocol_version6_parameter_problem_t *) packet, packetlen, bufferlen);
            case internet_control_message_protocol_version6_type_echo_request:              return (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_echo_gen(module, parent, (internet_control_message_protocol_version6_echo_t *) packet, packetlen, bufferlen);
            case internet_control_message_protocol_version6_type_echo_reply:                return (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_echo_gen(module, parent, (internet_control_message_protocol_version6_echo_t *) packet, packetlen, bufferlen);
            case internet_control_message_protocol_version6_type_router_solicitation:       return (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_router_solicitation_gen(module, parent, (internet_control_message_protocol_version6_router_solicitation_t *) packet, packetlen, bufferlen);
        }
    }

    internet_control_message_protocol_version6_context_t * context = (internet_control_message_protocol_version6_context_t *) calloc(1, sizeof(internet_control_message_protocol_version6_context_t));

    context->func = address_of(func);

    context->module = module;
    context->children = nil;
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;
    context->bufferlen = bufferlen;

    return context;
}

static internet_control_message_protocol_version6_context_t * internet_control_message_protocol_version6_context_func_rem(internet_control_message_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_control_message_protocol_version6_context_func_valid(internet_control_message_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return true;
}