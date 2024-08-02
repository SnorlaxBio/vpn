#include <stdlib.h>

#include "../version4.h"

static internet_protocol_version4_context_t * internet_protocol_version4_context_func_rem(internet_protocol_version4_context_t * context);

static internet_protocol_version4_context_func_t func = {
    internet_protocol_version4_context_func_rem
};

extern internet_protocol_version4_context_t * internet_protocol_version4_context_gen(protocol_context_t * parent, internet_protocol_version4_packet_t * datagram, uint64_t datagramlen) {
    internet_protocol_version4_context_t * context = (internet_protocol_version4_context_t *) calloc(1, sizeof(internet_protocol_version4_context_t));

    context->func = address_of(func);
    context->parent = parent;
    context->datagram = datagram;
    context->datagramlen = datagramlen;

    return context;
}

static internet_protocol_version4_context_t * internet_protocol_version4_context_func_rem(internet_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->subcontext) context->subcontext = protocol_context_rem(context->subcontext);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}
