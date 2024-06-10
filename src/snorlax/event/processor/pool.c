/**
 * @file        snorlax/event/processor/pool.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 9, 2024
 */

#include <stdlib.h>

#include "pool.h"

extern event_processor_pool_t * event_processor_pool_gen(void) {
    event_processor_pool_t * o  = (event_processor_pool_t *) calloc(1, sizeof(event_processor_pool_t));

    return o;
}
