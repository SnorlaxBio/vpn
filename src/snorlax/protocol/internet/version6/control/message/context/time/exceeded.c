#include "../../../message.h"

static internet_control_message_protocol_version6_context_time_exceeded_t * internet_control_message_protocol_version6_context_time_exceeded_func_rem(internet_control_message_protocol_version6_context_time_exceeded_t * context);
static int32_t internet_control_message_protocol_version6_context_time_exceeded_func_valid(internet_control_message_protocol_version6_context_time_exceeded_t * context);
typedef uint8_t * (*internet_control_message_protocol_version6_context_time_exceeded_func_addrptr_t)(internet_control_message_protocol_version6_context_time_exceeded_t *, uint32_t);
typedef void (*internet_control_message_protocol_version6_context_time_exceeded_func_checksum_build_t)(internet_control_message_protocol_version6_context_time_exceeded_t *, const uint8_t *, uint64_t);

static internet_control_message_protocol_version6_context_time_exceeded_func_t func = {
    internet_control_message_protocol_version6_context_time_exceeded_func_rem,
    internet_control_message_protocol_version6_context_time_exceeded_func_valid,
    (internet_control_message_protocol_version6_context_time_exceeded_func_addrptr_t) protocol_context_func_addrptr,
    (internet_control_message_protocol_version6_context_time_exceeded_func_checksum_build_t) protocol_context_func_checksum_build
};

extern internet_control_message_protocol_version6_context_time_exceeded_t * internet_control_message_protocol_version6_context_time_exceeded_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_time_exceeded_t * packet, uint64_t packetlen, uint64_t bufferlen) {
    internet_control_message_protocol_version6_context_time_exceeded_t * context = (internet_control_message_protocol_version6_context_time_exceeded_t *) calloc(1, sizeof(internet_control_message_protocol_version6_context_time_exceeded_t));

    context->func = address_of(func);
    context->module = module;
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;
    context->bufferlen = bufferlen;

    return context;
}

static internet_control_message_protocol_version6_context_time_exceeded_t * internet_control_message_protocol_version6_context_time_exceeded_func_rem(internet_control_message_protocol_version6_context_time_exceeded_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_control_message_protocol_version6_context_time_exceeded_func_valid(internet_control_message_protocol_version6_context_time_exceeded_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "critical", "");

    return true;
}