#include "../message.h"

static internet_control_message_protocol_version6_context_t * internet_control_message_protocol_version6_context_func_rem(internet_control_message_protocol_version6_context_t * context);

static internet_control_message_protocol_version6_context_func_t func = {
    internet_control_message_protocol_version6_context_func_rem
};

extern internet_control_message_protocol_version6_context_t * internet_control_message_protocol_version6_context_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_packet_t * packet, uint64_t packetlen) {
    internet_control_message_protocol_version6_context_t * context = nil;

    if(internet_control_message_protocol_version6_message_length_min <= packetlen) {
        switch(packet->type) {
            case internet_control_message_protocol_version6_message_type_destination_unreachable:   context = (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_destination_unreachable_gen(parent, (internet_control_message_protocol_version6_destination_unreachable_t *) packet, packetlen);  break;
            case internet_control_message_protocol_version6_message_type_packet_too_big:            context = (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_packet_too_big_gen(parent, (internet_control_message_protocol_version6_packet_too_big_t *) packet, packetlen);                    break;
            case internet_control_message_protocol_version6_message_type_time_exceeded:             context = (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_time_exceeded_gen(parent, (internet_control_message_protocol_version6_time_exceeded_t *) packet, packetlen);                      break;
            case internet_control_message_protocol_version6_message_type_parameter_problem:         context = (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_parameter_problem_gen(parent, (internet_control_message_protocol_version6_parameter_problem_t *) packet, packetlen);              break;
            case internet_control_message_protocol_version6_message_type_echo_request:              context = (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_echo_gen(parent, (internet_control_message_protocol_version6_echo_t *) packet, packetlen);                                        break;
            case internet_control_message_protocol_version6_message_type_echo_reply:                context = (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_echo_gen(parent, (internet_control_message_protocol_version6_echo_t *) packet, packetlen);                                        break;
            case internet_control_message_protocol_version6_message_type_router_solicitation:       context = (internet_control_message_protocol_version6_context_t *) internet_control_message_protocol_version6_context_router_solicitation_gen(parent, (internet_control_message_protocol_version6_router_solicitation_t *) packet, packetlen);          break;
            default:                                                                                snorlaxdbg(true, false, "critical", "");                                                                                                                                                        break;
        }
    } else {
        context = (internet_control_message_protocol_version6_context_t *) calloc(1, sizeof(internet_control_message_protocol_version6_context_t));
    }

    context->func = address_of(func);

    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

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