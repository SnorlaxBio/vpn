/**
 * @file        snorlax/protocol/internet/transmission/control/block.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 23, 2024
 * @see         [Transmission Control Protocol <sup>TCP</sup>](https://datatracker.ietf.org/doc/html/rfc9293)
 */
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#include "../control.h"

static transmission_control_block_t * transmission_control_block_func_rem(transmission_control_block_t * block);
static int32_t transmission_control_block_func_open(transmission_control_block_t * block);
static int32_t transmission_control_block_func_send(transmission_control_block_t * block, const uint8_t * data, uint64_t datalen);
static int32_t transmission_control_block_func_recv(transmission_control_block_t * block);
static int32_t transmission_control_block_func_close(transmission_control_block_t * block);
___implement static int32_t transmission_control_block_func_listen(transmission_control_block_t * block);
static int32_t transmission_control_block_func_in(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
static int32_t transmission_control_block_func_complete_in(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
static int32_t transmission_control_block_func_out(transmission_control_block_t * block, transmission_control_block_buffer_out_t * node);

static transmission_control_block_func_t func = {
    transmission_control_block_func_rem,
    transmission_control_block_func_open,
    transmission_control_block_func_send,
    transmission_control_block_func_recv,
    transmission_control_block_func_close,
    transmission_control_block_func_listen,
    transmission_control_block_func_in,
    transmission_control_block_func_complete_in,
    transmission_control_block_func_out
};

extern transmission_control_block_t * transmission_control_block_gen(hashtable_node_key_t * key, transmission_control_protocol_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(key == nil, false, "critical", "");
    snorlaxdbg(key->value == nil, false, "critical", "");
    snorlaxdbg(key->length == 0, false, "critical", "");
#endif // RELEASE

    transmission_control_block_t * block = (transmission_control_block_t *) calloc(1, sizeof(transmission_control_block_t));

    block->func = address_of(func);

    block->key.value = malloc(key->length);
    block->key.length = key->length;
    block->module = module;
    block->buffer.in = nil;
    block->buffer.out = nil;
    block->state.current = transmission_control_state_closed;
    block->state.prev = transmission_control_state_closed;

    memcpy(block->key.value, key->value, key->length);

    // if(context) {
    //     snorlaxdbg(context->block != nil, false, "critical", "");
    //     snorlaxdbg(context->parent == nil, false, "critical", "");

    //     block->path = protocol_path_gen((protocol_context_t *) context, 128);

    //     transmission_control_block_state_set(block, transmission_control_state_synchronize_sequence_recv);
    //     transmission_control_block_acknowledge_set(block, transmission_control_protocol_context_sequence_get(context) + 1);
    //     transmission_control_block_sequence_set(block, transmission_control_protocol_module_seqeuence_gen(context->module, context->parent, context));
    //     transmission_control_block_version_set(block, internet_protocol_context_version_get(context->parent));

    //     snorlaxdbg(false, true, "implement", "default window when transmission control block gen and remove below");
    //     transmission_control_block_window_local_set(block, transmission_control_protocol_context_window_get(context));
    //     transmission_control_block_window_remote_set(block, transmission_control_protocol_context_window_get(context));

    //     protocol_path_debug(block->path, stdout);
    // }

    return block;
}

static transmission_control_block_t * transmission_control_block_func_rem(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    block->sync = sync_rem(block->sync);

    free(block);

    return nil;
}

/**
 * @fn          int32_t transmission_control_block_func_open(transmission_control_block_t * block)
 * @brief
 * @details     
 */
static int32_t transmission_control_block_func_open(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

#ifdef    TRANSMISSION_CONTROL_PROTOCOL_SUPPORT_AUTOMATIC_OPEN
    // @see      [User/Transmission Control Protocol <sup>TCP</sup> Interface / 3.9.1.2. Send](https://datatracker.ietf.org/doc/html/rfc9293#section-3.9.1)
    snorlaxdbg(false, true, "implement", "send if data exist");
#endif // TRANSMISSION_CONTROL_PROTOCOL_SUPPORT_AUTOMATIC_OPEN
    // TRANSMISSION_CONTROL_PROTOCOL_SUPPORT_AUTOMATIC_OPEN

    // block

    // PASSIVE OPEN: SERVER
    // ACTIVE OPEN: CLIENT
    // PASSIVE OPEN & ACTIVE OPEN

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t transmission_control_block_func_recv(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t transmission_control_block_func_send(transmission_control_block_t * block, const uint8_t * data, uint64_t datalen) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "refactor", "");

    // if(transmission_control_block_avail_io(block) == false) {
    //     snorlaxdbg(transmission_control_block_avail_io(block) == false, false, "warning", "");
    //     return fail;
    // }

    // transmission_control_block_buffer_t * out = block->buffer.out;
    // transmission_control_block_buffer_node_t * node = transmission_control_block_buffer_tail(out);
    // uint64_t remain = transmission_control_block_buffer_node_remain(node);
    // uint32_t sequence = node ? transmission_control_block_buffer_node_sequence_get(node) : transmission_control_block_sequence_get(block);

    // if(remain > 0) {
    //     if(datalen <= remain) {
    //         memcpy(transmission_control_block_buffer_node_back(node), data, datalen);
    //         transmission_control_block_buffer_node_size_set(node, transmission_control_block_buffer_node_size_get(node) + datalen);

    //         transmission_control_block_out(block, node);

    //         return datalen;
    //     }

    //     memcpy(transmission_control_block_buffer_node_back(node), data, remain);
    //     transmission_control_block_buffer_node_size_set(node, transmission_control_block_buffer_node_size_get(node) + remain);

    //     data = data + remain;
    //     sequence = sequence + remain;
    // } else {
    //     node = nil;
    // }

    // uint64_t len = datalen - remain;
    // uint16_t mss = block->module->max_segment_size;
    // uint64_t n = len / mss;
    // uint64_t last = len % mss;

    // snorlaxdbg(false, true, "debug", "capacity => %u", mss);

    // for(uint64_t i = 0; i < n; i++) {
    //     /**
    //      * 매크로나 함수로 작게 만들 수 있어 보인다.
    //      */
    //     transmission_control_block_buffer_node_t * node = transmission_control_block_buffer_back(out, mss);

    //     snorlaxdbg(false, true, "debug", "capacity => %lu", transmission_control_block_buffer_node_capacity_get(node));
    //     snorlaxdbg(false, true, "debug", "size => %lu", transmission_control_block_buffer_node_size_get(node));

    //     if(transmission_control_block_buffer_node_size_get(node) == 0)  transmission_control_block_buffer_node_sequence_set(node, sequence);

    //     memcpy(transmission_control_block_buffer_node_back(node), data, mss);
    //     transmission_control_block_buffer_node_size_set(node, transmission_control_block_buffer_node_size_get(node) + mss);
    //     data = data + mss;
    //     sequence = sequence + mss;
    // }

    // if(last) {
    //     transmission_control_block_buffer_node_t * node = transmission_control_block_buffer_back(out, mss);

    //     snorlaxdbg(false, true, "debug", "capacity => %lu", transmission_control_block_buffer_node_capacity_get(node));
    //     snorlaxdbg(false, true, "debug", "size => %lu", transmission_control_block_buffer_node_size_get(node));
    //     snorlaxdbg(false, true, "debug", "position => %lu", transmission_control_block_buffer_node_position_get(node));

    //     if(transmission_control_block_buffer_node_size_get(node) == 0)  transmission_control_block_buffer_node_sequence_set(node, sequence);

    //     snorlaxdbg(false, true, "debug", "node => %p", node);
    //     snorlaxdbg(false, true, "debug", "transmission_control_block_buffer_node_front(node) => %p", transmission_control_block_buffer_node_front(node));
    //     snorlaxdbg(false, true, "debug", "data => %p", data);
    //     memcpy(transmission_control_block_buffer_node_back(node), data, last);
    //     transmission_control_block_buffer_node_size_set(node, transmission_control_block_buffer_node_size_get(node) + last);
    // }

    // transmission_control_block_out(block, node);

    // return datalen;
}

static int32_t transmission_control_block_func_complete_in(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    switch(transmission_control_block_state_get(block)) {
        case transmission_control_state_closed:                         return transmission_control_block_complete_in_closed(block, context);
        case transmission_control_state_listen:                         return transmission_control_block_complete_in_listen(block, context);
        case transmission_control_state_synchronize_sequence_sent:      return transmission_control_block_complete_in_synchronize_sequence_sent(block, context);
        case transmission_control_state_synchronize_sequence_recv:      return transmission_control_block_complete_in_synchronize_sequence_recv(block, context);
        case transmission_control_state_establish:                      return transmission_control_block_complete_in_establish(block, context);
        case transmission_control_state_finish_wait_first:              return transmission_control_block_complete_in_finish_wait_first(block, context);
        case transmission_control_state_finish_wait_second:             return transmission_control_block_complete_in_finish_wait_second(block, context);
        case transmission_control_state_close_wait:                     return transmission_control_block_complete_in_close_wait(block, context);
        case transmission_control_state_closing:                        return transmission_control_block_complete_in_closing(block, context);
        case transmission_control_state_last_acknowledge:               return transmission_control_block_complete_in_last_acknowledge(block, context);
        case transmission_control_state_time_wait:                      return transmission_control_block_complete_in_time_wait(block, context);
        default:                                                        return transmission_control_block_complete_in_exception(block, context);
    }
}

static int32_t transmission_control_block_func_in(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    switch(transmission_control_block_state_get(block)) {
        case transmission_control_state_closed:                         return transmission_control_block_in_closed(block, context);
        case transmission_control_state_listen:                         return transmission_control_block_in_listen(block, context);
        case transmission_control_state_synchronize_sequence_sent:      return transmission_control_block_in_synchronize_sequence_sent(block, context);
        case transmission_control_state_synchronize_sequence_recv:      return transmission_control_block_in_synchronize_sequence_recv(block, context);
        case transmission_control_state_establish:                      return transmission_control_block_in_establish(block, context);
        case transmission_control_state_finish_wait_first:              return transmission_control_block_in_finish_wait_first(block, context);
        case transmission_control_state_finish_wait_second:             return transmission_control_block_in_finish_wait_second(block, context);
        case transmission_control_state_close_wait:                     return transmission_control_block_in_close_wait(block, context);
        case transmission_control_state_closing:                        return transmission_control_block_in_closing(block, context);
        case transmission_control_state_last_acknowledge:               return transmission_control_block_in_last_acknowledge(block, context);
        case transmission_control_state_time_wait:                      return transmission_control_block_in_time_wait(block, context);
        default:                                                        return transmission_control_block_in_exception(block, context);
    }



    // transmission_control_block_remote_sequence_set(block, transmission_control_protocol_context_sequence_get(context));
    // transmission_control_block_remote_acknowledge_set(block, transmission_control_protocol_context_acknowledge_get(context));

    // uint32_t acknowledge = transmission_control_block_acknowledge_get(block);
    // uint32_t sequence = transmission_control_protocol_context_sequence_get(context);

    // uint32_t difference = acknowledge - sequence;
    
    // if(protocol_packet_max < difference) {
    //     snorlaxdbg(protocol_packet_max < difference, false, "check", "");
    //     transmission_control_protocol_context_error_set(context, EINVAL);
    //     return fail;
    // }

    // snorlaxdbg(false, true, "debug", "acknowledge => %u", acknowledge);
    // snorlaxdbg(false, true, "debug", "sequence => %u", sequence);

    // if(difference == 0) {
    //     if(transmission_control_protocol_context_datalen_get(context) > 0) {
    //         int32_t n = transmission_control_block_agent_send(block->agent, transmission_control_protocol_context_data_get(context), transmission_control_protocol_context_datalen_get(context));
    //         if(n == fail) {
    //             snorlaxdbg(transmission_control_protocol_context_error_get(context) == 0, false, "critical", "");

    //             if(transmission_control_protocol_context_error_get(context) != EAGAIN) {
    //                 snorlaxdbg(transmission_control_protocol_context_error_get(context) != 0, false, "critical", "%d", transmission_control_protocol_context_error_get(context));
    //                 snorlaxdbg(true, false, "implement", "fast close");
    //                 return fail;
    //             }

    //             transmission_control_protocol_context_error_set(context, 0);
    //         } else if(n != transmission_control_protocol_context_datalen_get(context)) {
    //             transmission_control_protocol_context_error_set(context, EIO);
    //             snorlaxdbg(transmission_control_protocol_context_error_get(context) != 0, false, "critical", "%d", transmission_control_protocol_context_error_get(context));
    //             return fail;
    //         }

    //         acknowledge = acknowledge + n;

    //         snorlaxdbg(sequence + transmission_control_protocol_context_datalen_get(context) != acknowledge, false, "critical", "");

    //         transmission_control_block_acknowledge_set(block, acknowledge);
    //     }

    //     return transmission_control_protocol_context_datalen_get(context);
    // } else {
    //     snorlaxdbg(sequence + transmission_control_protocol_context_datalen_get(context) != acknowledge, false, "critical", "");

    //     return success;
    // }

    // return fail;
}

___implement static int32_t transmission_control_block_func_close(transmission_control_block_t * block) {
    return fail;
}

___implement static int32_t transmission_control_block_func_listen(transmission_control_block_t * block) {
    return fail;
}

___implement
extern transmission_control_protocol_context_t * transmission_control_block_func_context_gen_transmit_segment(transmission_control_block_t * block, transmission_control_block_buffer_out_t * data, uint8_t flags, uint8_t * buffer, uint64_t bufferlen) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(data == nil, false, "critical", "");
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(bufferlen == 0, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "refactor",  "");

    // protocol_path_node_t * node = protocol_path_begin(block->path);

    // transmission_control_protocol_context_t * context = transmission_control_protocol_context_gen((transmission_control_protocol_module_t *) node->module, nil, (transmission_control_protocol_packet_t *) buffer, 0, bufferlen);

    // transmission_control_protocol_context_block_set(context, block);
    // transmission_control_protocol_context_key_gen(context);

    // transmission_control_protocol_context_buffer_reversal_push(context, transmission_control_block_buffer_node_front(data), (context->datalen = transmission_control_block_buffer_node_length(data)));

    // snorlaxdbg(false, true, "debug", "implement transmission control protocol option");

    // transmission_control_protocol_context_buffer_reversal_reserve(context, transmission_control_protocol_packet_length_min);

    // transmission_control_protocol_context_headerlen_add(context, transmission_control_protocol_packet_length_min);

    // transmission_control_protocol_context_source_set(context, ntohs(transmission_control_protocol_to_port(protocol_path_node_destination_get(node))));
    // transmission_control_protocol_context_destination_set(context, ntohs(transmission_control_protocol_to_port(protocol_path_node_source_get(node))));

    // transmission_control_protocol_context_sequence_set(context, transmission_control_block_buffer_node_sequence_get(data));
        
    // transmission_control_protocol_context_acknowledge_set(context, transmission_control_block_acknowledge_get(block));
    // transmission_control_protocol_context_offset_set(context, transmission_control_protocol_context_headerlen_get(context) / 4);
    
    // snorlaxdbg(false, true, "debug", "transmission_control_flag_control_syn");
    // snorlaxdbg(false, true, "debug", "block ack => %u", transmission_control_block_acknowledge_get(block));
    // snorlaxdbg(false, true, "debug", "acknowledge => %u", transmission_control_protocol_context_acknowledge_get(context));
    // snorlaxdbg(false, true, "debug", "sequence => %u", transmission_control_protocol_context_sequence_get(context));
    // snorlaxdbg(false, true, "debug", "sequence => %u", transmission_control_block_buffer_node_sequence_get(data));

    // if(transmission_control_block_sequence_get(block) != transmission_control_block_buffer_node_sequence_get(data)) {
    //     flags = flags | transmission_control_flag_control_syn;
    // }

    // // if(transmission_control_block_acknowledge_get(block) != transmission_control_block_remote_sequence_get(block)) {
    // //     flags = flags | transmission_control_flag_control_ack;
    // // }

    // transmission_control_protocol_context_flags_set(context, flags);
    // transmission_control_protocol_context_window_set(context, transmission_control_block_window_local_get(block));
    // transmission_control_protocol_context_urgent_set(context, 0);

    // return context;
}

extern transmission_control_protocol_context_t * transmission_control_block_context_gen_connect_synack(transmission_control_block_t * block, uint8_t * buffer, uint64_t bufferlen) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(bufferlen == 0, false, "critical", "");
#endif // RELEASE
    snorlaxdbg(true, false, "refactor",  "");

    // protocol_path_node_t * node = protocol_path_begin(block->path);

    // transmission_control_protocol_context_t * context = transmission_control_protocol_context_gen((transmission_control_protocol_module_t *) node->module, nil, (transmission_control_protocol_packet_t *) buffer, 0, bufferlen);

    // transmission_control_protocol_context_block_set(context, block);
    // transmission_control_protocol_context_key_gen(context);

    // snorlaxdbg(false, true, "debug", "implement transmission control protocol option");

    // transmission_control_protocol_context_buffer_reversal_reserve(context, transmission_control_protocol_packet_length_min);

    // transmission_control_protocol_context_headerlen_add(context, transmission_control_protocol_packet_length_min);

    // transmission_control_protocol_context_source_set(context, ntohs(transmission_control_protocol_to_port(protocol_path_node_destination_get(node))));
    // transmission_control_protocol_context_destination_set(context, ntohs(transmission_control_protocol_to_port(protocol_path_node_source_get(node))));
    // transmission_control_protocol_context_sequence_set(context, transmission_control_block_sequence_get(block));
    // transmission_control_protocol_context_acknowledge_set(context, transmission_control_block_acknowledge_get(block));
    // transmission_control_protocol_context_offset_set(context, transmission_control_protocol_context_headerlen_get(context) / 4);
    // transmission_control_protocol_context_flags_set(context, transmission_control_flag_control_synack);
    // transmission_control_protocol_context_window_set(context, transmission_control_block_window_get(block));
    // transmission_control_protocol_context_urgent_set(context, 0);

    // return context;
}

