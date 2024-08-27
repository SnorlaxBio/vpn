#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "../../../control.h"

extern int32_t transmission_control_block_complete_in_closed(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE
    

    return success;
}

extern int32_t transmission_control_block_complete_in_listen(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_synchronize_sequence_sent(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_synchronize_sequence_recv(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(block->agent == nil, false, "critical", "");
#endif // RELEASE

    if(transmission_control_block_state_is_changed(block)) {
        uint8_t  buffer[protocol_packet_max];
        uint64_t bufferlen = protocol_packet_max;

        transmission_control_protocol_context_t * response = transmission_control_protocol_context_gen(block->module, nil, (transmission_control_protocol_packet_t *) (buffer - protocol_packet_max), 0, address_of(bufferlen));

        snorlaxdbg(response == nil, false, "critical", "");

        transmission_control_protocol_context_block_set(response, block);

        snorlaxdbg(false, true, "implement", "data");
        snorlaxdbg(false, true, "implement", "option");

        uint64_t headerlen = 0;

        transmission_control_protocol_option_maximum_segment_size_t mss = { .kind = 2, .length = 4, .size = transmission_control_block_maximum_segment_get(block) };
        transmission_control_protocol_context_buffer_reversal_push(block, (uint8_t *) address_of(mss), sizeof(transmission_control_protocol_option_maximum_segment_size_t));
        headerlen = headerlen + sizeof(transmission_control_protocol_option_maximum_segment_size_t);

        transmission_control_protocol_option_window_scale_t ws = { .kind = 2, .length = 3, .size = transmission_control_block_window_scale_get(block), .pad = 1 };
        transmission_control_protocol_context_buffer_reversal_push(block, (uint8_t *) address_of(ws), sizeof(transmission_control_protocol_option_window_scale_t));
        headerlen = headerlen + sizeof(transmission_control_protocol_option_window_scale_t);

        protocol_path_node_t * path = protocol_path_begin(block->path);

        transmission_control_protocol_context_buffer_reversal_reserve(response, transmission_control_protocol_packet_length_min);
        headerlen = headerlen + transmission_control_protocol_packet_length_min;
        transmission_control_protocol_context_headerlen_add(response, headerlen);

        transmission_control_protocol_context_source_set(response, ntohs(transmission_control_protocol_to_port(protocol_path_node_destination_get(path))));
        transmission_control_protocol_context_destination_set(response, ntohs(transmission_control_protocol_to_port(protocol_path_node_source_get(path))));
        transmission_control_protocol_context_sequence_set(response, transmission_control_block_sequence_get(block));
        transmission_control_protocol_context_acknowledge_set(response, transmission_control_block_acknowledge_get(block));

        snorlaxdbg((headerlen & 0x03u != 0), false, "critical", "");

        transmission_control_protocol_context_offset_set(response, transmission_control_protocol_context_headerlen_get(response) / 4);
        transmission_control_protocol_context_flags_set(response, transmission_control_flag_control_synack);
        transmission_control_protocol_context_window_set(response, transmission_control_block_window_get(block));
        transmission_control_protocol_context_urgent_set(response, 0);

        transmission_control_protocol_module_debug(block->module, stdout, response);

        protocol_path_node_t * parent = protocol_path_node_next(path);
        uint8_t * packet = buffer + bufferlen;

        if(protocol_module_out(parent->module, parent, (protocol_context_t *) response) == fail) {
            return fail;
        }

        snorlaxdbg(bufferlen == protocol_packet_max, false, "critical", "");

        transmission_control_block_buffer_t * out = block->buffer.out;
        transmission_control_block_buffer_out_t * node = transmission_control_block_buffer_out_gen(out, (buffer + bufferlen), (protocol_packet_max - bufferlen));

        transmission_control_block_buffer_out_segment_set(node, packet);

        transmission_control_block_state_prev_set(block, transmission_control_block_state_get(block));
    } else {
        snorlaxdbg(false, true, "warning", "packet drop & retransmission synack packet");

        // if(transmission_control_protocol_context_flags_get(context) & )

        return success;
    }
}

extern int32_t transmission_control_block_complete_in_establish(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    if(transmission_control_block_state_is_changed(block)) {
        // snorlaxdbg(transmission_control_block_buffer_out_head(block->buffer.out), false, "implement", "");

        snorlaxdbg(false, true, "implement", "");
    } else {
        snorlaxdbg(true, false, "implement", "");
    }

    return fail;
}

extern int32_t transmission_control_block_complete_in_finish_wait_first(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_finish_wait_second(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_close_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_closing(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_last_acknowledge(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_time_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_complete_in_exception(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}
