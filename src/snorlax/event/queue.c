/**
 * @file        snorlax/event/queue.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 7, 2024
 */

#include "queue.h"

#include "../event.h"

extern event_queue_t * event_queue_gen(void) {
    return (event_queue_t *) calloc(1, sizeof(event_queue_t));
}

extern event_queue_t * event_queue_rem(event_queue_t * queue, event_func_t func) {
    event_t * e = queue->head;

    while(e) {
        queue->head = queue->head->next;
        if(func) func(e);
        free(e);
        e = queue->head;
    }

    free(queue);

    return nil;
}

extern void event_queue_push(event_queue_t * queue, event_t * e) {
    if(queue->tail) {
        queue->tail->next = e;
        e->prev = queue->tail;
    } else {
        queue->head = e;
    }
    queue->tail = e;
    queue->size = queue->size + 1;
}

extern event_t * event_queue_pop(event_queue_t * queue) {
    event_t * e = queue->head;

    if(e) {
        queue->head = queue->head->next;
        queue->size = queue->size - 1;
    }

    if(queue->head == nil) {
        queue->tail = nil;
    }

    return e;
}

extern void event_queue_clear(event_queue_t * queue, event_func_t func) {
    event_t * e = queue->head;

    while(e) {
        queue->head = queue->head->next;
        if(func) func(e);
        free(e);
        e = queue->head;
    }

    queue->head = nil;
    queue->tail = nil;
    queue->size = 0lu;
}
