/**
 * @file        snorlax/list/double-linked.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#ifndef   __SNORLAX__LIST_DOUBLE_LINKED__H__
#define   __SNORLAX__LIST_DOUBLE_LINKED__H__

#include <stdint.h>
#include <stdio.h>

#include <snorlax/bucket.h>

struct snorlax_list_double_linked_item;

typedef struct snorlax_list_double_linked_item snorlax_list_double_linked_item_t;

struct snorlax_list_double_linked {
    int type;
    snorlax_list_double_linked_item_t * head;
    snorlax_list_double_linked_item_t * tail;
    uint64_t size;
};

struct snorlax_list_double_linked_item {
    snorlax_list_double_linked_item_t * prev;
    snorlax_list_double_linked_item_t * next;
    snorlax_bucket_t bucket;
};

typedef struct snorlax_list_double_linked snorlax_list_double_linked_t;

extern snorlax_list_double_linked_t * snorlax_list_double_linked_gen(void);
extern void snorlax_list_double_linked_prev_add(snorlax_list_double_linked_item_t * base, snorlax_list_double_linked_item_t * node);
extern void snorlax_list_double_linked_next_add(snorlax_list_double_linked_item_t * base, snorlax_list_double_linked_item_t * node);

#endif // __SNORLAX__LIST_DOUBLE_LINKED__H__
