#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#include "../version4.h"

static internet_protocol_version4_module_t * internet_protocol_version4_module_func_rem(internet_protocol_version4_module_t * module);
static int32_t internet_protocol_version4_module_func_deserialize(internet_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version4_context_t ** context);
static int32_t internet_protocol_version4_module_func_serialize(internet_protocol_version4_module_t * module, protocol_context_t * parent, internet_protocol_version4_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void internet_protocol_version4_module_func_debug(internet_protocol_version4_module_t * module, FILE * stream, internet_protocol_version4_context_t * context);
static int32_t internet_protocol_version4_module_func_in(internet_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version4_context_t ** context);
typedef int32_t (*internet_protocol_version4_module_func_out_t)(internet_protocol_version4_module_t *, protocol_path_node_t *, protocol_context_t *);
static internet_protocol_version4_context_t * internet_protocol_version4_module_func_context_gen(internet_protocol_version4_module_t * module, protocol_path_node_t * node, protocol_context_t * child);

static void internet_protocol_version4_option_end_debug(FILE * stream, internet_protocol_version4_option_t * option);
static void internet_protocol_version4_option_no_operation_debug(FILE * stream, internet_protocol_version4_option_t * option);
static void internet_protocol_version4_option_security_debug(FILE * stream, internet_protocol_version4_option_t * option);
static void internet_protocol_version4_option_loose_source_route_debug(FILE * stream, internet_protocol_version4_option_t * option);
static void internet_protocol_version4_option_strict_source_route_debug(FILE * stream, internet_protocol_version4_option_t * option);
static void internet_protocol_version4_option_record_route_debug(FILE * stream, internet_protocol_version4_option_t * option);
static void internet_protocol_version4_option_stream_identifier_debug(FILE * stream, internet_protocol_version4_option_t * option);
static void internet_protocol_version4_option_internet_timestamp_debug(FILE * stream, internet_protocol_version4_option_t * option);

static internet_protocol_version4_module_func_t func = {
    internet_protocol_version4_module_func_rem,
    internet_protocol_version4_module_func_deserialize,
    internet_protocol_version4_module_func_serialize,
    internet_protocol_version4_module_func_debug,
    internet_protocol_version4_module_func_in,
    (internet_protocol_version4_module_func_out_t) protocol_module_func_out,
    internet_protocol_version4_module_func_context_gen,
    nil,
    internet_protocol_version4_module_func_local_is
};

extern internet_protocol_version4_module_t * internet_protocol_version4_module_gen(protocol_module_map_t * map, internet_protocol_version4_context_handler_t on, uint32_t * addr) {
#ifndef   RELEASE
    snorlaxdbg(on == nil, false, "critical", "");
#endif // RELEASE

    internet_protocol_version4_module_t * module = (internet_protocol_version4_module_t *) calloc(1, sizeof(internet_protocol_version4_module_t));

    module->func = address_of(func);
    module->map = map;
    module->on = on;
    module->addr = addr;
    module->type = internet_protocol_version4_no;
    module->addrlen = sizeof(uint32_t);
    module->identification = time(nil);
    module->default_ttl = 64;

    return module;
}

static internet_protocol_version4_module_t * internet_protocol_version4_module_func_rem(internet_protocol_version4_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t internet_protocol_version4_module_func_deserialize(internet_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version4_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version4_context_gen(module, parent, (internet_protocol_version4_packet_t *) packet, packetlen, 0);

    if(packetlen < internet_protocol_version4_packet_header_length_min) {
        internet_protocol_version4_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version4_packet_t * datagram = (internet_protocol_version4_packet_t *) packet;

    if(packetlen < internet_protocol_version4_context_total_get(*context)) {
        internet_protocol_version4_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version4_context_checksumcal_set(*context, internet_protocol_version4_checksum_cal(datagram, internet_protocol_version4_context_packetlen_get(*context)));

    internet_protocol_version4_context_pseudo_set(*context, internet_protocol_version4_pseudo_gen(datagram), sizeof(internet_protocol_version4_pseudo_t));

    internet_protocol_version4_context_option_set(*context, internet_protocol_version4_module_option_offset_cal(datagram));
    internet_protocol_version4_context_segment_set(*context, internet_protocol_version4_module_segment_offset_cal(datagram));
    internet_protocol_version4_context_segmentlen_set(*context, internet_protocol_version4_context_segment_length_cal(*context));

    // internet_protocol_version4_context_direction_set(*context, internet_protocol_version4_direction_cal(internet_protocol_version4_context_source_get(*context), internet_protocol_version4_context_destination_get(*context), module->addr));

    internet_protocol_version4_module_debug(module, stdout, *context);

    return internet_protocol_version4_context_valid(*context) ? success : fail;
}

static int32_t internet_protocol_version4_module_func_serialize(internet_protocol_version4_module_t * module, protocol_context_t * parent, internet_protocol_version4_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    snorlaxdbg(true, false, "implement", "");
    return fail;
}

static void internet_protocol_version4_module_func_debug(internet_protocol_version4_module_t * module, FILE * stream, internet_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    char s[128];

    fprintf(stream, "| internet protocol ");
    fprintf(stream, "| %d ", internet_protocol_version4_context_version_get(context));
    fprintf(stream, "| % 2d ", internet_protocol_version4_context_length_get(context));
    fprintf(stream, "| % 3d ", internet_protocol_version4_context_service_get(context));
    fprintf(stream, "| % 6d ", internet_protocol_version4_context_total_get(context));
    fprintf(stream, "| % 6d ", internet_protocol_version4_context_identification_get(context));
    fprintf(stream, "| %04x ", internet_protocol_version4_context_fragment_get(context));
    fprintf(stream, "| % 3d ", internet_protocol_version4_context_ttl_get(context));
    fprintf(stream, "| % 3d ", internet_protocol_version4_context_protocol_get(context));
    fprintf(stream, "| % 6d ", internet_protocol_version4_context_checksum_get(context));
    fprintf(stream, "| %15s ", internet_protocol_version4_address_to_string(s, *((uint32_t *) internet_protocol_version4_context_source_ptr_get(context))));
    fprintf(stream, "| %15s ", internet_protocol_version4_address_to_string(s, *((uint32_t *) internet_protocol_version4_context_destination_ptr_get(context))));
    fprintf(stream, "|\n");
    snorlaxdbg(false, true, "implement", "option = internet_protocol_version4_context_option_get(context); option != internet_protocol_version4_context_segment_get(context) && option != nil && *option != 0 => 을 가볍게 매크로 하나로 변경하자.");
    for(internet_protocol_version4_option_t * option = internet_protocol_version4_context_option_get(context); option != internet_protocol_version4_context_segment_get(context) && option != nil && *option != 0; option = internet_protocol_version4_context_option_offset_next(option)) {
        switch(internet_protocol_version4_option_type_get(option)) {
            case internet_protocol_version4_option_type_end:                    internet_protocol_version4_option_end_debug(stream, option);                    break;
            case internet_protocol_version4_option_type_no_operation:           internet_protocol_version4_option_no_operation_debug(stream, option);           break;
            case internet_protocol_version4_option_type_security:               internet_protocol_version4_option_security_debug(stream, option);               break;
            case internet_protocol_version4_option_type_loose_source_route:     internet_protocol_version4_option_loose_source_route_debug(stream, option);     break;
            case internet_protocol_version4_option_type_strict_source_route:    internet_protocol_version4_option_strict_source_route_debug(stream, option);    break;
            case internet_protocol_version4_option_type_record_route:           internet_protocol_version4_option_record_route_debug(stream, option);           break;
            case internet_protocol_version4_option_type_stream_identifier:      internet_protocol_version4_option_stream_identifier_debug(stream, option);      break;
            case internet_protocol_version4_option_type_internet_timestamp:     internet_protocol_version4_option_internet_timestamp_debug(stream, option);     break;
            default:                                                            snorlaxdbg(true, false, "critical", "");                                        break;
        }
    }
}

static void internet_protocol_version4_option_end_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    fprintf(stream, "| option | end of option list |\n");
}

static void internet_protocol_version4_option_no_operation_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    fprintf(stream, "| option | no operation |\n");
}

static void internet_protocol_version4_option_security_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    fprintf(stream, "| option | security | % 3d ", internet_protocol_version4_option_length_get(option));
    fprintf(stream, "| %04x ", internet_protocol_version4_option_security_field_get(option));
    fprintf(stream, "| %04x ", internet_protocol_version4_option_security_compartment_field_get(option));
    fprintf(stream, "| %04x ", internet_protocol_version4_option_security_handling_restriction_field_get(option));
    fprintf(stream, "| %04x ", internet_protocol_version4_option_security_transmission_control_code_field_get(option));
    fprintf(stream, "|\n");
}

static void internet_protocol_version4_option_loose_source_route_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    uint8_t pointer = internet_protocol_version4_option_loose_source_route_pointer_get(option);

    fprintf(stream, "| option | loose source route | % 3d ", internet_protocol_version4_option_length_get(option));
    fprintf(stream, "| % 3d ", pointer);
    for(uint32_t * addr = internet_protocol_version4_option_loose_source_route_address_begin(option); addr != internet_protocol_version4_option_loose_source_route_address_end(option); addr = addr + 1) {
        fprintf(stream, "| %15s ", internet_protocol_version4_address_uint32_to_str(*addr));
    }
    fprintf(stream, "|\n");
}

