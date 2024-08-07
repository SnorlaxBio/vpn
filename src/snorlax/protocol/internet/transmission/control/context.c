#include <stdlib.h>

#include "../control.h"

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context);

static transmission_control_protocol_context_func_t func = {
    transmission_control_protocol_context_func_rem
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen) {
    transmission_control_protocol_context_t * context = (transmission_control_protocol_context_t *) calloc(1, sizeof(transmission_control_protocol_context_t));

    context->func = address_of(func);
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}