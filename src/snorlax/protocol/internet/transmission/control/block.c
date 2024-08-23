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
static int32_t transmission_control_block_func_in(transmission_control_block_t * block, transmission_control_protocol_context_t * context);
static int32_t transmission_control_block_func_out(transmission_control_block_t * block, transmission_control_block_node_t * node);

static transmission_control_block_func_t func = {
    transmission_control_block_func_rem,
    transmission_control_block_func_open,
    transmission_control_block_func_send,
    transmission_control_block_func_recv,
    transmission_control_block_func_close,
    transmission_control_block_func_in,
    transmission_control_block_func_out
};

extern transmission_control_block_t * transmission_control_block_gen(hashtable_node_key_t * key, transmission_control_protocol_module_t * module, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(key == nil, false, "critical", "");
    snorlaxdbg(key->value == nil, false, "critical", "");
    snorlaxdbg(key->length == 0, false, "critical", "");
#endif // RELEASE

    transmission_control_block_t * block = (transmission_control_block_t *) calloc(1, sizeof(transmission_control_block_t));

    block->func = address_of(func);

    block->key.value = malloc(key->length);
    block->key.length = key->length;
    block->window = transmission_control_window_size_init;
    block->module = module;
    block->buffer.out = buffer_list_gen(buffer_list_node_gen, module->max_segment_size);

    memcpy(block->key.value, key->value, key->length);

    if(context) {
        snorlaxdbg(context->block != nil, false, "critical", "");
        snorlaxdbg(context->parent == nil, false, "critical", "");

        block->path = protocol_path_gen((protocol_context_t *) context, 128);

        transmission_control_block_state_set(block, transmission_control_state_synchronize_sequence_recv);
        transmission_control_block_acknowledge_set(block, transmission_control_protocol_context_sequence_get(context) + 1);
        transmission_control_block_sequence_set(block, transmission_control_protocol_module_seqeuence_gen(context->module, context->parent, context));
        transmission_control_block_version_set(block, internet_protocol_context_version_get(context->parent));

        snorlaxdbg(false, true, "implement", "default window when transmission control block gen and remove below");
        transmission_control_block_window_set(block, transmission_control_protocol_context_window_get(context));

        protocol_path_debug(block->path, stdout);
    }

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

    if(transmission_control_block_avail_io(block) == false) {
        snorlaxdbg(transmission_control_block_avail_io(block) == false, false, "warning", "");
        return fail;
    }

    buffer_list_t * out = block->buffer.out;

    transmission_control_block_node_t * node = transmission_control_block_buffer_back(out);
    uint64_t remain = transmission_control_block_node_remain(node);

    transmission_control_block_node_t * front = node;

    // TRANSMISSION 할 노드를 찾는다.
    for(front = transmission_control_block_buffer_back(out); front != nil; front = transmission_control_block_node_next(front)) {

    }

    if(remain > 0) {
        if(datalen <= remain) {
            memcpy(buffer_list_node_front(node), data, datalen);
            buffer_list_node_size_set(node, buffer_list_node_size_get(node) + datalen);

            transmission_control_block_out(block, node);

            return datalen;
        }
        memcpy(buffer_list_node_front(node), data, remain);
        buffer_list_node_size_set(node, buffer_list_node_size_get(node) + remain);
    }

    uint64_t len = datalen - remain;
    uint16_t mss = block->module->max_segment_size;
    uint64_t n = len / mss;
    uint64_t last = len % mss;

    data = data + remain;

    for(uint64_t i = 0; i < n; i++) {
        buffer_list_node_t * node = buffer_list_back(out, mss);
        memcpy(buffer_list_node_front(node), address_of(data[i * mss]), mss);
        buffer_list_node_size_set(node, buffer_list_node_size_get(node) + mss);
    }

    if(last) {
        buffer_list_node_t * node = buffer_list_back(out, mss);
        memcpy(buffer_list_node_front(node), address_of(data[n * mss]), last);
        buffer_list_node_size_set(node, buffer_list_node_size_get(node) + last);
    }
    // 새롭게 들어온 녀석들이 있다면,... 바로 보낸다.
    transmission_control_block_out(block, front);

    return datalen;
}

