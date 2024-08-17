#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "../control.h"

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context);
static int32_t transmission_control_protocol_context_func_valid(transmission_control_protocol_context_t * context);

static transmission_control_protocol_context_func_t func = {
    transmission_control_protocol_context_func_rem,
    transmission_control_protocol_context_func_valid
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen) {
    transmission_control_protocol_context_t * context = (transmission_control_protocol_context_t *) calloc(1, sizeof(transmission_control_protocol_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->key.value) context->key.value = memory_rem(context->key.value);

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t transmission_control_protocol_context_func_valid(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return true;
}

extern int32_t transmission_control_protocol_context_key_gen(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE
    transmission_control_protocol_address_pair_t pair;
    if(transmission_control_protocol_address_pair_init(&pair, context->parent, context) == fail) {
        snorlaxdbg(false, true, "warning", "");
        /**
         * 라우터의 경우 키가 정상적으로 설정되지 않을 수 있다.
         */
        return fail;
    }

    uint8_t version = internet_protocol_context_version_get(context->parent);

    if(version == 4) context->key.length = (sizeof(uint32_t) + sizeof(uint16_t)) * 2;
    if(version == 6) context->key.length = ((sizeof(uint32_t) * 4) + sizeof(uint16_t)) * 2;

    context->key.value = memory_gen(context->key.value, context->key.length);
    memcpy(context->key.value, &pair, context->key.length);

    return fail;
}
