#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

#include "../control.h"

static transmission_control_protocol_module_t * transmission_control_protocol_module_func_rem(transmission_control_protocol_module_t * module);
static int32_t transmission_control_protocol_module_func_deserialize(transmission_control_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_context_t * parent, transmission_control_protocol_context_t ** context);
static int32_t transmission_control_protocol_module_func_serialize(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void transmission_control_protocol_module_func_debug(transmission_control_protocol_module_t * module, FILE * stream, transmission_control_protocol_context_t * context);
static int32_t transmission_control_protocol_module_func_in(transmission_control_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_context_t * parent, transmission_control_protocol_context_t ** context);

static transmission_control_protocol_module_func_t func = {
    transmission_control_protocol_module_func_rem,
    transmission_control_protocol_module_func_deserialize,
    transmission_control_protocol_module_func_serialize,
    transmission_control_protocol_module_func_debug,
    transmission_control_protocol_module_func_in
};

extern transmission_control_protocol_module_t * transmission_control_protocol_module_gen(protocol_module_map_t * map, transmission_control_protocol_context_handler_t on) {
    transmission_control_protocol_module_t * module = (transmission_control_protocol_module_t *) calloc(1, sizeof(transmission_control_protocol_module_t));

    module->func = address_of(func);

    module->map = map;
    module->on = on;

    return module;
}

static transmission_control_protocol_module_t * transmission_control_protocol_module_func_rem(transmission_control_protocol_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t transmission_control_protocol_module_func_deserialize(transmission_control_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_context_t * parent, transmission_control_protocol_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_protocol_packet_t * segment = (transmission_control_protocol_packet_t *) packet;

    if(*context == nil) *context = transmission_control_protocol_context_gen(parent, segment, packetlen);

    if(packetlen < transmission_control_protocol_packet_length_min) {
        transmission_control_protocol_context_error_set(*context, EAGAIN);
        return fail;
    }

    transmission_control_protocol_context_headerlen_set(*context, transmission_control_protocol_context_offset_get(*context) * 4);

    if(packetlen < transmission_control_protocol_context_headerlen_get(*context)) {
        transmission_control_protocol_context_error_set(*context, EAGAIN);
        return fail;
    }

    transmission_control_protocol_context_datalen_set(*context, packetlen - transmission_control_protocol_context_headerlen_get(*context));
    transmission_control_protocol_context_checksum_set(*context, ntohs(segment->checksum));

    uint16_t checksum = transmission_control_protocol_checksum_cal(segment, packetlen, internet_protocol_context_pseudo_get(parent), internet_protocol_context_pseudolen_get(parent));

    if(checksum != transmission_control_protocol_context_checksum_get(*context)) {
        transmission_control_protocol_context_error_set(*context, EIO);
        return fail;
    }

    transmission_control_protocol_context_source_set(*context, ntohs(segment->source));
    transmission_control_protocol_context_destination_set(*context, ntohs(segment->destination));
    transmission_control_protocol_context_sequence_set(*context, ntohs(segment->sequence));
    transmission_control_protocol_context_acknowledgment_set(*context, ntohs(segment->acknowledgment));
    transmission_control_protocol_context_window_set(*context, ntohs(segment->window));
    transmission_control_protocol_context_urgent_set(*context, ntohs(segment->pointer));
    transmission_control_protocol_context_data_set(*context, transmission_control_protocol_context_data_cal(*context));
    transmission_control_protocol_context_option_set(*context, transmission_control_protocol_context_option_cal(*context));

    transmission_control_protocol_module_debug(module, stdout, *context);

    return success;
}

static int32_t transmission_control_protocol_module_func_serialize(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    snorlaxdbg(true, false, "critical", "");
    return fail;
}

static void transmission_control_protocol_module_func_debug(transmission_control_protocol_module_t * module, FILE * stream, transmission_control_protocol_context_t * context) {
    fprintf(stream, "| transmission control protocol ");
    fprintf(stream, "| %d ", transmission_control_protocol_context_source_get(context));
    fprintf(stream, "| %d ", transmission_control_protocol_context_destination_get(context));
    fprintf(stream, "| %d ", transmission_control_protocol_context_sequence_get(context));
    fprintf(stream, "| %d ", transmission_control_protocol_context_acknowledgment_get(context));
    fprintf(stream, "| %d ", transmission_control_protocol_context_offset_get(context));
    fprintf(stream, "| cwr %c ", transmission_control_protocol_context_cwr_get(context) ? 'o' : 'x');
    fprintf(stream, "| ece %c ", transmission_control_protocol_context_ece_get(context) ? 'o' : 'x');
    fprintf(stream, "| urg %c ", transmission_control_protocol_context_urg_get(context) ? 'o' : 'x');
    fprintf(stream, "| ack %c ", transmission_control_protocol_context_ack_get(context) ? 'o' : 'x');
    fprintf(stream, "| psh %c ", transmission_control_protocol_context_psh_get(context) ? 'o' : 'x');
    fprintf(stream, "| rst %c ", transmission_control_protocol_context_rst_get(context) ? 'o' : 'x');
    fprintf(stream, "| syn %c ", transmission_control_protocol_context_syn_get(context) ? 'o' : 'x');
    fprintf(stream, "| fin %c ", transmission_control_protocol_context_fin_get(context) ? 'o' : 'x');
    fprintf(stream, "| %d ", transmission_control_protocol_context_window_get(context));
    fprintf(stream, "| %d ", transmission_control_protocol_context_checksum_get(context));
    fprintf(stream, "| %d ", transmission_control_protocol_context_urgent_get(context));
    fprintf(stream, "|\n");
}

static int32_t transmission_control_protocol_module_func_in(transmission_control_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_context_t * parent, transmission_control_protocol_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_protocol_packet_t * segment = (transmission_control_protocol_packet_t *) packet;

    if(*context == nil) *context = transmission_control_protocol_context_gen(parent, segment, packetlen);

    if(transmission_control_protocol_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        transmission_control_protocol_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    return transmission_control_protocol_module_on(module, protocol_event_in, parent, *context);
}

extern int32_t transmission_control_protocol_module_func_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    return success;
}
