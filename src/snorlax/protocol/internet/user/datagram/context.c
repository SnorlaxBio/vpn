#include <stdlib.h>

#include "../datagram.h"

static user_datagram_protocol_context_t * user_datagram_protocol_context_func_rem(user_datagram_protocol_context_t * context);
static int32_t user_datagram_protocol_context_func_valid(user_datagram_protocol_context_t * context);
static uint8_t * user_datagram_protocol_context_func_addrptr(user_datagram_protocol_context_t * context, uint32_t type);

static user_datagram_protocol_context_func_t func = {
    user_datagram_protocol_context_func_rem,
    user_datagram_protocol_context_func_valid,
    user_datagram_protocol_context_func_addrptr
};

extern user_datagram_protocol_context_t * user_datagram_protocol_context_gen(user_datagram_protocol_module_t * module, internet_protocol_context_t * parent, user_datagram_protocol_packet_t * packet, uint64_t packetlen) {
    user_datagram_protocol_context_t * context = (user_datagram_protocol_context_t *) calloc(1, sizeof(user_datagram_protocol_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = protocol_context_array_gen();

    return context;
}

static user_datagram_protocol_context_t * user_datagram_protocol_context_func_rem(user_datagram_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t user_datagram_protocol_context_func_valid(user_datagram_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return true;
}

static uint8_t * user_datagram_protocol_context_func_addrptr(user_datagram_protocol_context_t * context, uint32_t type) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(type == protocol_address_type_source) {
        return (uint8_t *) address_of(context->packet->source);
    } else if(type == protocol_address_type_destination) {
        return (uint8_t *) address_of(context->packet->destination);
    }

    return nil;
}
