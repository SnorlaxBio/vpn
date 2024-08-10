#include "../message.h"

static internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_func_rem(internet_control_message_protocol_version4_context_t * context);

static internet_control_message_protocol_version4_context_func_t func = {
    internet_control_message_protocol_version4_context_func_rem
};

extern internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_gen(internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_packet_t * packet, uint64_t packetlen) {
    internet_control_message_protocol_version4_context_t * context = (internet_control_message_protocol_version4_context_t *) calloc(1, sizeof(internet_control_message_protocol_version4_context_t));

    context->func = address_of(func);
    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->message.packet = packet;
    context->packetlen = packetlen;

    return context;
}

static internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_func_rem(internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}
