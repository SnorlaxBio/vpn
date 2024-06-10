/**
 * @file        snorlax/descriptor/event.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#include "event.h"
#include "event/type.h"

#include "../event/queue.h"

static int descriptor_event_on_void(descriptor_event_t * e, event_engine_t * engine);
static int descriptor_event_on_read(descriptor_event_t * e, event_engine_t * engine);
static int descriptor_event_on_write(descriptor_event_t * e, event_engine_t * engine);
static int descriptor_event_on_close(descriptor_event_t * e, event_engine_t * engine);
static int descriptor_event_on_exception(descriptor_event_t * e, event_engine_t * engine);
static int descriptor_event_on_open(descriptor_event_t * e, event_engine_t * engine);

static descriptor_event_handler_t handlers[6] = {
    descriptor_event_on_void,
    descriptor_event_on_read,
    descriptor_event_on_write,
    descriptor_event_on_close,
    descriptor_event_on_exception,
    descriptor_event_on_open
};

extern descriptor_event_t * descriptor_event_gen(descriptor_t * o, descriptor_event_handler_t handler, bucket_t param, event_engine_t * engine) {
    descriptor_event_t * e = (descriptor_event_t *) calloc(1, sizeof(descriptor_event_t));

    e->on = handler;
    e->descriptor = o;
    e->param = param;

    event_queue_push(engine->queue, (event_t *) e);

    return e;
}
