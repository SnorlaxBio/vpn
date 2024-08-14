#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../version6.h"

static internet_protocol_version6_module_func_t func = {
    internet_protocol_version6_module_func_rem,
    internet_protocol_version6_module_func_deserialize,
    internet_protocol_version6_module_func_serialize,
    internet_protocol_version6_module_func_debug,
    internet_protocol_version6_module_func_in
};

extern internet_protocol_version6_module_t * internet_protocol_version6_module_gen(protocol_module_map_t * map, internet_protocol_version6_context_handler_t on) {
    internet_protocol_version6_module_t * module = (internet_protocol_version6_module_t *) calloc(1, sizeof(internet_protocol_version6_module_t));

    module->func = address_of(func);
    module->map = map;
    module->on = on;

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

    if(*context == nil) *context = internet_protocol_version6_context_gen(parent, (internet_protocol_version6_packet_t *) packet, packetlen);

    if(packetlen < internet_protocol_version6_packet_header_length_min) {
        internet_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version6_packet_t * datagram = (internet_protocol_version6_packet_t *) packet;

    internet_protocol_version6_context_payload_length_set(*context, ntohs(datagram->payload));

    if(packetlen < internet_protocol_version6_packet_header_length_min + internet_protocol_version6_context_payload_length_get(*context)) {
        internet_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version6_context_packetlen_set(*context, internet_protocol_version6_packet_header_length_min + internet_protocol_version6_context_payload_length_get(*context));

    internet_protocol_version6_context_version_set(*context, internet_protocol_version6_version_get(datagram));
    internet_protocol_version6_context_traffic_class_set(*context, internet_protocol_version6_traffic_class_get(datagram));
    internet_protocol_version6_context_flow_label_set(*context, internet_protocol_version6_flow_label_get(datagram));

    internet_protocol_version6_module_debug(module, stdout, *context);

    // TODO: UPGRADE PACKET PARSING ... 

    if(packetlen != internet_protocol_version6_packet_header_length_min) {
        uint8_t protocolno = 0;
        int32_t index = 0;
        protocol_module_t * submodule = protocol_module_map_get(module->map, protocolno = internet_protocol_version6_context_next_protocolno_get(*context));
        protocol_packet_t * subpacket = internet_protocol_version6_context_next_packet_get(*context);
        uint64_t subpacketlen = internet_protocol_version6_context_next_packetlen_get(*context);
        packetlen = packetlen - internet_protocol_version6_packet_header_length_min;

        while(submodule) {
            protocol_context_t ** subcontext = protocol_context_array_pop((*context)->children);
            protocol_module_deserialize(submodule, subpacket, subpacketlen, (protocol_context_t *) *context, subcontext);

            if(internet_protocol_version6_extension_check(protocolno)) {
                submodule = protocol_module_map_get(module->map, protocolno = internet_protocol_version6_extension_context_next_protocolno_get(*subcontext));
                subpacket = internet_protocol_version6_extension_context_next_packet_get(*context);
                subpacketlen = internet_protocol_version6_extension_context_next_packetlen_get(*context);
            } else {
                submodule = nil;
            }
        }
    }

    

    // TODO: UPDATE

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
    fprintf(stream, "| %s ", internet_protocol_version6_addr_to_str(address, internet_protocol_version6_context_source_get(context)));
    fprintf(stream, "| %s ", internet_protocol_version6_addr_to_str(address, internet_protocol_version6_context_destination_get(context)));
    fprintf(stream, "|\n");
}

extern int32_t internet_protocol_version6_module_func_on(internet_protocol_version6_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context){
    return success;
}

extern int32_t internet_protocol_version6_module_func_in(internet_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version6_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version6_context_gen(parent, (internet_protocol_version6_packet_t *) packet, packetlen);

    if(internet_protocol_version6_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        internet_protocol_version6_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    return internet_protocol_version6_module_on(module, protocol_event_in, parent, *context);
}
