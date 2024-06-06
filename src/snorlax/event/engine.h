/**
 * @file        snorlax/event/engine.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 5, 2024
 */

#ifndef   __SNORLAX__EVENT_ENGINE__H__
#define   __SNORLAX__EVENT_ENGINE__H__

#include <stdint.h>

#include <snorlax.h>
#include <snorlax/event/queue.h>

struct snorlax_event_object;
struct snorlax_event_engine;
struct snorlax_event_engine_func;

typedef struct snorlax_event_object snorlax_event_object_t;
typedef struct snorlax_event_engine snorlax_event_engine_t;
typedef struct snorlax_event_engine_func snorlax_event_engine_func_t;

typedef void (*snorlax_event_object_func_get)(snorlax_event_object_t *);

struct snorlax_event_engine {
    snorlax_event_engine_func_t * func;
    uint64_t                      size;

    snorlax_event_object_t *      head;
    snorlax_event_object_t *      tail;

    snorlax_event_queue_t *       queue;
};

struct snorlax_event_engine_func {
    snorlax_event_engine_t * (*gen)(uint64_t);
    snorlax_event_engine_t * (*rem)(snorlax_event_engine_t *, snorlax_event_object_func_get);

    void (*clear)(snorlax_event_engine_t *, snorlax_event_object_func_get);
    snorlax_event_object_t * (*add)(snorlax_event_engine_t *, snorlax_event_object_t *);
    snorlax_event_object_t * (*del)(snorlax_event_engine_t *, snorlax_event_object_t *, snorlax_event_object_func_get);
    snorlax_event_object_t * (*begin)(snorlax_event_engine_t *);
    snorlax_event_object_t * (*end)(snorlax_event_engine_t *);
    snorlax_event_object_t * (*find)(snorlax_event_engine_t *, ...);

    int (*on)(snorlax_event_engine_t *);
    int (*off)(snorlax_event_engine_t *);
    int (*loop)(snorlax_event_engine_t *);

    snorlax_event_object_t * (*reg)(snorlax_event_object_t *);
    snorlax_event_object_t * (*unreg)(snorlax_event_object_t *);
};

#endif // __SNORLAX__EVENT_ENGINE__H__

