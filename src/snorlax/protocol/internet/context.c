#include <arpa/inet.h>

#include "../internet.h"

#include "../internet/version4.h"
#include "../internet/version6.h"

static internet_protocol_context_t * internet_protocol_context_func_rem(internet_protocol_context_t * context);
static int32_t internet_protocol_context_func_valid(internet_protocol_context_t * context);

typedef uint8_t * (*internet_protocol_context_func_addrptr_t)(internet_protocol_context_t *, uint32_t);
typedef void (*internet_protocol_context_func_checksum_build_t)(internet_protocol_context_t *, const uint8_t *, uint64_t);

static internet_protocol_context_func_t func = {
    internet_protocol_context_func_rem,
    internet_protocol_context_func_valid,
    (internet_protocol_context_func_addrptr_t) protocol_context_func_addrptr,
    (internet_protocol_context_func_checksum_build_t) protocol_context_func_checksum_build
};

extern internet_protocol_context_t * internet_protocol_context_gen(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_packet_t * packet, uint64_t packetlen) {
    internet_protocol_context_t * context = (internet_protocol_context_t *) calloc(1, sizeof(internet_protocol_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = protocol_context_array_gen();

    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static internet_protocol_context_t * internet_protocol_context_func_rem(internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);

    context->pseudo = (internet_protocol_pseudo_t *) memory_rem(context->pseudo);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_protocol_context_func_valid(internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    return false;
}

extern uint8_t * internet_protocol_context_source_get(internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint8_t version = internet_protocol_context_version_get(context);

    if(version == 4) {
        return internet_protocol_version4_context_source_ptr_get((internet_protocol_version4_context_t *) context);
    } else if(version == 6) {
        return internet_protocol_version6_context_source_get((internet_protocol_version6_context_t *) context);
    } else {
        snorlaxdbg(true, false, "crtical", "");
    }

    return nil;
}

extern uint8_t * internet_protocol_context_destination_get(internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint8_t version = internet_protocol_context_version_get(context);

    if(version == 4) {
        return internet_protocol_version4_context_destination_ptr_get((internet_protocol_version4_context_t *) context);
    } else if(version == 6) {
        return internet_protocol_version6_context_destination_get((internet_protocol_version6_context_t *) context);
    } else {
        snorlaxdbg(true, false, "crtical", "");
    }

    return nil;
}