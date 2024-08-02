#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../version6.h"

// struct internet_protocol_version6_module {
//     internet_protocol_version6_module_func_t * func;
//     sync_t * sync;
//     protocol_module_t * parent;
//     protocol_module_map_t * children;
// };

static internet_protocol_version6_module_t * internet_protocol_version6_module_func_rem(internet_protocol_version6_module_t * module);
static int32_t internet_protocol_version6_module_func_deserialize(internet_protocol_version6_module_t * module, protocol_packet_t * packet, uint32_t packetlen, protocol_context_t * parent, internet_protocol_version6_context_t ** context);
static int32_t internet_protocol_version6_module_func_serialize(internet_protocol_version6_module_t * module, protocol_context_t * parent, internet_protocol_version6_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen);
static void internet_protocol_version6_module_func_debug(internet_protocol_version6_module_t * module, FILE * stream, internet_protocol_version6_context_t * context);

static internet_protocol_version6_module_func_t func = {
    internet_protocol_version6_module_func_rem,
    internet_protocol_version6_module_func_deserialize,
    internet_protocol_version6_module_func_serialize,
    internet_protocol_version6_module_func_debug
};

extern internet_protocol_version6_module_t * internet_protocol_version6_module_gen(protocol_module_t * parent, protocol_module_t ** children, uint64_t childrenlen, protocol_module_map_index_t index) {
    internet_protocol_version6_module_t * module = (internet_protocol_version6_module_t *) calloc(1, sizeof(internet_protocol_version6_module_t));

    module->func = address_of(func);
    module->parent = parent;

    if(children && childrenlen && index) {
        module->children = protocol_module_map_gen(children, childrenlen, index);
    }

    return module;
}

static internet_protocol_version6_module_t * internet_protocol_version6_module_func_rem(internet_protocol_version6_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->children = protocol_module_map_rem(module->children);

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t internet_protocol_version6_module_func_deserialize(internet_protocol_version6_module_t * module, protocol_packet_t * packet, uint32_t packetlen, protocol_context_t * parent, internet_protocol_version6_context_t ** context) {
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

    internet_protocol_version6_context_version_set(*context, internet_protocol_version6_version_get(datagram));
    internet_protocol_version6_context_traffic_class_set(*context, internet_protocol_version6_traffic_class_get(datagram));
    internet_protocol_version6_context_flow_label_set(*context, internet_protocol_version6_flow_label_get(datagram));

    internet_protocol_version6_module_debug(module, stdout, *context);

    protocol_module_t * submodule = protocol_module_map_get(module->children, internet_protocol_version6_context_next_header_get(*context));

    while(submodule) {

    }

    // TODO: UPDATE

    return success;
}

static int32_t internet_protocol_version6_module_func_serialize(internet_protocol_version6_module_t * module, protocol_context_t * parent, internet_protocol_version6_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen) {
    // TODO: UPGRADE
    return fail;
}

static void internet_protocol_version6_module_func_debug(internet_protocol_version6_module_t * module, FILE * stream, internet_protocol_version6_context_t * context) {
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