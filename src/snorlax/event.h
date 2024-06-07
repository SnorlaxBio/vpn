/**
 * @file        snorlax/event.h
 * @brief   
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 7, 2024
 */

#ifndef   __SNORLAX__EVENT__H__
#define   __SNORLAX__EVENT__H__

#include <stdint.h>

#include <snorlax.h>

struct event;
struct event_queue;

typedef struct event event_t;
typedef struct event_queue event_queue_t;

struct event {
    event_queue_t * queue;
    event_t *       prev;
    event_t *       next;
    uint32_t        type;
    uint32_t        flags;
    bucket_t        o;
};

extern event_t * event_gen(uint32_t type, uint32_t flags, bucket_t o);
extern event_t * event_rem(event_t * e, bucket_func_get get);

#endif // __SNORLAX__EVENT__H__
