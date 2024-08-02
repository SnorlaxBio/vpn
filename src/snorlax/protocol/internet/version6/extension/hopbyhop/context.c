#include "../../../version6.h"

static internet_protocol_version6_extension_hopbyhop_context_t * internet_protocol_version6_extension_hopbyhop_context_func_rem(internet_protocol_version6_extension_hopbyhop_context_t * context);

static internet_protocol_version6_extension_hopbyhop_context_func_t func = {
    internet_protocol_version6_extension_hopbyhop_context_func_rem
};

// struct internet_protocol_version6_extension_hopbyhop_context {
//     internet_protocol_version6_extension_hopbyhop_context_func_t * func;
//     sync_t * sync;
//     internet_protocol_version6_context_t * parent;
//     protocol_context_t * subcontext;
//     int32_t error;
//     uint8_t * packet;
//     uint64_t packetlen;
// };

// struct internet_protocol_version6_extension_hopbyhop_context_func {
//     internet_protocol_version6_extension_hopbyhop_context_t * (*rem)(internet_protocol_version6_extension_hopbyhop_context_t *);
// };

extern internet_protocol_version6_extension_hopbyhop_context_t * internet_protocol_version6_extension_hopbyhop_context_gen(internet_protocol_version6_context_t * parent, protocol_packet_t * datagram, uint64_t datagramlen) {
#ifndef   RELEASE
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(datagram == nil, false, "critical", "");
    snorlaxdbg(datagramlen == 0, false, "criticial", "");
#endif // RELEASE

    internet_protocol_version6_extension_hopbyhop_context_t * context = (internet_protocol_version6_extension_hopbyhop_context_t *) calloc(1, sizeof(internet_protocol_version6_extension_hopbyhop_context_t));

    context->func = address_of(func);

    context->parent = parent;
    context->extension = (internet_protocol_version6_extension_hopbyhop_t *) datagram;
    context->extensionlen = datagramlen;

    return context;
}

static internet_protocol_version6_extension_hopbyhop_context_t * internet_protocol_version6_extension_hopbyhop_context_func_rem(internet_protocol_version6_extension_hopbyhop_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}