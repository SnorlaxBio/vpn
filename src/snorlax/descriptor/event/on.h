/**
 * @file        snorlax/descriptor/event/on.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 9, 2024
 */

#ifndef   __SNORLAX__DESCRIPTOR_EVENT_ON__H__
#define   __SNORLAX__DESCRIPTOR_EVENT_ON__H__

#include <snorlax.h>

struct descriptor;
struct event_engine;

typedef struct descriptor descriptor_t;
typedef struct event_engine event_engine_t;

extern int descriptor_event_on_exception(descriptor_t * o, bucket_t param, event_engine_t * engine);

#endif // __SNORLAX__DESCRIPTOR_EVENT_ON__H__
