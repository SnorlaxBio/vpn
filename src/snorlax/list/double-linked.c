/**
 * @file        snorlax/list/double-linked.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#include "double-linked.h"

#include "../list.h"

extern snorlax_list_double_linked_t * snorlax_list_double_linked_gen(void) {
    snorlax_list_double_linked_t * o = (snorlax_list_double_linked_t *) calloc(1, sizeof(snorlax_list_double_linked_t));

    o->type = snorlax_list_double_linked;

    return o;
}

extern void snorlax_list_double_linked_prev_add(snorlax_list_double_linked_item_t * base, snorlax_list_double_linked_item_t * node) {
        
}

extern void snorlax_list_double_linked_next_add(snorlax_list_double_linked_item_t * base, snorlax_list_double_linked_item_t * node) {

}

