/**
 * @file        snorlax/list/linked/double.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 3, 2024
 */

#ifndef   __SNORLAX__LIST_LINKED_DOUBLE__H__
#define   __SNORLAX__LIST_LINKED_DOUBLE__H__

#include <stdint.h>
#include <stdio.h>

#include <snorlax.h>
#include <snorlax/bucket.h>

struct snorlax_list_linked_double;
struct snorlax_list_linked_double_node;
struct snorlax_list_linked_double_func;

typedef struct snorlax_list_linked_double snorlax_list_linked_double_t;
typedef struct snorlax_list_linked_double_node snorlax_list_linked_double_node_t;
typedef struct snorlax_list_linked_double_func snorlax_list_linked_double_func_t;

struct snorlax_list_linked_double {
    // INHERITED COLLECTION
    snorlax_list_linked_double_func_t * func;
    uint64_t size;
    // SPECIFIED MEMBER OF DOUBLE LINKED LIST
    snorlax_list_linked_double_node_t * head;
    snorlax_list_linked_double_node_t * tail;
};

struct snorlax_list_linked_double_node {
    // INHERITED COLLECTION NODE
    snorlax_list_linked_double_t * collection;
    snorlax_bucket_t bucket;
    // SPECIFIED MEMBER OF DOUBLE LINKED LIST ITEM
    snorlax_list_linked_double_node_t * prev;
    snorlax_list_linked_double_node_t * next;
};

/**
 * 노출 시켜야 할 필요가 있다.
 * 
 * PRIVATE & PUBLIC
 */
struct snorlax_list_linked_double_func {
    // INHERIED METHOD OF COLLECTION
    snorlax_list_linked_double_t * (*gen)(void);
    snorlax_list_linked_double_t * (*rem)(snorlax_list_linked_double_t *, snorlax_bucket_func_get);
    void (*clr)(snorlax_list_linked_double_t *, snorlax_bucket_func_get);
    snorlax_list_linked_double_node_t * (*add)(snorlax_list_linked_double_t *, snorlax_bucket_t);
    snorlax_list_linked_double_node_t * (*del)(snorlax_list_linked_double_t *, snorlax_bucket_t);
    snorlax_list_linked_double_node_t * (*begin)(snorlax_list_linked_double_t *);
    snorlax_list_linked_double_node_t * (*end)(snorlax_list_linked_double_t *);
    snorlax_list_linked_double_node_t * (*find)(snorlax_list_linked_double_t *, snorlax_bucket_t);
    // SPECIFIED METHOD OF DOUBLE LINKED LIST
    snorlax_list_linked_double_node_t * (*insert_node_prev)(snorlax_list_linked_double_t *, snorlax_list_linked_double_node_t *, snorlax_bucket_t);
    snorlax_list_linked_double_node_t * (*insert_node_next)(snorlax_list_linked_double_t *, snorlax_list_linked_double_node_t *, snorlax_bucket_t);
    snorlax_list_linked_double_node_t * (*push_front)(snorlax_list_linked_double_t *, snorlax_bucket_t);
    snorlax_list_linked_double_node_t * (*push_back)(snorlax_list_linked_double_t *, snorlax_bucket_t);
    snorlax_list_linked_double_node_t * (*delete_node)(snorlax_list_linked_double_t *, snorlax_list_linked_double_node_t *, snorlax_bucket_func_get);
};

#endif // __SNORLAX__LIST_LINKED_DOUBLE__H__
