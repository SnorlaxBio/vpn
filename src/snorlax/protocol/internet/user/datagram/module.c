#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

#include "../datagram.h"

static user_datagram_protocol_module_t * user_datagram_protocol_module_func_rem(user_datagram_protocol_module_t * module);
static int32_t user_datagram_protocol_module_func_deserialize(user_datagram_protocol_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_context_t * parent, user_datagram_protocol_context_t ** context);
static int32_t user_datagram_protocol_module_func_serialize(user_datagram_protocol_module_t * module, internet_protocol_context_t * parent, user_datagram_protocol_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen);
static void user_datagram_protocol_module_func_debug(user_datagram_protocol_module_t * module, FILE * stream, user_datagram_protocol_context_t * context);

static user_datagram_protocol_module_func_t func = {
    user_datagram_protocol_module_func_rem,
    user_datagram_protocol_module_func_deserialize,
    user_datagram_protocol_module_func_serialize,
    user_datagram_protocol_module_func_debug
};

extern user_datagram_protocol_module_t * user_datagram_protocol_module_gen(protocol_module_map_t * map) {
    user_datagram_protocol_module_t * module = (user_datagram_protocol_module_t *) calloc(1, sizeof(user_datagram_protocol_module_t));

    module->func = address_of(func);
    module->map = map;

    return module;
}

static user_datagram_protocol_module_t * user_datagram_protocol_module_func_rem(user_datagram_protocol_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t user_datagram_protocol_module_func_deserialize(user_datagram_protocol_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_context_t * parent, user_datagram_protocol_context_t ** context) {
// user_datagram_protocol_module_t * module,
// protocol_packet_t * packet,
// uint32_t packetlen,
// protocol_context_t * parent,
// user_datagram_protocol_context_t ** context
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    user_datagram_protocol_packet_t * datagram = (user_datagram_protocol_packet_t *) packet;

    if(*context == nil) *context = user_datagram_protocol_context_gen(parent, datagram, packetlen);

    if(packetlen < user_datagram_protocol_packet_length_min) {
        user_datagram_protocol_context_error_set(*context, EAGAIN);
        return fail;
    }

    user_datagram_protocol_context_length_set(*context, ntohs(datagram->length));

    if(packetlen != user_datagram_protocol_context_length_get(*context)) {
        user_datagram_protocol_context_error_set(*context, EAGAIN);
        return fail;
    }

    user_datagram_protocol_context_source_set(*context, ntohs(datagram->source));
    user_datagram_protocol_context_destination_set(*context, ntohs(datagram->destination));
    user_datagram_protocol_context_checksum_set(*context, ntohs(datagram->checksum));

    uint16_t checksum = user_datagram_protocol_checksum_cal(datagram, internet_protocol_context_pseudo_get(parent), internet_protocol_context_pseudolen_get(parent));

    if(checksum != user_datagram_protocol_context_checksum_get(*context)) {
        user_datagram_protocol_context_error_set(*context, EIO);
        return fail;
    }

    user_datagram_protocol_module_debug(module, stdout, *context);

    // TODO: UPGRADE SUB PROTOCOL GET ...

    // protocol_module_t * submodule = protocol_module_map_get(module->map, internet_protocol_version4_context_protocol_get(*context));

    return success;
}

static int32_t user_datagram_protocol_module_func_serialize(user_datagram_protocol_module_t * module, internet_protocol_context_t * parent, user_datagram_protocol_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen) {
    snorlaxdbg(true, false, "implement", "");
    return fail;
}

static void user_datagram_protocol_module_func_debug(user_datagram_protocol_module_t * module, FILE * stream, user_datagram_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| user datagram protocol ");
    fprintf(stream, "| %d ", user_datagram_protocol_context_source_get(context));
    fprintf(stream, "| %d ", user_datagram_protocol_context_destination_get(context));
    fprintf(stream, "| %d ", user_datagram_protocol_context_length_get(context));
    fprintf(stream, "| %d ", user_datagram_protocol_context_checksum_get(context));
    fprintf(stream, "|\n");
}
