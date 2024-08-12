#include "../../../message.h"

static internet_control_message_protocol_version6_context_router_advertisement_t * internet_control_message_protocol_version6_context_router_advertisement_func_rem(internet_control_message_protocol_version6_context_router_advertisement_t * context);

static internet_control_message_protocol_version6_context_router_advertisement_func_t func = {
    internet_control_message_protocol_version6_context_router_advertisement_func_rem
};

extern internet_control_message_protocol_version6_context_router_advertisement_t * internet_control_message_protocol_version6_context_router_advertisement_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_router_advertisement_t * packet, uint64_t packetlen) {
    internet_control_message_protocol_version6_context_router_advertisement_t * context = (internet_control_message_protocol_version6_context_router_advertisement_t *) calloc(1, sizeof(internet_control_message_protocol_version6_context_router_advertisement_t));

    context->func = address_of(func);
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static internet_control_message_protocol_version6_context_router_advertisement_t * internet_control_message_protocol_version6_context_router_advertisement_func_rem(internet_control_message_protocol_version6_context_router_advertisement_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}