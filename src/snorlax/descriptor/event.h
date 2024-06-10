/**
 * @file        snorlax/descriptor/event.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#ifndef   __SNORLAX__DESCRIPTOR_EVENT__H__
#define   __SNORLAX__DESCRIPTOR_EVENT__H__

#include <snorlax/event.h>
#include <snorlax/event/engine.h>

#include <snorlax/descriptor.h>

struct descriptor_event;

typedef struct descriptor_event descriptor_event_t;

typedef int (*descriptor_event_handler_t)(descriptor_event_t *, bucket_t, event_engine_t *);

struct descriptor_event {
    descriptor_event_handler_t on;
    event_queue_t *            queue;
    event_t *                  prev;
    event_t *                  next;

    descriptor_t *             descriptor;
    bucket_t                   param;
};

extern descriptor_event_t * descriptor_event_gen(descriptor_t * o, descriptor_event_handler_t handler, bucket_t param, event_engine_t * engine);

#endif // __SNORLAX__DESCRIPTOR_EVENT__H__
