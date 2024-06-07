/**
 * @file        snorlax/event/engine.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#include "engine.h"
#include "queue.h"
#include "../event.h"

static event_engine_t * engine = nil;

extern int event_engine_run(void) {
    while(engine->cancel == nil) {
        event_engine_wait(engine);
        uint64_t n = engine->queue->size;
        for(uint64_t i = 0; i < n; i++) {
            event_t * e = event_queue_pop(engine->queue);
            if(e) {
                event_on(e);
                // todo: dispatch event
                continue;
            }
            break;
        }
    }

    if(engine->cancel) {
        engine->cancel(engine);
        engine->cancel = nil;
    }
    
    return success;
}
