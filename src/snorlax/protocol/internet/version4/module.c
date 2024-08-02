#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../version4.h"

static internet_protocol_version4_module_t * internet_protocol_version4_module_func_rem(internet_protocol_version4_module_t * module);
static int32_t internet_protocol_version4_module_func_deserialize(internet_protocol_version4_module_t * module, protocol_packet_t * packet, uint32_t packetlen, protocol_context_t * parent, internet_protocol_version4_context_t ** context);
static int32_t internet_protocol_version4_module_func_serialize(internet_protocol_version4_module_t * module, protocol_context_t * parent, internet_protocol_version4_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen);
static void internet_protocol_version4_module_func_debug(internet_protocol_version4_module_t * module, FILE * stream, internet_protocol_version4_context_t * context);

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
    internet_protocol_version4_module_func_debug
};

extern internet_protocol_version4_module_t * internet_protocol_version4_module_gen(protocol_module_t * parent, protocol_module_t ** children, uint64_t childrenlen, protocol_module_map_index_t index) {
    internet_protocol_version4_module_t * module = (internet_protocol_version4_module_t *) calloc(1, sizeof(internet_protocol_version4_module_t));

    module->func = address_of(func);

    module->parent = parent;

    if(children && childrenlen && index) {
        module->children = protocol_module_map_gen(children, childrenlen, index);
    }

    return module;
}

extern uint16_t internet_protocol_version4_module_checksum_cal(internet_protocol_version4_packet_t * datagram) {
    uint16_t checksum = datagram->checksum;

    datagram->checksum = 0;

    uint16_t * packet = (uint16_t *) datagram;
    uint32_t n = (datagram->length * 2);
    uint16_t v = 0;

    for(uint32_t i = 0; i < n; i++) {
        v = v + ntohs(packet[i]);
    }

    datagram->checksum = checksum;

    return ~v;
}

static internet_protocol_version4_module_t * internet_protocol_version4_module_func_rem(internet_protocol_version4_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->children = protocol_module_map_rem(module->children);

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t internet_protocol_version4_module_func_deserialize(internet_protocol_version4_module_t * module, protocol_packet_t * packet, uint32_t packetlen, protocol_context_t * parent, internet_protocol_version4_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_protocol_version4_context_gen(parent, (internet_protocol_version4_packet_t *) packet, packetlen);

    if(packetlen < internet_protocol_version4_packet_header_length_min) {
        internet_protocol_version4_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version4_packet_t * datagram = (internet_protocol_version4_packet_t *) packet;

    internet_protocol_version4_context_total_set(*context, datagram->length);

    if(packetlen < internet_protocol_version4_context_total_get(*context)) {
        internet_protocol_version4_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_protocol_version4_context_checksum_set(*context, ntohs(datagram->checksum));

    uint16_t checksum = internet_protocol_version4_module_checksum_cal(datagram);

    if(checksum != internet_protocol_version4_context_checksum_get(*context)) {
        internet_protocol_version4_context_error_set(*context, EIO);
        return fail;
    }

    internet_protocol_version4_context_identification_set(*context, ntohs(datagram->identification));
    internet_protocol_version4_context_fragment_set(*context, ntohs(datagram->fragment));
    internet_protocol_version4_context_source_set(*context, ntohl(datagram->source));
    internet_protocol_version4_context_destination_set(*context, ntohl(datagram->destination));
    internet_protocol_version4_context_option_offset_set(*context, internet_protocol_version4_module_option_offset_cal(datagram));
    internet_protocol_version4_context_segment_offset_set(*context, internet_protocol_version4_module_segment_offset_cal(datagram));
    internet_protocol_version4_context_segment_length_set(*context, internet_protocol_version4_context_segment_length_cal(*context));

    internet_protocol_version4_module_debug(module, stdout, *context);

    protocol_module_t * submodule = protocol_module_map_get(module->children, internet_protocol_version4_context_protocol_get(*context));

    if(submodule) {
        return protocol_module_deserialize(submodule, internet_protocol_version4_context_segment_offset_get(*context), internet_protocol_version4_context_segment_length_get(*context), (protocol_context_t *) *context, address_of((*context)->subcontext));
    } else {
#ifndef   RELEASE
        snorlaxdbg(false, true, "implement", "");
#endif // RELEASE
    }

    return success;
}

static int32_t internet_protocol_version4_module_func_serialize(internet_protocol_version4_module_t * module, protocol_context_t * parent, internet_protocol_version4_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen) {
    return fail;
}

static void internet_protocol_version4_module_func_debug(internet_protocol_version4_module_t * module, FILE * stream, internet_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

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
    fprintf(stream, "| %15s ", internet_protocol_version4_address_uint32_to_str(internet_protocol_version4_context_source_get(context)));
    fprintf(stream, "| %15s ", internet_protocol_version4_address_uint32_to_str(internet_protocol_version4_context_destination_get(context)));
    fprintf(stream, "|\n");

    for(internet_protocol_version4_option_t * option = internet_protocol_version4_context_option_offset_get(context); option != internet_protocol_version4_context_segment_offset_get(context) || *option == 0; option = internet_protocol_version4_context_option_offset_next(option)) {
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