static void internet_protocol_version4_option_strict_source_route_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    uint8_t pointer = internet_protocol_version4_option_strict_source_route_pointer_get(option);

    fprintf(stream, "| option | loose source route | % 3d ", internet_protocol_version4_option_length_get(option));
    fprintf(stream, "| % 3d ", pointer);
    for(uint32_t * addr = internet_protocol_version4_option_strict_source_route_address_begin(option); addr != internet_protocol_version4_option_strict_source_route_address_end(option); addr = addr + 1) {
        fprintf(stream, "| %15s ", internet_protocol_version4_address_uint32_to_str(*addr));
    }
    fprintf(stream, "|\n");
}

static void internet_protocol_version4_option_record_route_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    uint8_t pointer = internet_protocol_version4_option_record_route_pointer_get(option);

    fprintf(stream, "| option | loose source route | % 3d ", internet_protocol_version4_option_length_get(option));
    fprintf(stream, "| % 3d ", pointer);
    for(uint32_t * addr = internet_protocol_version4_option_record_route_address_begin(option); addr != internet_protocol_version4_option_record_route_address_end(option); addr = addr + 1) {
        fprintf(stream, "| %15s ", internet_protocol_version4_address_uint32_to_str(*addr));
    }
    fprintf(stream, "|\n");
}

