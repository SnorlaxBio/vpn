#include <stdlib.h>

#include "../datagram.h"

static user_datagram_protocol_context_t * user_datagram_protocol_context_func_rem(user_datagram_protocol_context_t * context);

static user_datagram_protocol_context_func_t func = {
    user_datagram_protocol_context_func_rem
};

extern user_datagram_protocol_context_t * user_datagram_protocol_context_gen(internet_protocol_context_t * parent, user_datagram_protocol_packet_t * packet, uint64_t packetlen) {
    user_datagram_protocol_context_t * context = (user_datagram_protocol_context_t *) calloc(1, sizeof(user_datagram_protocol_context_t));

    context->func = address_of(func);

    return context;
}

static user_datagram_protocol_context_t * user_datagram_protocol_context_func_rem(user_datagram_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}
