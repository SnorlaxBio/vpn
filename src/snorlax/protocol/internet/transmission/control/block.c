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
static int32_t transmission_control_block_func_out(transmission_control_block_t * block);

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

static int32_t transmission_control_block_func_open(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

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

    if(transmission_control_block_avail_io(block) == false) {
        snorlaxdbg(transmission_control_block_avail_io(block) == false, false, "warning", "");
        return fail;
    }

    uint16_t mss = block->module->max_segment_size;
    uint64_t n = datalen / mss;
    uint64_t last = datalen % mss;
    buffer_list_t * out = block->buffer.out;

    for(uint64_t i = 0; i < n; i++) {
        buffer_list_node_t * node = buffer_list_back(out, mss);
        memcpy(buffer_list_node_front(node), address_of(data[i * mss]), mss);
    }

    if(last) {
        buffer_list_node_t * node = buffer_list_back(out, mss);
        memcpy(buffer_list_node_front(node), address_of(data[n * mss]), last);
    }

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

static int32_t transmission_control_block_func_out(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}
