#include <stdlib.h>
#include <errno.h>

#include "../../../version6.h"

static internet_protocol_version6_extension_routing_module_t * internet_protocol_version6_extension_routing_module_func_rem(internet_protocol_version6_extension_routing_module_t * module);
static int32_t internet_protocol_version6_extension_routing_module_func_deserialize(internet_protocol_version6_extension_routing_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t ** context);
static int32_t internet_protocol_version6_extension_routing_module_func_serialize(internet_protocol_version6_extension_routing_module_t * module, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void internet_protocol_version6_extension_routing_module_func_debug(internet_protocol_version6_extension_routing_module_t * module, FILE * stream, internet_protocol_version6_extension_routing_context_t * context);
static int32_t internet_protocol_version6_extension_routing_module_func_in(internet_protocol_version6_extension_routing_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t ** context);

typedef int32_t (*internet_protocol_version6_extension_routing_module_func_out_t)(internet_protocol_version6_extension_routing_module_t *, protocol_path_node_t *, protocol_context_t *);

static internet_protocol_version6_extension_routing_module_func_t func = {
    internet_protocol_version6_extension_routing_module_func_rem,
    internet_protocol_version6_extension_routing_module_func_deserialize,
    internet_protocol_version6_extension_routing_module_func_serialize,
    internet_protocol_version6_extension_routing_module_func_debug,
    internet_protocol_version6_extension_routing_module_func_in,
    (internet_protocol_version6_extension_routing_module_func_out_t) protocol_module_func_out
};

extern internet_protocol_version6_extension_routing_module_t * internet_protocol_version6_extension_routing_module_gen(internet_protocol_version6_extension_routing_context_handler_t on) {
    internet_protocol_version6_extension_routing_module_t * module = (internet_protocol_version6_extension_routing_module_t *) calloc(1, sizeof(internet_protocol_version6_extension_routing_module_t));

    module->func = address_of(func);
    module->on = on;

    return module;
}

static internet_protocol_version6_extension_routing_module_t * internet_protocol_version6_extension_routing_module_func_rem(internet_protocol_version6_extension_routing_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t internet_protocol_version6_extension_routing_module_func_deserialize(internet_protocol_version6_extension_routing_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version6_extension_routing_context_gen(module, parent, packet, packetlen, 0);

    if(packetlen < internet_protocol_version6_extension_length_min) {
        internet_protocol_version6_extension_routing_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version6_extension_routing_t * segment = (internet_protocol_version6_extension_routing_t *) packet;

    internet_protocol_version6_extension_routing_context_length_set(*context, (1 + segment->length) * 8);

    if(packetlen < internet_protocol_version6_extension_routing_context_length_get(*context)) {
        internet_protocol_version6_extension_routing_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version6_extension_routing_module_debug(module, stdout, *context);

    return success;
}

static int32_t internet_protocol_version6_extension_routing_module_func_serialize(internet_protocol_version6_extension_routing_module_t * module, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    return fail;
}

static void internet_protocol_version6_extension_routing_module_func_debug(internet_protocol_version6_extension_routing_module_t * module, FILE * stream, internet_protocol_version6_extension_routing_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "criticial", "");
    snorlaxdbg(context->packet == nil, false, "criticial", "");
#endif // RELEASE

    fprintf(stream, "| routing ");
    fprintf(stream, "| %d ", context->packet->next);
    fprintf(stream, "| %d ", (context->packet->length + 1) * 8);
    fprintf(stream, "| %d ", context->packet->type);
    fprintf(stream, "| %d ", context->packet->left);
    fprintf(stream, "|\n");

    // TODO: TYPE SPECIFIC DATA 
}

extern int32_t internet_protocol_version6_extension_routing_module_func_on(internet_protocol_version6_extension_routing_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t * context) {
    return success;
}

static int32_t internet_protocol_version6_extension_routing_module_func_in(internet_protocol_version6_extension_routing_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version6_extension_routing_context_gen(module, parent, packet, packetlen, 0);

    if(internet_protocol_version6_extension_routing_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        internet_protocol_version6_extension_routing_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    if(internet_protocol_version6_extension_routing_module_on(module, protocol_event_in, parent, *context) == fail) {
        internet_protocol_version6_extension_routing_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    internet_protocol_version6_extension_routing_module_on(module, protocol_event_complete_in, parent, *context);

    return success;
}
