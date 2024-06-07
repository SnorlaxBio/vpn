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

static event_queue_t queue = { 0, nil, nil };

extern event_queue_t * event_queue_get(void) {
    return &queue;
}

extern void event_queue_push(event_t * e) {
    if(queue.tail) {
        queue.tail->next = e;
        e->prev = queue.tail;
    } else {
        queue.head = e;
    }
    queue.tail = e;
    queue.size = queue.size + 1;
}

extern event_t * event_queue_pop(void) {
    event_t * e = queue.head;

    if(e) {
        queue.head = queue.head->next;
        queue.size = queue.size - 1;
    }

    if(queue.head == nil) {
        queue.tail = nil;
    }

    return e;
}