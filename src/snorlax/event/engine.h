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

#include <descriptor.h>
#include <descriptor/event.h>

struct event_engine;
struct event_engine_func;
struct event_object;
struct event_queue;
struct event_processor_pool;

typedef struct event_engine event_engine_t;
typedef struct event_engine_func event_engine_func_t;
typedef struct event_processor_pool event_processor_pool_t;

typedef struct event_object event_object_t;
typedef struct event_queue event_queue_t;

struct event_engine {
    event_engine_func_t *       func;
    uint64_t                    size;
    event_object_t *            head;
    event_object_t *            tail;

    event_queue_t *             queue;
    event_processor_pool_t *    processors;

    void (*cancel)(event_engine_t *);
};

struct event_engine_func {
    event_engine_t * (*rem)(event_engine_t *);
    int (*wait)(event_engine_t *);
    int (*reg)(event_engine_t *, event_object_t *);
    int (*unreg)(event_engine_t *, event_object_t *);
};

extern int event_engine_run(void);
extern int event_engine_on(void);
extern int event_engine_off(void (*cancel)(event_engine_t *));


extern void event_engine_dispatch_event_descriptor(event_engine_t * engine, descriptor_t * descriptor, descriptor_event_handler_t on, bucket_t param);

#define event_engine_wait(engine)       (engine->func->wait(engine))
#define event_engine_rem(engine)        (engine->func->rem(engine))
#define event_engine_reg(engine, o)     (engine->func->reg(engine, o))
#define event_engine_unreg(engine, o)   (engine->func->unreg(engine, o))

#endif // __SNORLAX__EVENT_ENGINE__H__
