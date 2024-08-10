#include <stdlib.h>
#include <errno.h>

#include "../../../version6.h"

static internet_protocol_version6_extension_routing_module_t * internet_protocol_version6_extension_routing_module_func_rem(internet_protocol_version6_extension_routing_module_t * module);
static int32_t internet_protocol_version6_extension_routing_module_func_deserialize(internet_protocol_version6_extension_routing_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t ** context);
static int32_t internet_protocol_version6_extension_routing_module_func_serialize(internet_protocol_version6_extension_routing_module_t * module, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen);
static void internet_protocol_version6_extension_routing_module_func_debug(internet_protocol_version6_extension_routing_module_t * module, FILE * stream, internet_protocol_version6_extension_routing_context_t * context);

static internet_protocol_version6_extension_routing_module_func_t func = {
    internet_protocol_version6_extension_routing_module_func_rem,
    internet_protocol_version6_extension_routing_module_func_deserialize,
    internet_protocol_version6_extension_routing_module_func_serialize,
    internet_protocol_version6_extension_routing_module_func_debug
};

extern internet_protocol_version6_extension_routing_module_t * internet_protocol_version6_extension_routing_module_gen(void) {
    internet_protocol_version6_extension_routing_module_t * module = (internet_protocol_version6_extension_routing_module_t *) calloc(1, sizeof(internet_protocol_version6_extension_routing_module_t));

    module->func = address_of(func);

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

static int32_t internet_protocol_version6_extension_routing_module_func_deserialize(internet_protocol_version6_extension_routing_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version6_extension_routing_context_gen(parent, packet, packetlen);

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

static int32_t internet_protocol_version6_extension_routing_module_func_serialize(internet_protocol_version6_extension_routing_module_t * module, internet_protocol_version6_context_t * parent, internet_protocol_version6_extension_routing_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen) {
    return fail;
}

static void internet_protocol_version6_extension_routing_module_func_debug(internet_protocol_version6_extension_routing_module_t * module, FILE * stream, internet_protocol_version6_extension_routing_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "criticial", "");
    snorlaxdbg(context->extension == nil, false, "criticial", "");
#endif // RELEASE

    fprintf(stream, "| routing ");
    fprintf(stream, "| %d ", context->extension->next);
    fprintf(stream, "| %d ", (context->extension->length + 1) * 8);
    fprintf(stream, "| %d ", context->extension->type);
    fprintf(stream, "| %d ", context->extension->left);
    fprintf(stream, "|\n");

    // TODO: TYPE SPECIFIC DATA 
}
