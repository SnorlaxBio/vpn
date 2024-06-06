/**
 * @file        snorlax/event/queue.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 5, 2024
 */

#ifndef   __SNORLAX__EVENT_QUEUE__H__
#define   __SNORLAX__EVENT_QUEUE__H__

#include <stdint.h>
#include <stdio.h>

#include <snorlax.h>

struct snorlax_event;
struct snorlax_event_func;
struct snorlax_event_queue;
struct snorlax_event_queue_func;

typedef struct snorlax_event snorlax_event_t;
typedef struct snorlax_event_func snorlax_event_func_t;
typedef struct snorlax_event_queue snorlax_event_queue_t;
typedef struct snorlax_event_queue_func snorlax_event_queue_func_t;

typedef void (*snorlax_event_func_get)(snorlax_event_t *);

struct snorlax_event {
    snorlax_event_func_t * func;
    snorlax_event_queue_t * queue;

    snorlax_event_t * prev;
    snorlax_event_t * next;
};

struct snorlax_event_queue {
    snorlax_event_queue_func_t * func;
    uint64_t                     size;

    snorlax_event_t * head;
    snorlax_event_t * tail;
};

struct snorlax_event_func {
    snorlax_event_queue_t * (*gen)(uint64_t);
    snorlax_event_queue_t * (*rem)(snorlax_event_queue_t *, snorlax_event_func_get);
    void (*clear)(snorlax_event_queue_t *, snorlax_event_func_get);
    snorlax_event_t * (*add)(snorlax_event_queue_t *, snorlax_event_t *);
    snorlax_event_t * (*del)(snorlax_event_queue_t *, snorlax_event_t *, snorlax_event_func_get);
    snorlax_event_t * (*begin)(snorlax_event_queue_t *);
    snorlax_event_t * (*end)(snorlax_event_queue_t *);
    snorlax_event_t * (*find)(snorlax_event_queue_t *, ...);
};

extern snorlax_event_queue_t * snorlax_event_queue_gen(void);
extern snorlax_event_queue_t * snorlax_event_queue_rem(snorlax_event_queue_t * queue, snorlax_event_func_get func);
extern void snorlax_event_queue_clear(snorlax_event_queue_t * queue, snorlax_event_func_get func);
extern snorlax_event_t * snorlax_event_queue_add(snorlax_event_queue_t * queue, snorlax_event_t * event);
extern snorlax_event_t * snorlax_event_queue_del(snorlax_event_queue_t * queue, snorlax_event_t * event, snorlax_event_func_get func);
extern snorlax_event_t * snorlax_event_queue_begin(snorlax_event_queue_t * queue);
extern snorlax_event_t * snorlax_event_queue_end(snorlax_event_queue_t * queue);
extern snorlax_event_t * snorlax_event_queue_find(snorlax_event_queue_t * queue, ...);

#endif // __SNORLAX__EVENT_QUEUE__H__
