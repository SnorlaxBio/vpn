#include <stdlib.h>

#include "../control.h"

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context);
static int32_t transmission_control_protocol_context_func_valid(transmission_control_protocol_context_t * context);

static transmission_control_protocol_context_func_t func = {
    transmission_control_protocol_context_func_rem,
    transmission_control_protocol_context_func_valid
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen) {
    transmission_control_protocol_context_t * context = (transmission_control_protocol_context_t *) calloc(1, sizeof(transmission_control_protocol_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t transmission_control_protocol_context_func_valid(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return true;
}