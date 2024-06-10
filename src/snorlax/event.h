/**
 * @file        snorlax/event.h
 * @brief   
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 7, 2024
 */

#ifndef   __SNORLAX__EVENT__H__
#define   __SNORLAX__EVENT__H__

#include <stdint.h>

#include <snorlax.h>

struct event;
struct event_queue;
struct event_engine;
struct event_object;

typedef struct event event_t;
typedef struct event_object event_object_t;
typedef struct event_engine event_engine_t;
typedef struct event_queue event_queue_t;

typedef int (*event_handler_t)(event_object_t *, bucket_t, event_engine_t *);

struct event {
    event_handler_t     on;
    event_queue_t *     queue;
    event_t *           prev;
    event_t *           next;
    event_object_t *    object;
    bucket_t            param;
};

#define event_on(e, engine)     (e->on(e->object, e->param, engine))

#endif // __SNORLAX__EVENT__H__
