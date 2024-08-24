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
        snorlaxdbg(transmission_control_block_state_prev_get(block) != transmission_control_state_closed, false, "critical", "");

        uint32_t acknowledge = transmission_control_block_remote_sequence_get(block) + 1;

        transmission_control_block_acknowledge_set(block, acknowledge);

        uint8_t  buffer[protocol_packet_max];
        uint64_t bufferlen = protocol_packet_max;

        transmission_control_protocol_context_t * response = transmission_control_protocol_context_gen(block->module, nil, (transmission_control_protocol_packet_t *) (buffer - protocol_packet_max), 0, address_of(bufferlen));

        snorlaxdbg(response == nil, false, "critical", "");

        snorlaxdbg(false, true, "implement", "option");

        protocol_path_node_t * path = protocol_path_begin(block->path);

        transmission_control_protocol_context_buffer_reversal_reserve(response, transmission_control_protocol_packet_length_min);
        transmission_control_protocol_context_headerlen_add(response, transmission_control_protocol_packet_length_min);

        snorlaxdbg(false, true, "refactor", "transmission_control_protocol_to_port => transmission_control_protocol_address_to_port");

        transmission_control_protocol_context_source_set(response, ntohs(transmission_control_protocol_to_port(protocol_path_node_destination_get(path))));
        transmission_control_protocol_context_destination_set(response, ntohs(transmission_control_protocol_to_port(protocol_path_node_source_get(path))));
        transmission_control_protocol_context_sequence_set(response, transmission_control_block_sequence_get(block));
        transmission_control_protocol_context_acknowledge_set(response, transmission_control_block_acknowledge_get(block));
        transmission_control_protocol_context_offset_set(response, transmission_control_protocol_context_headerlen_get(response) / 4);
        transmission_control_protocol_context_flags_set(response, transmission_control_flag_control_synack);
        transmission_control_protocol_context_window_set(response, transmission_control_block_window_get(block));
        transmission_control_protocol_context_urgent_set(response, 0);

        transmission_control_protocol_module_debug(block->module, stdout, response);

        protocol_path_node_t * parent = protocol_path_node_next(path);

        if(protocol_module_out(parent->module, parent, (protocol_context_t *) response) == fail) {
            snorlaxdbg(false, true, "debug", "fail to protocol_module_out(...)");

            return fail;
        }

        transmission_control_block_buffer_out_t * out = block->buffer.out;

        snorlaxdbg(bufferlen == protocol_packet_max, false, "critical", "");

        transmission_control_block_buffer_out_node_t * node = transmission_control_block_buffer_out_node_gen(out, (buffer + bufferlen), (protocol_packet_max - bufferlen));

        node->sequence = transmission_control_block_sequence_get(block);
        node->acknowledge = node->sequence + 1;
    
        return success;
    } else {
        snorlaxdbg(transmission_control_block_state_is_changed(block) == false, false, "implement", "");
        /**
         * 정책을 정하면 구현을 하자.
         * 
         * RETRANSMIT OR DROP PACKET
         * 
         * 아직은 정책이 정해지지 않았지만,
         * 이 상태는 아직은 변경되지 않아서, SYN 을 받은 것이다.
         * 그래서 이전에 받은 패킷이 존재해야 한다.
         * 그렇다면, 바로 RETRANSMIT 을 하고 타이머를 업데이트할 것인가?
         * 아니면 RETRANSMIT 타이머대로 동작하도록 할 것인가?
         * DDOS 가 오면, 타이머에 맞기는 것이 맞다. 패킷 드롭
         * 하지만, 타이머의 비용은 ????
         */

        return fail;
    }

}

extern int32_t transmission_control_block_complete_in_establish(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

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
