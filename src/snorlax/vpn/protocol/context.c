#include "../protocol.h"

static virtual_private_network_protocol_context_t * virtual_private_network_protocol_context_func_rem(virtual_private_network_protocol_context_t * context);
static int32_t virtual_private_network_protocol_context_func_valid(virtual_private_network_protocol_context_t * context);

static virtual_private_network_protocol_context_func_t func = {
    virtual_private_network_protocol_context_func_rem,
    virtual_private_network_protocol_context_func_valid
};

extern virtual_private_network_protocol_context_t * virtual_private_network_protocol_context_gen(protocol_context_t * parent, virtual_private_network_protocol_packet_t * packet, uint64_t packetlen) {
    virtual_private_network_protocol_context_t * context = (virtual_private_network_protocol_context_t *) calloc(1, sizeof(virtual_private_network_protocol_context_t));

    context->func = address_of(func);
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static virtual_private_network_protocol_context_t * virtual_private_network_protocol_context_func_rem(virtual_private_network_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t virtual_private_network_protocol_context_func_valid(virtual_private_network_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    return context->packet->length == context->packetlen;
}