static int32_t transmission_control_block_func_out(transmission_control_block_t * block, transmission_control_block_buffer_out_t * node) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "refactor",  "");



    // if(transmission_control_block_avail_io(block)) {
    //     uint8_t buffer[protocol_packet_max];
    //     transmission_control_protocol_module_t * module = block->module;
    //     transmission_control_block_buffer_t * out = block->buffer.out;

    //     snorlaxdbg(false, true, "debug", "node => %p", node);

    //     node = transmission_control_block_buffer_node_unprocessed_get(out, node);
    //     snorlaxdbg(false, true, "debug", "unprocessed node");
    //     node = node ? node : transmission_control_block_buffer_head(block->buffer.out);

    //     while(transmission_control_block_check_window_remote(block, node)) {
    //         uint64_t len = transmission_control_block_buffer_node_length(node);

    //         snorlaxdbg(module->max_segment_size < len, false, "warning", "");

    //         uint8_t flags = transmission_control_block_check_window_remote(block, node->next) ? 0 : transmission_control_flag_control_psh;
            
    //         transmission_control_protocol_context_t * context = transmission_control_block_func_context_gen_transmit_segment(block, node, flags, buffer, protocol_packet_max);

    //         snorlaxdbg(context == nil, false, "critical", "");

    //         transmission_control_protocol_module_debug(module, stdout, context);
    //         protocol_path_node_t * parent = protocol_path_node_next(protocol_path_begin(block->path));
    //         if(protocol_module_out(parent->module, parent, (protocol_context_t *) context) == fail) {
    //             snorlaxdbg(false, true, "critical", "fail to protocol_module_out(...) => %d", transmission_control_protocol_context_error_get(context));
    //             context = transmission_control_protocol_context_rem(context);
    //             break;
    //         }

    //         transmission_control_block_buffer_transmit_on(out, node);

    //         node = node->next;
    //     }

    //     return success;
    // }

    // return transmission_control_block_is_finishing(block) ? fail : success;
}

