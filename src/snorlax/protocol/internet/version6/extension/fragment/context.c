#include <stdlib.h>

#include "../../../version6.h"

static internet_protocol_version6_extension_fragment_context_t * internet_protocol_version6_extension_fragment_context_func_rem(internet_protocol_version6_extension_fragment_context_t * context);

static internet_protocol_version6_extension_fragment_context_func_t func = {
    internet_protocol_version6_extension_fragment_context_func_rem
};

extern internet_protocol_version6_extension_fragment_context_t * internet_protocol_version6_extension_fragment_context_gen(internet_protocol_version6_context_t * parent, protocol_packet_t * datagram, uint64_t datagramlen) {
    internet_protocol_version6_extension_fragment_context_t * context = (internet_protocol_version6_extension_fragment_context_t *) calloc(1, sizeof(internet_protocol_version6_extension_fragment_context_t));

    context->func = address_of(func);
    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->extension = (internet_protocol_version6_extension_fragment_t *) datagram;
    context->extensionlen = datagramlen;

    return context;
}

static internet_protocol_version6_extension_fragment_context_t * internet_protocol_version6_extension_fragment_context_func_rem(internet_protocol_version6_extension_fragment_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}