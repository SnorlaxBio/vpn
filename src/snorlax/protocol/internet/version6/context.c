#include "../version6.h"

static internet_protocol_version6_context_t * internet_protocol_version6_context_func_rem(internet_protocol_version6_context_t * context);
static int32_t internet_protocol_version6_context_func_valid(internet_protocol_version6_context_t * context);
static uint8_t * internet_protocol_version6_context_func_addrptr(internet_protocol_version6_context_t * context, uint32_t tyep);

typedef void (*internet_protocol_version6_context_func_checksum_build_t)(internet_protocol_version6_context_t *, const uint8_t *, uint64_t);

static internet_protocol_version6_context_func_t func = {
    internet_protocol_version6_context_func_rem,
    internet_protocol_version6_context_func_valid,
    internet_protocol_version6_context_func_addrptr,
    (internet_protocol_version6_context_func_checksum_build_t) protocol_context_func_checksum_build
};

extern internet_protocol_version6_context_t * internet_protocol_version6_context_gen(internet_protocol_version6_module_t * module, protocol_context_t * parent, internet_protocol_version6_packet_t * datagram, uint64_t datagramlen, uint64_t * bufferlen) {
    internet_protocol_version6_context_t * context = (internet_protocol_version6_context_t *) calloc(1, sizeof(internet_protocol_version6_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->packet = (internet_protocol_version6_packet_t *) datagram;
    context->packetlen = datagramlen;
    context->bufferlen = bufferlen;

    return context;
}

static internet_protocol_version6_context_t * internet_protocol_version6_context_func_rem(internet_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->pseudo = memory_rem(context->pseudo);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_protocol_version6_context_func_valid(internet_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return true;
}

static uint8_t * internet_protocol_version6_context_func_addrptr(internet_protocol_version6_context_t * context, uint32_t type) {
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
