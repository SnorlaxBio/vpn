/**
 * @file        snorlax/eva.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 6, 2024
 */

#include "eva.h"

#include "event.h"
#include "event/engine.h"


extern int snorlax_eva_run(void) {
    event_engine_on();
    return event_engine_run();
}