___implement extern int32_t transmission_control_block_func_check_window_remote(transmission_control_block_t * block, transmission_control_block_buffer_out_t * node) {
#ifndef   RELEASE
        snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "refactor",  "");



    // if(node == nil) return false;

    // snorlaxdbg(false, true, "implement", "");

    // return true;
}

// @deprecated
extern int32_t transmission_control_block_func_number_update(uint32_t * field, uint32_t no, uint32_t n) {
#ifndef   RELEASE
    snorlaxdbg(field == nil, false, "critical", "");
#endif // RELEASE



    return false;
}

extern int32_t transmission_control_block_remote_sequence_update(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE
    snorlaxdbg(true, false, "implement", "");
    // acknowledge = 3560048157
    // remote sequence = 3560048156
    // remote window = 
    // uint32_t sequence = 0;
    //     // transmission_control_block_remote_sequence_get(block) + transmission_control_protocol_context_datalen_get(context) + (transmission_control_protocol_context_flags_get(context) & (transmission_control_flag_control_fin | transmission_control_flag_control_syn) ? 1 : 0);
    // uint32_t window = transmission_control_block_remote_window_get(block);
    // uint32_t acknowledge = transmission_control_block_acknowledge_get(block);

    // uint32_t value = transmission_control_protocol_context_sequence_get(context);
    
    
    //  + transmission_control_protocol_context_datalen_get(context) + (transmission_control_protocol_context_flags_get(context) & (transmission_control_flag_control_fin | transmission_control_flag_control_syn) ? 1 : 0);

    // overflow compare 




    return false;
}