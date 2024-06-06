/**
 * @file        snorlax/event/object.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 5, 2024
 */

#ifndef   __SNORLAX__EVENT_OBJECT__H__
#define   __SNORLAX__EVENT_OBJECT__H__

#include <snorlax.h>

struct snorlax_event_engine;
struct snorlax_event_object;
struct snorlax_event_object_func;

typedef struct snorlax_event_engine snorlax_event_engine_t;
typedef struct snorlax_event_object snorlax_event_object_t;
typedef struct snorlax_event_object_func snorlax_event_object_func_t;

struct snorlax_event_object {
    snorlax_event_object_func_t * func;
    snorlax_event_engine_t * engine;

    snorlax_event_object_t * prev;
    snorlax_event_object_t * next;

    uint32_t type;
};

struct snorlax_event_object_func {

    int (*interest)(snorlax_event_object_t *, uint32_t);
    
};

#endif // __SNORLAX__EVENT_OBJECT__H__
