#include <stdlib.h>
#include <errno.h>

#include "../protocol.h"

static virtual_private_network_protocol_module_t * virtual_private_network_protocol_module_func_rem(virtual_private_network_protocol_module_t * module);
static int32_t virtual_private_network_protocol_module_func_deserialize(virtual_private_network_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, virtual_private_network_protocol_context_t ** context);
static int32_t virtual_private_network_protocol_module_func_serialize(virtual_private_network_protocol_module_t * module, protocol_context_t * parent, virtual_private_network_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void virtual_private_network_protocol_module_func_debug(virtual_private_network_protocol_module_t * module, FILE * stream, virtual_private_network_protocol_context_t * context);
static int32_t virtual_private_network_protocol_module_func_in(virtual_private_network_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, virtual_private_network_protocol_context_t ** context);

static virtual_private_network_protocol_module_func_t func = {
    virtual_private_network_protocol_module_func_rem,
    virtual_private_network_protocol_module_func_deserialize,
    virtual_private_network_protocol_module_func_serialize,
    virtual_private_network_protocol_module_func_debug,
    virtual_private_network_protocol_module_func_in
};

extern virtual_private_network_protocol_module_t * virtual_private_network_protocol_module_gen(protocol_module_map_t * map, virtual_private_network_protocol_context_handler_t on) {
    virtual_private_network_protocol_module_t * module = (virtual_private_network_protocol_module_t *) calloc(1, sizeof(virtual_private_network_protocol_module_t));

    module->func = address_of(func);
    module->map = map;
    module->on = on;

    return module;
}

static virtual_private_network_protocol_module_t * virtual_private_network_protocol_module_func_rem(virtual_private_network_protocol_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t virtual_private_network_protocol_module_func_deserialize(virtual_private_network_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, virtual_private_network_protocol_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    virtual_private_network_protocol_packet_t * datagram = (virtual_private_network_protocol_packet_t *) packet;

    if(*context) *context = virtual_private_network_protocol_context_gen(parent, datagram, packetlen);

    if(packetlen < sizeof(virtual_private_network_protocol_packet_t)) {
        virtual_private_network_protocol_context_error_set(*context, EAGAIN);
        return fail;
    }

    if(packetlen < datagram->length) {
        virtual_private_network_protocol_context_error_set(*context, EAGAIN);
        return fail;
    }

    virtual_private_network_protocol_context_length_set(*context, datagram->length);

    return success;
}

static int32_t virtual_private_network_protocol_module_func_serialize(virtual_private_network_protocol_module_t * module, protocol_context_t * parent, virtual_private_network_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    snorlaxdbg(true, false, "implement", "");
    return fail;
}

static void virtual_private_network_protocol_module_func_debug(virtual_private_network_protocol_module_t * module, FILE * stream, virtual_private_network_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| virtual private network protocol ");
    fprintf(stream, "| %d ", context->packet->type);
    fprintf(stream, "| %d ", context->packet->length);
    fprintf(stream, "|\n");
}

static int32_t virtual_private_network_protocol_module_func_in(virtual_private_network_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, virtual_private_network_protocol_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context) *context = virtual_private_network_protocol_context_gen(parent, (virtual_private_network_protocol_packet_t *) packet, packetlen);

    if(virtual_private_network_protocol_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        virtual_private_network_protocol_module_on(module, protocol_event_exception, parent, *context);

        return fail;
    }

    if(virtual_private_network_protocol_context_valid(*context)) {
        virtual_private_network_protocol_context_error_set(*context, EIO);
        virtual_private_network_protocol_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    return virtual_private_network_protocol_module_on(module, protocol_event_in, parent, *context);
}