static void internet_protocol_version4_option_stream_identifier_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    fprintf(stream, "| option | stream identifier | % 6d |\n", internet_protocol_version4_option_stream_id_get(option));
}

static void internet_protocol_version4_option_internet_timestamp_debug(FILE * stream, internet_protocol_version4_option_t * option) {
    uint8_t flag = internet_protocol_version4_option_internet_timestamp_flag_get(option);

    fprintf(stream, "| option | internet timestamp | % 3d ", internet_protocol_version4_option_length_get(option));
    fprintf(stream, "| % 3d ", internet_protocol_version4_option_internet_timestamp_pointer_get(option));
    fprintf(stream, "| % 2d ", internet_protocol_version4_option_internet_timestamp_overflow_get(option));
    fprintf(stream, "| % 2d ", flag);

    if(flag == 0) {
        for(uint32_t * timestamp = internet_protocol_version4_option_internet_timestamp_begin(option); timestamp != internet_protocol_version4_option_internet_timestamp_end(option); timestamp = timestamp + 1) {
            fprintf(stream, "| %u ", *timestamp);
        }
    } else {
        for(uint32_t * addr = internet_protocol_version4_option_internet_timestamp_begin(option); addr != internet_protocol_version4_option_internet_timestamp_end(option); addr = addr + 2) {
            uint32_t * timestamp = addr + 1;
            fprintf(stream, "| %15s ", internet_protocol_version4_address_uint32_to_str(*addr));
            fprintf(stream, "| %u ", *timestamp);
        }
    }

    fprintf(stream, "|\n");
}

