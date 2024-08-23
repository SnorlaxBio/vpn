#include <string.h>

#include "../../../control.h"

typedef transmission_control_block_buffer_node_t * (*transmission_control_block_buffer_node_rem_t)(transmission_control_block_buffer_node_t *);
typedef void * (*transmission_control_block_buffer_node_front_t)(transmission_control_block_buffer_node_t *);
typedef void * (*transmission_control_block_buffer_node_back_t)(transmission_control_block_buffer_node_t *);
typedef int32_t (*transmission_control_block_buffer_node_shrink_t)(transmission_control_block_buffer_node_t *);
typedef uint64_t (*transmission_control_block_buffer_node_length_t)(transmission_control_block_buffer_node_t *);
typedef uint64_t (*transmission_control_block_buffer_node_remain_t)(transmission_control_block_buffer_node_t *);
typedef uint64_t (*transmission_control_block_buffer_node_position_get_t)(transmission_control_block_buffer_node_t *);
typedef void (*transmission_control_block_buffer_node_position_set_t)(transmission_control_block_buffer_node_t *, uint64_t);
typedef uint64_t (*transmission_control_block_buffer_node_size_get_t)(transmission_control_block_buffer_node_t *);
typedef void (*transmission_control_block_buffer_node_size_set_t)(transmission_control_block_buffer_node_t *, uint64_t);
typedef uint64_t (*transmission_control_block_buffer_node_capacity_get_t)(transmission_control_block_buffer_node_t *);
typedef void (*transmission_control_block_buffer_node_capacity_set_t)(transmission_control_block_buffer_node_t *, uint64_t);
typedef void (*transmission_control_block_buffer_node_clear_t)(transmission_control_block_buffer_node_t *);

static transmission_control_block_buffer_node_func_t func = {
    (transmission_control_block_buffer_node_rem_t) buffer_list_node_func_rem,
    (transmission_control_block_buffer_node_front_t) buffer_list_node_func_front,
    (transmission_control_block_buffer_node_back_t) buffer_list_node_func_back,
    (transmission_control_block_buffer_node_shrink_t) buffer_list_node_func_shrink,
    (transmission_control_block_buffer_node_length_t) buffer_list_node_func_length,
    (transmission_control_block_buffer_node_remain_t) buffer_list_node_func_remain,
    (transmission_control_block_buffer_node_position_get_t) buffer_list_node_func_position_get,
    (transmission_control_block_buffer_node_position_set_t) buffer_list_node_func_position_set,
    (transmission_control_block_buffer_node_size_get_t) buffer_list_node_func_size_get,
    (transmission_control_block_buffer_node_size_set_t) buffer_list_node_func_size_set,
    (transmission_control_block_buffer_node_capacity_get_t) buffer_list_node_func_capacity_get,
    (transmission_control_block_buffer_node_capacity_set_t) buffer_list_node_func_capacity_set,
    (transmission_control_block_buffer_node_clear_t) buffer_list_node_func_clear
};

extern transmission_control_block_buffer_node_t * transmission_control_block_buffer_node_gen(transmission_control_block_buffer_t * buffer, const void * data, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_buffer_node_t * node = (transmission_control_block_buffer_node_t *) calloc(1, sizeof(transmission_control_block_buffer_node_t));

    node->func = address_of(func);

    transmission_control_block_buffer_add(buffer, node);

    if(data) {
        uint64_t page = buffer->page ? buffer->page : 1;
        node->capacity = ((n / page) + (n % page == 0 ? 0 : 1)) * page;
        snorlaxdbg(false, true, "debug", "capacity => %lu", node->capacity);
        node->mem = memory_gen(nil, node->capacity);

        memcpy(node->mem, data, n);
        node->size = n;
    } else if(n > 0) {
        uint64_t page = buffer->page ? buffer->page : 1;
        node->capacity = ((n / page) + (n % page == 0 ? 0 : 1)) * page;
        snorlaxdbg(false, true, "debug", "capacity => %lu", node->capacity);

        node->mem = memory_gen(nil, node->capacity); 
    }

    nanosecond_get(address_of(node->time));

    return node;
}
