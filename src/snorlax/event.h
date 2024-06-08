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
/**
 * 이벤트 제네레이터와 프로세스를 나눌 필요는 있다.
 * 하지만, 지금은 현 상태를 유지할 것이다.
 */
struct event_generator;
struct event_processor;
struct event_engine;

typedef struct event event_t;
typedef struct event_engine event_engine_t;
typedef struct event_queue event_queue_t;
typedef struct event_generator event_generator_t;
typedef struct event_processor event_processor_t;

typedef int (*event_handler_t)(event_t *, event_engine_t *);
typedef void (*event_func_t)(event_t *);

struct event {
    event_handler_t on;
    event_queue_t * queue;
    event_t *       prev;
    event_t *       next;
};

#define event_on(e, engine)     (e->on(e, engine))

#endif // __SNORLAX__EVENT__H__
