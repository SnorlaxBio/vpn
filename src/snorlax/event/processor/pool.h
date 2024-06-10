/**
 * @file        snorlax/event/processor/pool.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 9, 2024
 */

#ifndef   __SNORLAX__EVENT_PROCESSOR_POOL__H__
#define   __SNORLAX__EVENT_PROCESSOR_POOL__H__

#include <stdint.h>

struct event_processor_pool;

typedef struct event_processor_pool event_processor_pool_t;

struct event_processor_pool {
    uint64_t size;
};

extern event_processor_pool_t * event_processor_pool_gen(void);

#endif // __SNORLAX__EVENT_PROCESSOR_POOL__H__
