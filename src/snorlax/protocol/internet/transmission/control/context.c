#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#include "../control.h"

static transmission_control_protocol_context_t * transmission_control_protocol_context_func_rem(transmission_control_protocol_context_t * context);
static int32_t transmission_control_protocol_context_func_valid(transmission_control_protocol_context_t * context);
static uint8_t * transmission_control_protocol_context_func_addrptr(transmission_control_protocol_context_t * context, uint32_t type);

static void transmission_control_protocol_context_func_checksum_build(transmission_control_protocol_context_t * context, const uint8_t * pseudo, uint64_t pseudolen);

typedef void (*transmission_control_protocol_context_func_checksum_build_t)(transmission_control_protocol_context_t *, const uint8_t *, uint64_t);

static transmission_control_protocol_context_func_t func = {
    transmission_control_protocol_context_func_rem,
    transmission_control_protocol_context_func_valid,
    transmission_control_protocol_context_func_addrptr,
    transmission_control_protocol_context_func_checksum_build
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

    if(context->packetlen == 0) {
        context->data = (uint8_t *) packet;
    }

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

    if(transmission_control_protocol_context_error_get(context)) return false;

    snorlaxdbg(false, true, "debug", "checksumcal => %u", transmission_control_protocol_context_checksumcal_get(context));
    snorlaxdbg(false, true, "debug", "checksum => %u", transmission_control_protocol_context_checksum_get(context));

    if(transmission_control_protocol_context_checksumcal_get(context) != transmission_control_protocol_context_checksum_get(context)) {
        transmission_control_protocol_context_error_set(context, EIO);
        snorlaxdbg(transmission_control_protocol_context_checksumcal_get(context) != transmission_control_protocol_context_checksum_get(context), false, "critical", "");
        return false;
    }

    return true;
}

extern int32_t transmission_control_protocol_context_key_gen(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->parent) {
        uint8_t version = internet_protocol_context_version_get(context->parent);

        if(version == 4) {
            context->key.length = (sizeof(uint32_t) + sizeof(uint16_t)) * 2;
            context->key.value = memory_gen(context->key.value, context->key.length);

            memcpy(context->key.value                                                       , transmission_control_protocol_context_addrptr(context, protocol_address_type_source), sizeof(uint16_t));
            memcpy(address_of(context->key.value[sizeof(uint16_t)])                         , internet_protocol_context_addrptr(context, protocol_address_type_source), sizeof(uint32_t));
            memcpy(address_of(context->key.value[sizeof(uint16_t) + sizeof(uint32_t)])      , transmission_control_protocol_context_addrptr(context, protocol_address_type_destination), sizeof(uint16_t));
            memcpy(address_of(context->key.value[(sizeof(uint16_t) * 2) + sizeof(uint32_t)]), internet_protocol_context_addrptr(context, protocol_address_type_destination), sizeof(uint32_t));

            return success;
        } else if(version == 6) {
            context->key.length = ((sizeof(uint32_t) * 4) + sizeof(uint16_t)) * 2;
            context->key.value = memory_gen(context->key.value, context->key.length);

            memcpy(context->key.value, transmission_control_protocol_context_addrptr(context, protocol_address_type_source), sizeof(uint16_t));
            memcpy(address_of(context->key.value[sizeof(uint16_t)]), internet_protocol_context_addrptr(context, protocol_address_type_source), sizeof(uint32_t) * 4);
            memcpy(address_of(context->key.value[sizeof(uint16_t) + (sizeof(uint32_t) * 4)]), transmission_control_protocol_context_addrptr(context, protocol_address_type_destination), sizeof(uint16_t));
            memcpy(address_of(context->key.value[(sizeof(uint16_t) * 2) + (sizeof(uint32_t) * 4)]), internet_protocol_context_addrptr(context, protocol_address_type_destination), sizeof(uint32_t) * 4);

            return success;
        } else {
            snorlaxdbg(version != 4 && version != 6, false, "critical", "");
        }
    } else if(context->block && context->block->path) {
        protocol_path_node_t * node = protocol_path_begin(context->block->path);

        snorlaxdbg(node == nil, false, "critical", "");

        protocol_path_node_t * next = protocol_path_node_next(node);

        snorlaxdbg(next == nil, false, "critical", "");

        context->key.length = (node->length + next->length) * 2;
        context->key.value = memory_gen(context->key.value, context->key.length);

        memcpy(context->key.value, protocol_path_node_source_get(node), node->length);
        memcpy(address_of(context->key.value[node->length]), protocol_path_node_source_get(next), next->length);
        memcpy(address_of(context->key.value[node->length + next->length]), protocol_path_node_destination_get(node), node->length);
        memcpy(address_of(context->key.value[node->length * 2 + next->length]), protocol_path_node_destination_get(next), next->length);

        return success;
    } else {
        snorlaxdbg(true, false, "critical", "");
    }

    snorlaxdbg(true, false, "implement", "");

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
        if(context->block == nil || transmission_control_block_state_get(context->block) == transmission_control_state_synchronize_sequence_recv) {
            return true;
        }
    }

    snorlaxdbg(false, true, "debug", "");

    return false;
}

extern int32_t transmssion_control_protocol_context_is_connect_ack(transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(context->block == nil, false, "critical", "");       // TODO: PACKET DROP ...
#endif // RELEASE

    uint8_t flags = transmission_control_protocol_context_flags_get(context);

    if(flags == transmission_control_flag_control_ack) {
        snorlaxdbg(false, true, "implement", "old applied packet drop");
        if(transmission_control_block_state_get(context->block) == transmission_control_state_synchronize_sequence_recv) {
            return true;
        }
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

static void transmission_control_protocol_context_func_checksum_build(transmission_control_protocol_context_t * context, const uint8_t * pseudo, uint64_t pseudolen) {
    snorlaxdbg(false, true, "debug", "context->packetlen => %lu\n", context->packetlen);
    context->checksumcal = transmission_control_protocol_checksum_cal(context->packet, context->packetlen, (internet_protocol_pseudo_t *) pseudo, pseudolen);

    transmission_control_protocol_context_checksum_set(context, context->checksumcal);
}