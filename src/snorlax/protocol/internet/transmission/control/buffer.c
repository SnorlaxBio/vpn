/**
 * @file        snorlax/protocol/internet/transmission/control/buffer.c
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 28, 2024
 */

#include "../control.h"

typedef transmission_control_buffer_t * (*transmission_control_buffer_func_rem_t)(transmission_control_buffer_t *);
typedef void (*transmission_control_buffer_func_push_t)(transmission_control_buffer_t *, const void *, uint64_t);
typedef void (*transmission_control_buffer_func_pop_t)(transmission_control_buffer_t *, uint64_t);
typedef void (*transmission_control_buffer_func_clear_t)(transmission_control_buffer_t *);
typedef void (*transmission_control_buffer_func_shrink_t)(transmission_control_buffer_t *);
typedef transmission_control_buffer_node_t * (*transmission_control_buffer_func_front_t)(transmission_control_buffer_t *);
typedef transmission_control_buffer_node_t * (*transmission_control_buffer_func_back_t)(transmission_control_buffer_t *, uint64_t);
typedef transmission_control_buffer_node_t * (*transmission_control_buffer_func_head_t)(transmission_control_buffer_t *);
typedef transmission_control_buffer_node_t * (*transmission_control_buffer_func_add_t)(transmission_control_buffer_t *, transmission_control_buffer_node_t *);
typedef transmission_control_buffer_node_t * (*transmission_control_buffer_func_del_t)(transmission_control_buffer_t *, transmission_control_buffer_node_t *);

static transmission_control_buffer_func_t func = {
    (transmission_control_buffer_func_rem_t) buffer_list_func_rem,
    (transmission_control_buffer_func_push_t) buffer_list_func_push,
    (transmission_control_buffer_func_pop_t) buffer_list_func_pop,
    (transmission_control_buffer_func_clear_t) buffer_list_func_clear,
    (transmission_control_buffer_func_shrink_t) buffer_list_func_shrink,
    (transmission_control_buffer_func_front_t) buffer_list_func_front,
    (transmission_control_buffer_func_back_t) buffer_list_func_back,
    (transmission_control_buffer_func_head_t) buffer_list_func_head,
    (transmission_control_buffer_func_add_t) buffer_list_func_add,
    (transmission_control_buffer_func_del_t) buffer_list_func_del
};

extern transmission_control_buffer_t * transmission_control_buffer_gen(transmission_control_buffer_node_factory_t nodegen, transmission_control_protocol_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(nodegen == nil, false, "critical", "");
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE
    transmission_control_buffer_t * buffer = (transmission_control_buffer_t *) calloc(1, sizeof(transmission_control_buffer_t));

    buffer->func    = address_of(func);
    buffer->page    = transmission_control_protocol_module_maximum_segment_get(module);
    buffer->nodegen = nodegen;
    buffer->window  = transmission_control_protocol_module_window_get(module);

    return buffer;
}