static int32_t internet_protocol_version4_module_func_in(internet_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, protocol_context_t * parent, internet_protocol_version4_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version4_context_gen(module, parent, (internet_protocol_version4_packet_t *) packet, packetlen, 0);

    if(internet_protocol_version4_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        snorlaxdbg(internet_protocol_version4_context_error_get(*context) == 0, false, "critical", "");
        internet_protocol_version4_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    if(internet_protocol_version4_module_on(module, protocol_event_in, parent, *context) == fail) {
        snorlaxdbg(internet_protocol_version4_context_error_get(*context) == 0, false, "critical", "");
        internet_protocol_version4_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    snorlaxdbg(false, true, "implement", "option");

    protocol_module_t * submodule = protocol_module_map_get(module->map, internet_protocol_version4_context_protocol_get(*context));

    if(submodule) {
        protocol_packet_t * segment = (protocol_packet_t *) internet_protocol_version4_context_segment_get(*context);
        uint64_t segmentlen = internet_protocol_version4_context_segmentlen_get(*context);
        if(protocol_module_in(submodule, segment, segmentlen, (protocol_context_t *) *context, protocol_context_array_pop((*context)->children)) == fail) {
            internet_protocol_version4_context_error_set(*context, ECHILD);
            internet_protocol_version4_module_on(module, protocol_event_exception, parent, *context);
            return fail;
        }
    }

    internet_protocol_version4_module_on(module, protocol_event_complete_in, parent, *context);

    return success;
}

extern int32_t internet_protocol_version4_module_func_on(internet_protocol_version4_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version4_context_t * context) {
    snorlaxdbg(false, true, "debug", "type => %u", type);

    if(type == protocol_event_exception) {
        snorlaxdbg(false, true, "debug", "exception => %d", internet_protocol_version4_context_error_get(context));
    }
    
    return success;
}

extern int32_t internet_protocol_version4_module_func_local_is(internet_protocol_version4_module_t * module, uint32_t addr) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    if(module->addr) {
        uint32_t local = htons(*module->addr);

        return local = addr;
    }
    
    return false;
}

static internet_protocol_version4_context_t * internet_protocol_version4_module_func_context_gen(internet_protocol_version4_module_t * module, protocol_path_node_t * node, protocol_context_t * child) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(child == nil, false, "critical", "");
#endif // RELEASE
    internet_protocol_version4_context_t * context = internet_protocol_version4_context_gen(module, nil, (internet_protocol_version4_packet_t *) child->packet, child->packetlen, child->bufferlen);

    protocol_context_parent_set(child, context);

    protocol_context_array_push(context->children, child);
    internet_protocol_version4_context_segment_set(context, child->packet);
    internet_protocol_version4_context_segmentlen_set(context, child->packetlen);

    snorlaxdbg(false, true, "debug", "option");

    internet_protocol_version4_context_buffer_reserve(context, internet_protocol_version4_packet_header_length_min);

    internet_protocol_version4_context_version_set(context, 4);
    internet_protocol_version4_context_length_set(context, internet_protocol_version4_packet_header_length_min / 4);
    internet_protocol_version4_context_total_set(context, internet_protocol_version4_context_packetlen_get(context));
    fprintf(stdout, "internet_protocol_version4_context_total_get(context) => %u\n", internet_protocol_version4_context_total_get(context));
    internet_protocol_version4_context_identification_set(context, internet_protocol_version4_module_identification_gen(module));
    internet_protocol_version4_context_fragment_set(context, internet_protocol_version4_fragment_field_gen(1, 0, 0));
    internet_protocol_version4_context_ttl_set(context, internet_protocol_version4_module_default_ttl_get(module));
    internet_protocol_version4_context_protocol_set(context, protocol_module_number_get(child->module));
    internet_protocol_version4_context_checksum_set(context, internet_protocol_version4_context_checksum_cal(context));
    internet_protocol_version4_context_source_set(context, ntohl(internet_protocol_version4_to_addr(protocol_path_node_destination_get(node))));
    internet_protocol_version4_context_destination_set(context, ntohl(internet_protocol_version4_to_addr(protocol_path_node_source_get(node))));

    context->pseudo = internet_protocol_version4_pseudo_gen(internet_protocol_version4_context_datagram_get(context));
    context->pseudolen = sizeof(internet_protocol_version4_pseudo_t);

    protocol_context_checksum_build(child, (uint8_t *) context->pseudo, context->pseudolen);

    snorlaxdbg(protocol_context_valid(child) == false, false, "critical", "");

    // internet_protocol_version4_context_checksum_cal()

    internet_protocol_version4_context_checksum_build(context, nil, 0);

//    internet_protocol_version4_context_checksum_set(context, internet_protocol_version4_context_checksum_cal(context));

    snorlaxdbg(protocol_context_valid(context) == false, false, "critical", "");

    return context;
}