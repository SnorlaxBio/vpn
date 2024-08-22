#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>

#include "../control.h"
#include "../../../internet.h"
#include "../../../internet/version4.h"
#include "../../../internet/version6.h"

static transmission_control_protocol_module_t * transmission_control_protocol_module_func_rem(transmission_control_protocol_module_t * module);
static int32_t transmission_control_protocol_module_func_deserialize(transmission_control_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_context_t * parent, transmission_control_protocol_context_t ** context);
static int32_t transmission_control_protocol_module_func_serialize(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void transmission_control_protocol_module_func_debug(transmission_control_protocol_module_t * module, FILE * stream, transmission_control_protocol_context_t * context);
static int32_t transmission_control_protocol_module_func_in(transmission_control_protocol_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_context_t * parent, transmission_control_protocol_context_t ** context);
static int32_t transmission_control_protocol_module_func_out(transmission_control_protocol_module_t * module, protocol_path_node_t * node, protocol_context_t * context);

static transmission_control_protocol_module_func_t func = {
    transmission_control_protocol_module_func_rem,
    transmission_control_protocol_module_func_deserialize,
    transmission_control_protocol_module_func_serialize,
    transmission_control_protocol_module_func_debug,
    transmission_control_protocol_module_func_in,
    transmission_control_protocol_module_func_out,
    nil,
    nil,
    transmission_control_protocol_module_func_blockon,
    transmission_control_protocol_module_func_sequence_gen
};

extern transmission_control_protocol_module_t * transmission_control_protocol_module_gen(protocol_module_map_t * map, transmission_control_protocol_context_handler_t on) {
    transmission_control_protocol_module_t * module = (transmission_control_protocol_module_t *) calloc(1, sizeof(transmission_control_protocol_module_t));

    module->func = address_of(func);

    module->map = map;
    module->on = on;
    module->block = hashtable_gen(transmission_control_block_func_hash);
    module->addrlen = sizeof(uint16_t);
    module->type = transmission_control_protocol_no;
    module->max_segment_size = transmission_control_protocol_default_max_segment_size;

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

    if(*context == nil) *context = transmission_control_protocol_context_gen(module, parent, segment, packetlen, 0);

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
    transmission_control_protocol_context_checksumcal_set(*context, transmission_control_protocol_checksum_cal(segment, packetlen, internet_protocol_context_pseudo_get(parent), internet_protocol_context_pseudolen_get(parent)));

    transmission_control_protocol_context_data_set(*context, transmission_control_protocol_context_data_cal(*context));
    transmission_control_protocol_context_option_set(*context, transmission_control_protocol_context_option_cal(*context));

    // TODO: 메모리를 절약할 수 있는 방법을 찾자 혹은 계산량을 줄일 수 있는 방법을 찾자.
    transmission_control_protocol_context_key_gen(*context);

    // if(internet_protocol_local)

    transmission_control_protocol_module_debug(module, stdout, *context);

    return transmission_control_protocol_context_valid(*context) ? success : fail;
}

static int32_t transmission_control_protocol_module_func_serialize(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    snorlaxdbg(true, false, "critical", "");
    return fail;
}

static void transmission_control_protocol_module_func_debug(transmission_control_protocol_module_t * module, FILE * stream, transmission_control_protocol_context_t * context) {
    fprintf(stream, "| transmission control protocol ");
    fprintf(stream, "| %u ", transmission_control_protocol_context_source_get(context));
    fprintf(stream, "| %u ", transmission_control_protocol_context_destination_get(context));
    fprintf(stream, "| %u ", transmission_control_protocol_context_sequence_get(context));
    fprintf(stream, "| %u ", transmission_control_protocol_context_acknowledge_get(context));
    fprintf(stream, "| %d ", transmission_control_protocol_context_offset_get(context));
    fprintf(stream, "| cwr %c ", transmission_control_protocol_context_cwr_get(context) ? 'o' : 'x');
    fprintf(stream, "| ece %c ", transmission_control_protocol_context_ece_get(context) ? 'o' : 'x');
    fprintf(stream, "| urg %c ", transmission_control_protocol_context_urg_get(context) ? 'o' : 'x');
    fprintf(stream, "| ack %c ", transmission_control_protocol_context_ack_get(context) ? 'o' : 'x');
    fprintf(stream, "| psh %c ", transmission_control_protocol_context_psh_get(context) ? 'o' : 'x');
    fprintf(stream, "| rst %c ", transmission_control_protocol_context_rst_get(context) ? 'o' : 'x');
    fprintf(stream, "| syn %c ", transmission_control_protocol_context_syn_get(context) ? 'o' : 'x');
    fprintf(stream, "| fin %c ", transmission_control_protocol_context_fin_get(context) ? 'o' : 'x');
    fprintf(stream, "| %u ", transmission_control_protocol_context_window_get(context));
    fprintf(stream, "| %u ", transmission_control_protocol_context_checksum_get(context));
    fprintf(stream, "| %u ", transmission_control_protocol_context_urgent_get(context));
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

    snorlaxdbg(false, true, "implement", "");

    transmission_control_protocol_packet_t * segment = (transmission_control_protocol_packet_t *) packet;

    if(*context == nil) *context = transmission_control_protocol_context_gen(module, parent, segment, packetlen, 0);

    if(transmission_control_protocol_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        transmission_control_protocol_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    if(transmission_control_protocol_module_on(module, protocol_event_in, parent, *context) == fail) {
        transmission_control_protocol_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    transmission_control_protocol_module_on(module, protocol_event_complete_in, parent, *context);

    return success;
}

extern int32_t transmission_control_protocol_module_func_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    snorlaxdbg(false, true, "debug", "type => %u", type);

    if(type == protocol_event_in) {
        // module->
    } else if(type == protocol_event_exception) {
        snorlaxdbg(false, true, "debug", "exception => %u", transmission_control_protocol_context_error_get(context));
    }

    return success;
}

extern int32_t transmission_control_protocol_module_func_blockon(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    if(context->block == nil) {
        context->block = (transmission_control_block_t *) hashtable_get(module->block, address_of(context->key));
        if(type == protocol_event_in && context->block == nil) {
            if(transmission_control_protocol_context_is_connect_syn(context)) {
                hashtable_set(module->block, (hashtable_node_t *) (context->block = transmission_control_block_gen(address_of(context->key), module, context)));

                return success;
            }

            // | transmission control protocol | 52756 | 22 | 3255904328 | 324549507 | 8 | cwr x | ece x | urg x | ack o | psh x | rst x | syn x | fin x | 501 | 2220 | 0 |
            // 위의 패킷처럼 중간에 빠져 나오는 패킷이 있다. 이럴 경우, 빠르게 CLOSE IP 를 보내도록 하자.
            transmission_control_protocol_context_error_set(context, EINVAL);
            snorlaxdbg(false, true, "implement", "fast close");

            return fail;
        }
    }

    switch(type) {
        case protocol_event_in:                 return transmission_control_block_event_in_on(context->block, parent, context);
        case protocol_event_out:                return transmission_control_block_event_out_on(context->block, parent, context);
        case protocol_event_exception:          return transmission_control_block_event_exception_on(context->block, parent, context);
        case protocol_event_complete:           return transmission_control_block_event_complete_on(context->block, parent, context);
        case protocol_event_complete_in:        return transmission_control_block_event_complete_in_on(context->block, parent, context);
        case protocol_event_complete_out:       return transmission_control_block_event_complete_out_on(context->block, parent, context);
        default:                                return transmission_control_block_event_none_on(context->block, parent, context);
    }
}

extern uint32_t transmission_control_protocol_module_func_sequence_gen(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint32_t seq = time(nil);

    seq = seq + transmission_control_protocol_context_source_get(context);
    seq = seq + transmission_control_protocol_context_destination_get(context);

    uint8_t version = internet_protocol_context_version_get(parent);

    if(version == 4) {
        seq = seq + internet_protocol_version4_context_source_get((internet_protocol_version4_context_t *) parent);
        seq = seq + internet_protocol_version4_context_destination_get((internet_protocol_version4_context_t *) parent);
    } else if(version == 6) {
        uint32_t * addr = (uint32_t *) internet_protocol_version6_context_source_get((internet_protocol_version6_context_t *) parent);

        for(int i = 0; i < 4; i++, addr++) seq = seq + (*addr);

        addr = (uint32_t *) internet_protocol_version6_context_destination_get((internet_protocol_version6_context_t *) parent);

        for(int i = 0; i < 4; i++, addr++) seq = seq + (*addr);
    } else {
        snorlaxdbg(version != 4 && version != 6, false, "critical", "");
    }
    // seq += internet_protocol_

    return seq;
}

static int32_t transmission_control_protocol_module_func_out(transmission_control_protocol_module_t * module, protocol_path_node_t * node, protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    /**
     * TCP 의 경우 CONTROL BLOCK BUFFER 에 데이터를 삽입하고, 끝낸다.
     */

    snorlaxdbg(true, false, "critical", "");

    return fail;
}