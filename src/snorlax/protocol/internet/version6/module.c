#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "../version6.h"
#include "control/message.h"

static int32_t internet_protocol_version6_module_func_control_message_context_in_discard(internet_protocol_version6_module_t * module, internet_control_message_protocol_version6_context_t * context);

static internet_protocol_version6_module_func_t func = {
    internet_protocol_version6_module_func_rem,
    internet_protocol_version6_module_func_deserialize,
    internet_protocol_version6_module_func_serialize,
    internet_protocol_version6_module_func_debug,
    internet_protocol_version6_module_func_in,
    internet_protocol_version6_module_func_out,

    internet_protocol_version6_module_func_local_is,

    internet_protocol_version6_module_func_control_message_context_in
};

extern internet_protocol_version6_module_t * internet_protocol_version6_module_gen(protocol_module_map_t * map, internet_protocol_version6_context_handler_t on, uint8_t * addr) {
    internet_protocol_version6_module_t * module = (internet_protocol_version6_module_t *) calloc(1, sizeof(internet_protocol_version6_module_t));

    module->func = address_of(func);
    module->map = map;
    module->on = on;
    module->addr = addr;
    module->addrlen = 16;

    return module;
}

extern internet_protocol_version6_module_t * internet_protocol_version6_module_func_rem(internet_protocol_version6_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

extern int32_t internet_protocol_version6_module_func_deserialize(internet_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version6_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version6_context_gen(module, parent, (internet_protocol_version6_packet_t *) packet, packetlen);

    if(packetlen < internet_protocol_version6_packet_header_length_min) {
        internet_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version6_packet_t * datagram = (internet_protocol_version6_packet_t *) packet;
    uint64_t datagramlen = internet_protocol_version6_packet_header_length_min + internet_protocol_version6_context_payload_length_get(*context);

    if(packetlen < datagramlen) {
        internet_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version6_context_packetlen_set(*context, datagramlen);

    internet_protocol_version6_context_version_set(*context, internet_protocol_version6_version_get(datagram));
    internet_protocol_version6_context_traffic_class_set(*context, internet_protocol_version6_traffic_class_get(datagram));
    internet_protocol_version6_context_flow_label_set(*context, internet_protocol_version6_flow_label_get(datagram));

    // internet_protocol_version6_context_direction_set(*context, internet_protocol_version6_direction_cal(internet_protocol_version6_context_source_get(*context), internet_protocol_version6_context_destination_get(*context), module->addr));

    internet_protocol_version6_module_debug(module, stdout, *context);

    return success;
}

extern int32_t internet_protocol_version6_module_func_serialize(internet_protocol_version6_module_t * module, protocol_context_t * parent, internet_protocol_version6_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    // TODO: UPGRADE
    return fail;
}

extern void internet_protocol_version6_module_func_debug(internet_protocol_version6_module_t * module, FILE * stream, internet_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE
    char address[256];
    
    fprintf(stream, "| internet protocol version 6 ");
    fprintf(stream, "| %d ", internet_protocol_version6_context_version_get(context));
    fprintf(stream, "| %d ", internet_protocol_version6_context_traffic_class_get(context));
    fprintf(stream, "| %d ", internet_protocol_version6_context_flow_label_get(context));
    fprintf(stream, "| %d ", internet_protocol_version6_context_payload_length_get(context));
    fprintf(stream, "| %d ", internet_protocol_version6_context_next_header_get(context));
    fprintf(stream, "| %d ", internet_protocol_version6_context_hop_limit_get(context));
    fprintf(stream, "| %s ", internet_protocol_version6_address_to_string(address, internet_protocol_version6_context_source_get(context)));
    fprintf(stream, "| %s ", internet_protocol_version6_address_to_string(address, internet_protocol_version6_context_destination_get(context)));
    fprintf(stream, "|\n");
}

extern int32_t internet_protocol_version6_module_func_on(internet_protocol_version6_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context) {
    snorlaxdbg(false, true, "debug", "type => %u", type);

    if(type == protocol_event_exception) {
        snorlaxdbg(false, true, "debug", "exception => %d", internet_protocol_version6_context_error_get(context));
    }
    
    return success;
}

extern int32_t internet_protocol_version6_module_func_in(internet_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version6_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version6_context_gen(module, parent, (internet_protocol_version6_packet_t *) packet, packetlen);

    if(internet_protocol_version6_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        snorlaxdbg(false, true, "debug", "");
        internet_protocol_version6_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    internet_protocol_version6_module_on(module, protocol_event_in, parent, *context);

    uint8_t protocol = 0;
    protocol_module_t * submodule = protocol_module_map_get(module->map, protocol = internet_protocol_version6_context_next_protocol_get(*context));

    packet = internet_protocol_version6_context_next_packet_get(*context);
    packetlen = packetlen - internet_protocol_version6_packet_header_length_min;

    while(submodule) {
        protocol_context_t ** subcontext = protocol_context_array_pop((*context)->children);
        if(protocol_module_in(submodule, packet, packetlen, (protocol_context_t *) *context, subcontext) == fail) {
            snorlaxdbg(internet_protocol_version6_context_error_get(*subcontext) == 0, false, "critical", "");

            internet_protocol_version6_context_error_set(*context, ECHILD);

            internet_protocol_version6_module_on(module, protocol_event_exception, parent, *context);

            return fail;
        }

        if(internet_protocol_version6_extension_check(protocol)) {
            submodule = protocol_module_map_get(module->map, protocol = internet_protocol_version6_extension_context_next_protocol_get(*subcontext));
            packet = internet_protocol_version6_extension_context_next_packet_get(*subcontext);
            packetlen = packetlen - internet_protocol_version6_extension_context_length_get(*subcontext);
        } else {
            submodule = nil;
        }
    }

    internet_protocol_version6_module_on(module, protocol_event_complete_in, parent, *context);

    return success;
}

extern int32_t internet_protocol_version6_module_func_control_message_context_in(internet_protocol_version6_module_t * module, internet_control_message_protocol_version6_context_t * context) {
    switch(internet_control_message_protocol_version6_context_type_get(context)) {
        case internet_control_message_protocol_version6_type_router_solicitation:       return internet_protocol_version6_module_func_control_message_context_in_discard(module, context);
    }
    return success;
}

static int32_t internet_protocol_version6_module_func_control_message_context_in_discard(internet_protocol_version6_module_t * module, internet_control_message_protocol_version6_context_t * context) {
    // discard
    return success;
}

extern int32_t internet_protocol_version6_module_func_local_is(internet_protocol_version6_module_t * module, uint8_t * addr) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(addr == nil, false, "critical", "");
#endif // RELEASE

    if(module->addr) {
        return memcmp(module->addr, addr, 16) == 0;
    }

    return false;
}

extern int32_t internet_protocol_version6_module_func_out(internet_protocol_version6_module_t * module, internet_protocol_version6_context_t * context, protocol_path_node_t * node) {
    snorlaxdbg(true, false, "implement", "");
}