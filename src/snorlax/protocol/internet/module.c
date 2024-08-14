#include <stdlib.h>
#include <errno.h>

#include "../internet.h"
#include "version4.h"
#include "version6.h"

static internet_protocol_module_t * internet_protocol_module_func_rem(internet_protocol_module_t * module);
static int32_t internet_protocol_module_func_deserialize(internet_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_context_t ** context);
static int32_t internet_protocol_module_func_serialize(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void internet_protocol_module_func_debug(internet_protocol_module_t * module, FILE * stream, internet_protocol_context_t * context);
static int32_t internet_protocol_module_func_in(internet_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_context_t ** context);

static internet_protocol_module_func_t func = {
    internet_protocol_module_func_rem,
    internet_protocol_module_func_deserialize,
    internet_protocol_module_func_serialize,
    internet_protocol_module_func_debug,
    internet_protocol_module_func_in
};

extern internet_protocol_module_t * internet_protocol_module_gen(protocol_module_map_t * map, internet_protocol_context_handler_t on, internet_protocol_version4_module_t * version4, internet_protocol_version6_module_t * version6) {
    internet_protocol_module_t * module = (internet_protocol_module_t *) calloc(1, sizeof(internet_protocol_module_t));

    module->func = address_of(func);
    module->map = map;
    module->on = on;

    module->version4 = version4;
    module->version6 = version6;

    return module;
}

static internet_protocol_module_t * internet_protocol_module_func_rem(internet_protocol_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);
    module->version4 = internet_protocol_version4_module_rem(module->version4);
    module->version6 = internet_protocol_version6_module_rem(module->version6);

    free(module);

    return nil;
}

static int32_t internet_protocol_module_func_deserialize(internet_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
#endif // RELEASE   

    uint8_t version = internet_protocol_version_get(packet);

    if(version == 4) {
        return internet_protocol_version4_module_deserialize(module->version4, packet, packetlen, parent, (internet_protocol_version4_context_t **) context);
    } else if(version == 6) {
        return internet_protocol_version6_module_deserialize(module->version6, packet, packetlen, parent, (internet_protocol_version6_context_t **) context);
    } else {
        if(*context == nil) *context = internet_protocol_context_gen(parent, (internet_protocol_packet_t *) packet, packetlen);

        internet_protocol_context_error_set(*context, EIO);

        return fail;
    }
}

static int32_t internet_protocol_module_func_serialize(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
#endif // RELEASE

    uint8_t version = internet_protocol_version_get(context->packet);

    if(version == 4) {
        return internet_protocol_version4_module_serialize(module->version4, parent, (internet_protocol_version4_context_t *) context, packet, packetlen);
    } else if(version == 6) {
        return internet_protocol_version6_module_serialize(module->version6, parent, (internet_protocol_version6_context_t *) context, packet, packetlen);
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
        internet_protocol_version4_module_debug(module->version4, stream, (internet_protocol_version4_context_t *) context);
    } else if(version == 6) {
        internet_protocol_version6_module_debug(module->version6, stream, (internet_protocol_version6_context_t *) context);
    } else {
        snorlaxdbg(true, false, "critical", "");
    }
}

static int32_t internet_protocol_module_func_in(internet_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
#endif // RELEASE

    if(packetlen == 0) {
        if(*context == nil) *context = internet_protocol_context_gen(parent, nil, packetlen);

        internet_protocol_context_error_set(*context, EAGAIN);

        return fail;
    }

    uint8_t version = internet_protocol_version_get(packet);

    if(version == 4) {
        if(internet_protocol_version4_module_in(module->version4, packet, packetlen, parent, (internet_protocol_version4_context_t **) context) == success) {
            internet_protocol_version4_module_on(module->version4, protocol_event_in, parent, (internet_protocol_version4_context_t *) *context);
            internet_protocol_module_on(module, protocol_event_in, parent, *context);
        }
        
        if(internet_protocol_context_error_get(*context) != EAGAIN) {
            internet_protocol_version4_module_on(module->version4, protocol_event_exception, parent, (internet_protocol_version4_context_t *) *context);
            internet_protocol_module_on(module, protocol_event_exception, parent, *context);

            return fail;
        }

        return success;
    } else if(version == 6) {
        if(internet_protocol_version6_module_in(module->version6, packet, packetlen, parent, (internet_protocol_version6_context_t **) context) == success) {
            internet_protocol_version6_module_on(module->version6, protocol_event_in, parent, (internet_protocol_version6_context_t *) *context);
            internet_protocol_module_on(module, protocol_event_in, parent, *context);
        }
        
        if(internet_protocol_context_error_get(*context) != EAGAIN) {
            internet_protocol_version6_module_on(module->version6, protocol_event_exception, parent, (internet_protocol_version6_context_t *) *context);
            internet_protocol_module_on(module, protocol_event_exception, parent, *context);

            return fail;
        }

        return success;
    } else {
        if(*context == nil) *context = internet_protocol_context_gen(parent, nil, packetlen);

        internet_protocol_context_error_set(*context, EIO);

        internet_protocol_module_on(module, protocol_event_exception, parent, *context);

        return fail;
    }
}

extern int32_t internet_protocol_module_func_on(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
    return success;
}
