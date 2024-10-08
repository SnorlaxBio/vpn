#include "../message.h"

typedef uint8_t * (*internet_control_message_protocol_version4_context_func_addrptr_t)(internet_control_message_protocol_version4_context_t *, uint32_t);
typedef void (*internet_control_message_protocol_version4_context_func_checksum_build_t)(internet_control_message_protocol_version4_context_t *, const uint8_t *, uint64_t);

static internet_control_message_protocol_version4_context_func_t func = {
    internet_control_message_protocol_version4_context_func_rem,
    internet_control_message_protocol_version4_context_func_valid,
    (internet_control_message_protocol_version4_context_func_addrptr_t) protocol_context_func_addrptr,
    (internet_control_message_protocol_version4_context_func_checksum_build_t) protocol_context_func_checksum_build
};

extern internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_gen(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_packet_t * packet, uint64_t packetlen, uint64_t * bufferlen) {
    internet_control_message_protocol_version4_context_t * context = (internet_control_message_protocol_version4_context_t *) calloc(1, sizeof(internet_control_message_protocol_version4_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = nil;
    context->parent = parent;
    context->message = packet;
    context->messagelen = packetlen;
    context->bufferlen = bufferlen;

    return context;
}

extern internet_control_message_protocol_version4_context_t * internet_control_message_protocol_version4_context_func_rem(internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

extern int32_t internet_control_message_protocol_version4_context_func_valid(internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return true;
}