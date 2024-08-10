#include <stdlib.h>
#include <errno.h>

#include "../internet.h"
#include "version4.h"
#include "version6.h"

static internet_protocol_module_t * internet_protocol_module_func_rem(internet_protocol_module_t * module);
static int32_t internet_protocol_module_func_deserialize(internet_protocol_module_t * module, protocol_packet_t * packet, uint32_t packetlen, protocol_context_t * parent, internet_protocol_context_t ** context);
static int32_t internet_protocol_module_func_serialize(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen);
static void internet_protocol_module_func_debug(internet_protocol_module_t * module, FILE * stream, internet_protocol_context_t * context);

static internet_protocol_module_func_t func = {
    internet_protocol_module_func_rem,
    internet_protocol_module_func_deserialize,
    internet_protocol_module_func_serialize,
    internet_protocol_module_func_debug
};

extern internet_protocol_module_t * internet_protocol_module_gen(protocol_module_t * parent, protocol_module_t ** submodule, uint64_t submodulelen, protocol_module_map_index_t index) {
    internet_protocol_module_t * module = (internet_protocol_module_t *) calloc(1, sizeof(internet_protocol_module_t));

    module->func = address_of(func);
    module->parent = parent;

    if(submodule && submodulelen && index) {
        module->map = protocol_module_map_gen(submodule, submodulelen, index);
    }

    module->version4 = (protocol_module_t *) internet_protocol_version4_module_gen(parent, submodule, submodulelen, index);
    module->version6 = (protocol_module_t *) internet_protocol_version6_module_gen(parent, submodule, submodulelen, index);

    return module;
}

static internet_protocol_module_t * internet_protocol_module_func_rem(internet_protocol_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    if(module->map) module->map = protocol_module_map_rem(module->map);

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t internet_protocol_module_func_deserialize(internet_protocol_module_t * module, protocol_packet_t * packet, uint32_t packetlen, protocol_context_t * parent, internet_protocol_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(module->map == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE   

    uint8_t version = internet_protocol_version_get(packet);

    if(version == 4) {
        return internet_protocol_version4_module_deserialize(module->version4, packet, packetlen, parent, context);
    } else if(version == 6) {
        return internet_protocol_version6_module_deserialize(module->version6, packet, packetlen, parent, context);
    } else {
        if(*context == nil) *context = internet_protocol_context_gen(parent, (internet_protocol_packet_t *) packet, packetlen);

        internet_protocol_context_error_set(*context, EIO);
    }

    return fail;
}

static int32_t internet_protocol_module_func_serialize(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
#endif // RELEASE

    uint8_t version = internet_protocol_version_get(context->packet);

    if(version == 4) {
        return internet_protocol_version4_module_serialize(module->version4, parent, context, packet, packetlen);
    } else if(version == 6) {
        return internet_protocol_version6_module_serialize(module->version6, parent, context, packet, packetlen);
    } else {
#ifndef   RELEASE
        snorlaxdbg(true, false, "critical", "");
#endif // RELEASE
    }

    return fail;
}

static void internet_protocol_module_func_debug(internet_protocol_module_t * module, FILE * stream, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint8_t version = internet_protocol_version_get(context->packet);

    if(version == 4) {
        internet_protocol_version4_module_debug(module->version4, stream, context);
    } else if(version == 6) {
        internet_protocol_version6_module_debug(module->version6, stream, context);
    } else {
        snorlaxdbg(true, false, "critical", "");
    }
}
