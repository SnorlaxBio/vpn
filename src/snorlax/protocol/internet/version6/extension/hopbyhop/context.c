#include "../../../version6.h"

static internet_protocol_version6_extension_hopbyhop_context_t * internet_protocol_version6_extension_hopbyhop_context_func_rem(internet_protocol_version6_extension_hopbyhop_context_t * context);
static int32_t internet_protocol_version6_extension_hopbyhop_context_func_valid(internet_protocol_version6_extension_hopbyhop_context_t * context);

typedef uint8_t * (*internet_protocol_version6_extension_hopbyhop_context_func_addrptr_t)(internet_protocol_version6_extension_hopbyhop_context_t *, uint32_t);

static internet_protocol_version6_extension_hopbyhop_context_func_t func = {
    internet_protocol_version6_extension_hopbyhop_context_func_rem,
    internet_protocol_version6_extension_hopbyhop_context_func_valid,
    (internet_protocol_version6_extension_hopbyhop_context_func_addrptr_t) protocol_context_func_addrptr
};

extern internet_protocol_version6_extension_hopbyhop_context_t * internet_protocol_version6_extension_hopbyhop_context_gen(internet_protocol_version6_extension_hopbyhop_module_t * module, internet_protocol_version6_context_t * parent, protocol_packet_t * datagram, uint64_t datagramlen) {
#ifndef   RELEASE
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(datagram == nil, false, "critical", "");
    snorlaxdbg(datagramlen == 0, false, "criticial", "");
#endif // RELEASE

    internet_protocol_version6_extension_hopbyhop_context_t * context = (internet_protocol_version6_extension_hopbyhop_context_t *) calloc(1, sizeof(internet_protocol_version6_extension_hopbyhop_context_t));

    context->func = address_of(func);
    context->children = nil;
    context->parent = parent;
    context->packet = (internet_protocol_version6_extension_hopbyhop_t *) datagram;
    context->packetlen = datagramlen;

    return context;
}

static internet_protocol_version6_extension_hopbyhop_context_t * internet_protocol_version6_extension_hopbyhop_context_func_rem(internet_protocol_version6_extension_hopbyhop_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_protocol_version6_extension_hopbyhop_context_func_valid(internet_protocol_version6_extension_hopbyhop_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return true;
}