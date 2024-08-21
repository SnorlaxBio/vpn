#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#include "../control.h"

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context);
static int32_t transmission_control_protocol_context_func_valid(transmission_control_protocol_context_t * context);
static uint8_t * transmission_control_protocol_context_func_addrptr(transmission_control_protocol_context_t * context, uint32_t type);
typedef void (*transmission_control_protocol_context_func_checksum_build_t)(transmission_control_protocol_context_t *, const uint8_t *, uint64_t);

static transmission_control_protocol_context_func_t func = {
    transmission_control_protocol_context_func_rem,
    transmission_control_protocol_context_func_valid,
    transmission_control_protocol_context_func_addrptr,
    (transmission_control_protocol_context_func_checksum_build_t) protocol_context_func_checksum_build
};

extern transmission_control_protocol_context_t * transmission_control_protocol_context_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_packet_t * packet, uint64_t packetlen, uint64_t bufferlen) {
    transmission_control_protocol_context_t * context = (transmission_control_protocol_context_t *) calloc(1, sizeof(transmission_control_protocol_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = nil;
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;
    context->bufferlen = bufferlen;

    return context;
}

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
//    snorlaxdbg(context->block != nil, false, "critical", "");   // 사용한 컨트롤 블록은 nil 로 설정하거나, 해쉬테이블에서 삭제해야 한다.
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
    snorlaxdbg(false, true, "debug", "");
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

extern uint32_t transmission_control_protocol_direction_cal(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "deprecated", "");

    // if(context->parent->direction == internet_protocol_direction_none) {
    //     return internet_protocol_direction_none;
    // }

    // if(context->parent->direction == internet_protocol_direction_internal) {
    //     snorlaxdbg(false, true, "debug", "");
    // }

    // return context->parent->direction;
}

extern int32_t transmission_control_protocol_context_is_connect_syn(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint8_t flags = transmission_control_protocol_context_flags_get(context);

    if(flags == transmission_control_flag_control_syn) {
        snorlaxdbg(false, true, "debug", "connect syn");
        return true;
    }

    return false;
}

extern int32_t transmssion_control_protocol_context_is_accept_syn(transmission_control_protocol_context_t * context) {
    snorlaxdbg(true, false, "implement", "");
}

static uint8_t * transmission_control_protocol_context_func_addrptr(transmission_control_protocol_context_t * context, uint32_t type) {
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