#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../control.h"

static transmission_control_block_t * transmission_control_block_func_rem(transmission_control_block_t * block);
static int32_t transmission_control_block_func_open(transmission_control_block_t * block);
static int32_t transmission_control_block_func_send(transmission_control_block_t * block);
static int32_t transmission_control_block_func_recv(transmission_control_block_t * block);
static int32_t transmission_control_block_func_close(transmission_control_block_t * block);

static transmission_control_block_func_t func = {
    transmission_control_block_func_rem,
    transmission_control_block_func_open,
    transmission_control_block_func_send,
    transmission_control_block_func_recv,
    transmission_control_block_func_close
};

extern transmission_control_block_t * transmission_control_block_gen(hashtable_node_key_t * key) {
#ifndef   RELEASE
    snorlaxdbg(key == nil, false, "critical", "");
    snorlaxdbg(key->value == nil, false, "critical", "");
    snorlaxdbg(key->length == 0, false, "critical", "");
#endif // RELEASE

    transmission_control_block_t * block = (transmission_control_block_t *) calloc(1, sizeof(transmission_control_block_t));

    block->func = address_of(func);

    block->key.value = malloc(key->length);
    block->window = transmission_control_window_size_init;

    memcpy(block->key.value, key->value, key->length);

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

static int32_t transmission_control_block_func_send(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

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

    snorlaxdbg(false, true, "debug", "implement transmission control protocol option");

    transmission_control_protocol_context_buffer_reserve(context, transmission_control_protocol_packet_length_min);

    transmission_control_protocol_context_source_set(context, transmission_control_protocol_to_port(protocol_path_node_destination_get(node)));
    transmission_control_protocol_context_destination_set(context, transmission_control_protocol_to_port(protocol_path_node_source_get(node)));
    transmission_control_protocol_context_sequence_set(context, transmission_control_block_acknowledge_get(block));
    transmission_control_protocol_context_acknowledge_set(context, transmission_control_block_sequence_get(block));
    transmission_control_protocol_context_offset_set(context, 0);
    transmission_control_protocol_context_flags_set(context, transmission_control_flag_control_synack);
    transmission_control_protocol_context_window_set(context, transmission_control_block_window_get(block));
    transmission_control_protocol_context_urgent_set(context, 0);

    snorlaxdbg(false, true, "debug", "checksum ...");

    return context;
}
