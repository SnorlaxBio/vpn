/**
 * @file        snorlax/event/queue.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 7, 2024
 * 
 * @comment     이벤트 큐는 전역적으로 하나다. 그렇기 때문에, 파라미터로 queue 객체를
 *              정의하지 말자.
 */

#ifndef   __SNORLAX__EVENT_QUEUE__H__
#define   __SNORLAX__EVENT_QUEUE__H__

#include <stdint.h>

#include <snorlax.h>

struct event;
struct event_queue;

typedef struct event event_t;
typedef struct event_queue event_queue_t;

typedef void (*event_func_t)(event_t *);

struct event_queue {
    uint64_t  size;
    event_t * head;
    event_t * tail;
};

extern event_queue_t * event_queue_gen(void);
extern event_queue_t * event_queue_rem(event_queue_t * queue, event_func_t func);
extern void event_queue_push(event_queue_t * queue, event_t * e);
extern event_t * event_queue_pop(event_queue_t * queue);
extern void event_queue_clear(event_queue_t * queue, event_func_t func);

#endif // __SNORLAX__EVENT_QUEUE__H__
