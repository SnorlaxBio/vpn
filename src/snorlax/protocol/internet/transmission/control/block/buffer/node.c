#include <string.h>
#include <stdlib.h>

#include "../../../control.h"

typedef transmission_control_block_buffer_node_t * (*transmission_control_block_buffer_node_func_rem_t)(transmission_control_block_buffer_node_t *);
typedef void * (*transmission_control_block_buffer_node_func_front_t)(transmission_control_block_buffer_node_t *);
typedef void * (*transmission_control_block_buffer_node_func_back_t)(transmission_control_block_buffer_node_t *);
typedef int32_t (*transmission_control_block_buffer_node_func_shrink_t)(transmission_control_block_buffer_node_t *);
typedef uint64_t (*transmission_control_block_buffer_node_func_length_t)(transmission_control_block_buffer_node_t *);
typedef uint64_t (*transmission_control_block_buffer_node_func_remain_t)(transmission_control_block_buffer_node_t *);
typedef uint64_t (*transmission_control_block_buffer_node_func_position_get_t)(transmission_control_block_buffer_node_t *);
typedef void (*transmission_control_block_buffer_node_func_position_set_t)(transmission_control_block_buffer_node_t *, uint64_t);
typedef uint64_t (*transmission_control_block_buffer_node_func_size_get_t)(transmission_control_block_buffer_node_t *);
typedef void (*transmission_control_block_buffer_node_func_size_set_t)(transmission_control_block_buffer_node_t *, uint64_t);
typedef uint64_t (*transmission_control_block_buffer_node_func_capacity_get_t)(transmission_control_block_buffer_node_t *);
typedef void (*transmission_control_block_buffer_node_func_capacity_set_t)(transmission_control_block_buffer_node_t *, uint64_t);
typedef void (*transmission_control_block_buffer_node_func_clear_t)(transmission_control_block_buffer_node_t *);

static transmission_control_block_buffer_node_func_t func = {
    (transmission_control_block_buffer_node_func_rem_t) buffer_list_node_func_rem,
    (transmission_control_block_buffer_node_func_front_t) buffer_list_node_func_front,
    (transmission_control_block_buffer_node_func_back_t) buffer_list_node_func_back,
    (transmission_control_block_buffer_node_func_shrink_t) buffer_list_node_func_shrink,
    (transmission_control_block_buffer_node_func_length_t) buffer_list_node_func_length,
    (transmission_control_block_buffer_node_func_remain_t) buffer_list_node_func_remain,
    (transmission_control_block_buffer_node_func_position_get_t) buffer_list_node_func_position_get,
    (transmission_control_block_buffer_node_func_position_set_t) buffer_list_node_func_position_set,
    (transmission_control_block_buffer_node_func_size_get_t) buffer_list_node_func_size_get,
    (transmission_control_block_buffer_node_func_size_set_t) buffer_list_node_func_size_set,
    (transmission_control_block_buffer_node_func_capacity_get_t) buffer_list_node_func_capacity_get,
    (transmission_control_block_buffer_node_func_capacity_set_t) buffer_list_node_func_capacity_set,
    (transmission_control_block_buffer_node_func_clear_t) buffer_list_node_func_clear
};

extern transmission_control_block_buffer_node_t * transmission_control_block_buffer_node(transmission_control_block_buffer_t * collection, const void * data, uint64_t n) {
    transmission_control_block_buffer_node_t * node = (transmission_control_block_buffer_node_t *) calloc(1, sizeof(transmission_control_block_buffer_node_t));

    node->func = address_of(func);

    if(data) {
        if(n > 0) {
            uint64_t page = collection->page ? collection->page : 1;
            node->capacity = ((n / page) + (n % page == 0 ? 0 : 1)) * page;
            node->mem = memory_gen(nil, node->capacity);
            memcpy(node->mem, data, n);
            node->size = n;
        }
    } else if(n > 0) {
        uint64_t page = collection->page ? collection->page : 1;
        node->capacity = ((n / page) + (n % page == 0 ? 0 : 1)) * page;
        node->mem = memory_gen(nil, node->capacity);
    }

    nanosecond_get(address_of(node->time));

    snorlaxdbg(true, false, "implement", "");

    transmission_control_block_buffer_add(collection, node);

    return node;
}