// #include <string.h>
// #include <stdlib.h>

// #include "../../../control.h"

// typedef transmission_control_block_buffer_out_t * (*transmission_control_block_buffer_out_func_rem_t)(transmission_control_block_buffer_out_t *);
// typedef void (*transmission_control_block_buffer_out_func_push_t)(transmission_control_block_buffer_out_t *, const void *, uint64_t);
// typedef void (*transmission_control_block_buffer_out_func_pop_t)(transmission_control_block_buffer_out_t *, uint64_t);
// typedef void (*transmission_control_block_buffer_out_func_clear_t)(transmission_control_block_buffer_out_t *);
// typedef void (*transmission_control_block_buffer_out_func_shrink_t)(transmission_control_block_buffer_out_t *);
// typedef transmission_control_block_buffer_out_node_t * (*transmission_control_block_buffer_out_func_front_t)(transmission_control_block_buffer_out_t *);
// typedef transmission_control_block_buffer_out_node_t * (*transmission_control_block_buffer_out_func_back_t)(transmission_control_block_buffer_out_t *, uint64_t);
// typedef transmission_control_block_buffer_out_node_t * (*transmission_control_block_buffer_out_func_head_t)(transmission_control_block_buffer_out_t *);
// typedef transmission_control_block_buffer_out_node_t * (*transmission_control_block_buffer_out_func_add_t)(transmission_control_block_buffer_out_t *, transmission_control_block_buffer_out_node_t *);
// typedef transmission_control_block_buffer_out_node_t * (*transmission_control_block_buffer_out_func_del_t)(transmission_control_block_buffer_out_t *, transmission_control_block_buffer_out_node_t *);

// static transmission_control_block_buffer_out_func_t func = {
//     (transmission_control_block_buffer_out_func_rem_t) buffer_list_func_rem,
//     (transmission_control_block_buffer_out_func_push_t) buffer_list_func_push,
//     (transmission_control_block_buffer_out_func_pop_t) buffer_list_func_pop,
//     (transmission_control_block_buffer_out_func_clear_t) buffer_list_func_clear,
//     (transmission_control_block_buffer_out_func_shrink_t) buffer_list_func_shrink,
//     (transmission_control_block_buffer_out_func_front_t) buffer_list_func_front,
//     (transmission_control_block_buffer_out_func_back_t) buffer_list_func_back,
//     (transmission_control_block_buffer_out_func_head_t) buffer_list_func_head,
//     (transmission_control_block_buffer_out_func_add_t) buffer_list_func_add,
//     (transmission_control_block_buffer_out_func_del_t) buffer_list_func_del
// };

// extern transmission_control_block_buffer_out_t * transmission_control_block_buffer_out_gen(transmission_control_block_buffer_out_node_factory_t nodegen, uint64_t page) {

//     transmission_control_block_buffer_out_t * buffer = (transmission_control_block_buffer_out_t *) calloc(1, sizeof(transmission_control_block_buffer_out_t));

//     buffer->func = address_of(func);
//     buffer->nodegen = nodegen ? nodegen : transmission_control_block_buffer_out_node_gen;
//     buffer->page = page;

//     return buffer;
// }

// extern void transmission_control_block_buffer_out_func_transmit_on(transmission_control_block_buffer_out_t * buffer, transmission_control_block_buffer_out_node_t * node) {
// #ifndef   RELEASE
//     snorlaxdbg(buffer == nil, false, "critical", "");
//     snorlaxdbg(node == nil, false, "critical", "");
// #endif // RELEASE

//     node->transmit.count = node->transmit.count + 1;
//     nanosecond_get(address_of(node->transmit.time));
// }