static int32_t transmission_control_block_func_in(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    uint32_t acknowledge = transmission_control_block_acknowledge_get(block);
    uint32_t sequence = transmission_control_protocol_context_sequence_get(context);

    uint32_t difference = acknowledge - sequence;
    
    if(protocol_packet_max < difference) {
        snorlaxdbg(protocol_packet_max < difference, false, "check", "");
        transmission_control_protocol_context_error_set(context, EINVAL);
        return fail;
    }

    snorlaxdbg(false, true, "debug", "acknowledge => %u", acknowledge);
    snorlaxdbg(false, true, "debug", "sequence => %u", sequence);

    if(difference == 0) {
        if(transmission_control_protocol_context_datalen_get(context) > 0) {
            int32_t n = transmission_control_block_agent_send(block->agent, transmission_control_protocol_context_data_get(context), transmission_control_protocol_context_datalen_get(context));
            if(n == fail) {
                snorlaxdbg(transmission_control_protocol_context_error_get(context) == 0, false, "critical", "");

                if(transmission_control_protocol_context_error_get(context) != EAGAIN) {
                    snorlaxdbg(transmission_control_protocol_context_error_get(context) != 0, false, "critical", "%d", transmission_control_protocol_context_error_get(context));
                    snorlaxdbg(true, false, "implement", "fast close");
                    return fail;
                }

                transmission_control_protocol_context_error_set(context, 0);
            } else if(n != transmission_control_protocol_context_datalen_get(context)) {
                transmission_control_protocol_context_error_set(context, EIO);
                snorlaxdbg(transmission_control_protocol_context_error_get(context) != 0, false, "critical", "%d", transmission_control_protocol_context_error_get(context));
                return fail;
            }

            acknowledge = acknowledge + n;

            snorlaxdbg(sequence + transmission_control_protocol_context_datalen_get(context) != acknowledge, false, "critical", "");

            transmission_control_block_acknowledge_set(block, acknowledge);
        }

        return transmission_control_protocol_context_datalen_get(context);
    } else {
        snorlaxdbg(sequence + transmission_control_protocol_context_datalen_get(context) != acknowledge, false, "critical", "");

        return success;
    }

    return fail;
}

static int32_t transmission_control_block_func_close(transmission_control_block_t * block) {

}

extern transmission_control_protocol_context_t * transmission_control_block_context_gen_connect_synack(transmission_control_block_t * block, uint8_t * buffer, uint64_t bufferlen) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(bufferlen == 0, false, "critical", "");
#endif // RELEASE

    protocol_path_node_t * node = protocol_path_begin(block->path);

    transmission_control_protocol_context_t * context = transmission_control_protocol_context_gen((transmission_control_protocol_module_t *) node->module, nil, (transmission_control_protocol_packet_t *) buffer, 0, bufferlen);

    transmission_control_protocol_context_block_set(context, block);
    transmission_control_protocol_context_key_gen(context);

    snorlaxdbg(false, true, "debug", "implement transmission control protocol option");

    transmission_control_protocol_context_buffer_reserve(context, transmission_control_protocol_packet_length_min);

    transmission_control_protocol_context_headerlen_add(context, transmission_control_protocol_packet_length_min);

    transmission_control_protocol_context_source_set(context, ntohs(transmission_control_protocol_to_port(protocol_path_node_destination_get(node))));
    transmission_control_protocol_context_destination_set(context, ntohs(transmission_control_protocol_to_port(protocol_path_node_source_get(node))));
    transmission_control_protocol_context_sequence_set(context, transmission_control_block_sequence_get(block));
    transmission_control_protocol_context_acknowledge_set(context, transmission_control_block_acknowledge_get(block));
    transmission_control_protocol_context_offset_set(context, transmission_control_protocol_context_headerlen_get(context) / 4);
    transmission_control_protocol_context_flags_set(context, transmission_control_flag_control_synack);
    transmission_control_protocol_context_window_set(context, transmission_control_block_window_get(block));
    transmission_control_protocol_context_urgent_set(context, 0);

    return context;
}

static int32_t transmission_control_block_func_out(transmission_control_block_t * block, transmission_control_block_node_t * node) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

#if       0
    // 새롭게 들어온 녀석에 대해서 바로 보내는 것이 맞을까?
    // 나중에 변경하도록 하자.
    while(node->prev && transmission_control_block_node_transmit_count_get(node->prev) == 0) {
        node = node->prev;
    }

    // 커널 소스를 봐야겠다.
    // https://datatracker.ietf.org/doc/html/rfc9293#section-3.9.1 읽고 구현하자.
#endif // 0

    snorlaxdbg(true, false, "implement", "");

    if(transmission_control_block_avail_io(block)) {
    }

    /**
     * If the connection has not been opened, the send is considered an error.
     */
    if(transmission_control_block_finishing(block)) {
        return fail;
    }

    return success;

    // return transmission_control_block_finishing(block) ? fail : success;

    // }

    // // for(transmission_control_block_node_t * node = transmission_control_block_)

    // // 졸립다. 조금 후에 짜자...

    // snorlaxdbg(true, false, "implement", "");

    // return fail;
}
