#include "../internet.h"

static internet_protocol_context_t * internet_protocol_context_func_rem(internet_protocol_context_t * context);

static internet_protocol_context_func_t func = {
    internet_protocol_context_func_rem
};

extern internet_protocol_context_t * internet_protocol_context_gen(protocol_context_t * parent, internet_protocol_packet_t * packet, uint64_t packetlen) {
    internet_protocol_context_t * context = (internet_protocol_context_t *) calloc(1, sizeof(internet_protocol_context_t));

    context->func = address_of(func);
    context->children = protocol_context_array_gen();

    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static internet_protocol_context_t * internet_protocol_context_func_rem(internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->pseudo = (internet_protocol_pseudo_t *) memory_rem(context->pseudo);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}
