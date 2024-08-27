/**
 * @file        snorlax/protocol/internet/transmission/control/block/segment.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 28, 2024
 */

#include "../../control.h"

static transmission_control_block_segment_func_t func = {

};

extern transmission_control_block_segment_t * transmission_control_block_segment_gen(transmission_control_block_segment_node_factory_t nodegen, uint64_t mss) {
    transmission_control_block_segment_t * segment = (transmission_control_block_segment_t *) calloc(1, sizeof(transmission_control_block_segment_t));

    segment->func   = address_of(func);
    segment->page   = mss;

    return segment;
}