/**
 * @file        snorlax/event/object.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#ifndef   __SNORLAX__EVENT_OBJECT__H__
#define   __SNORLAX__EVENT_OBJECT__H__

struct event_object;
struct event_queue;

typedef struct event_object event_object_t;
typedef struct event_queue event_queue_t;

struct event_object {
    event_object_t * prev;
    event_object_t * next;
    event_queue_t * queue;
};

#endif // __SNORLAX__EVENT_OBJECT__H__
