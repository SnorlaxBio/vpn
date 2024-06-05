/**
 * @file        snorlax/event.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 3, 2024
 */

#ifndef   __SNORLAX__EVENT__H__
#define   __SNORLAX__EVENT__H__

#include <snorlax.h>

struct snorlax_event;
struct snorlax_event_queue;
struct snorlax_event_queue_func;

typedef struct snorlax_event snorlax_event_t;
typedef struct snorlax_event_queue snorlax_event_queue_t;
typedef struct snorlax_event_queue_func snorlax_event_queue_func_t;

// REDEFINE DOUBLE LINKED LIST METHOD TYPE
typedef snorlax_event_queue_t * (*snorlax_event_queue_gen_t)(void);
typedef snorlax_event_queue_t * (*snorlax_event_queue_rem_t)(snorlax_event_queue_t *, bucket_func_get_t);
typedef void (*snorlax_event_queue_clr_t)(snorlax_event_queue_t *, bucket_func_get_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_add_t)(snorlax_event_queue_t *, bucket_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_del_t)(snorlax_event_queue_t *, bucket_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_begin_t)(snorlax_event_queue_t *);
typedef snorlax_event_queue_t * (*snorlax_event_queue_end_t)(snorlax_event_queue_t *);
typedef snorlax_event_queue_t * (*snorlax_event_queue_find_t)(snorlax_event_queue_t *, bucket_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_insert_node_prev_t)(snorlax_event_queue_t *, snorlax_event_queue_t *, bucket_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_insert_node_next_t)(snorlax_event_queue_t *, snorlax_event_queue_t *, bucket_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_push_front_t)(snorlax_event_queue_t *, bucket_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_push_back_t)(snorlax_event_queue_t *, bucket_t);
typedef snorlax_event_queue_t * (*snorlax_event_queue_delete_node_t)(snorlax_event_queue_t *, snorlax_event_queue_t *, bucket_func_get_t);

struct snorlax_event {
    snorlax_event_queue_t * queue;
    bucket_t bucket;

    snorlax_event_t * prev;
    snorlax_event_t * next;
};

struct snorlax_event_queue {
    // INHERITED COLLECTION
    snorlax_event_queue_func_t * func;
    uint64_t size;
    // SPECIFIED MEMBER OF DOUBLE LINKED LIST
    snorlax_event_t * head;
    snorlax_event_t * tail;
};

struct snorlax_list_linked_double_func {
    // INHERIED METHOD OF COLLECTION
    snorlax_event_queue_t * (*gen)(void);
    snorlax_event_queue_t * (*rem)(snorlax_event_queue_t *, bucket_func_get_t);
    void (*clr)(snorlax_event_queue_t *, bucket_func_get_t);
    snorlax_event_queue_t * (*add)(snorlax_event_queue_t *, bucket_t);
    snorlax_event_queue_t * (*del)(snorlax_event_queue_t *, bucket_t);
    snorlax_event_queue_t * (*begin)(snorlax_event_queue_t *);
    snorlax_event_queue_t * (*end)(snorlax_event_queue_t *);
    snorlax_event_queue_t * (*find)(snorlax_event_queue_t *, bucket_t);
    // INHERIED METHOD OF DOUBLE LINKED LIST
    snorlax_event_queue_t * (*insert_node_prev)(snorlax_event_queue_t *, snorlax_event_queue_t *, bucket_t);
    snorlax_event_queue_t * (*insert_node_next)(snorlax_event_queue_t *, snorlax_event_queue_t *, bucket_t);
    snorlax_event_queue_t * (*push_front)(snorlax_event_queue_t *, bucket_t);
    snorlax_event_queue_t * (*push_back)(snorlax_event_queue_t *, bucket_t);
    snorlax_event_queue_t * (*delete_node)(snorlax_event_queue_t *, snorlax_event_queue_t *, bucket_func_get_t);
};

#endif // __SNORLAX__EVENT__H__
