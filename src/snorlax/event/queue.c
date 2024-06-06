/**
 * @file        snorlax/event/queue.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 5, 2024
 */

#include "queue.h"

static snorlax_event_func_t func = {
    snorlax_event_queue_gen,
    snorlax_event_queue_rem,
    snorlax_event_queue_clear,
    snorlax_event_queue_add,
    snorlax_event_queue_del,
    snorlax_event_queue_begin,
    snorlax_event_queue_end,
    snorlax_event_queue_find
};

extern snorlax_event_queue_t * snorlax_event_queue_gen(void) {
    snorlax_event_queue_t * o = (snorlax_event_queue_t *) calloc(1, sizeof(snorlax_event_queue_t));

    o->func = &func;

    return o;
}

extern snorlax_event_queue_t * snorlax_event_queue_rem(snorlax_event_queue_t * queue, snorlax_event_func_get func) {
    snorlax_event_t * node = queue->head;

    while(node) {
        queue->head = queue->head->next;

        if(func) {
            func(node);
        }

        free(node);

        node = queue->head;
    }

    free(queue);

    return nil;
}

extern void snorlax_event_queue_clear(snorlax_event_queue_t * queue, snorlax_event_func_get func) {
    snorlax_event_t * node = queue->head;

    while(node) {
        queue->head = queue->head->next;

        if(func) {
            func(node);
        }

        free(node);

        node = queue->head;
    }

    queue->head = nil;
    queue->tail = nil;
    queue->size = 0;

    return nil;
}

extern snorlax_event_t * snorlax_event_queue_add(snorlax_event_queue_t * queue, snorlax_event_t * event) {
    if(queue->tail) {
        queue->tail->next = event;
        event->prev = queue->tail;
    } else {
        queue->head = event;
    }

    queue->tail = event;
    queue->size = queue->size + 1;

    return event;
}

extern snorlax_event_t * snorlax_event_queue_del(snorlax_event_queue_t * queue, snorlax_event_t * event, snorlax_event_func_get func) {
    snorlax_event_t * prev = event->prev;
    snorlax_event_t * next = event->next;

    if(prev) {
        prev->next = next;
    } else {
        queue->head = next;
    }

    if(next) {
        next->prev = prev;
    } else {
        queue->tail = prev;
    }

    queue->size = queue->size - 1;

    if(func) {
        func(event);
    }

    free(event);

    return nil;
}

extern snorlax_event_t * snorlax_event_queue_begin(snorlax_event_queue_t * queue) {
    return queue->head;
}

extern snorlax_event_t * snorlax_event_queue_end(snorlax_event_queue_t * queue) {
    return nil;
}

extern snorlax_event_t * snorlax_event_queue_find(snorlax_event_queue_t * queue, ...) {
    // TODO: IMPLEMENT THIS
    return nil;
}
