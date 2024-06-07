/**
 * @file        snorlax/event/engine.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#ifndef   __SNORLAX__EVENT_ENGINE__H__
#define   __SNORLAX__EVENT_ENGINE__H__

#include <stdint.h>

#include <snorlax.h>

struct event_engine;
struct event_engine_func;
struct event_object;
struct event_queue;

typedef struct event_engine event_engine_t;
typedef struct event_engine_func event_engine_func_t;

typedef struct event_object event_object_t;
typedef struct event_queue event_queue_t;

struct event_engine {
    event_engine_func_t *   func;
    uint64_t                size;
    event_object_t *        head;
    event_object_t *        tail;

    event_queue_t *         queue;

    void (*cancel)(event_engine_t *);
};

struct event_engine_func {
    int (*wait)(event_engine_t *);
};

extern int event_engine_run(void);
#define event_engine_wait(engine)       (engine->func->wait(engine))


#endif // __SNORLAX__EVENT_ENGINE__H__
