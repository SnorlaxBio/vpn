/**
 * @file        snorlax/event/engine/epoll.h
 * @brief
 * @details
 * 
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#ifndef   __SNORLAX__EVENT_ENGINE_EPOLL__H__
#define   __SNORLAX__EVENT_ENGINE_EPOLL__H__

#include <stdint.h>

struct event_object;
struct event_queue;
struct event_engine_epoll;
struct event_engine_epoll_func;

typedef struct event_queue event_queue_t;
typedef struct event_object event_object_t;
typedef struct event_engine_epoll event_engine_epoll_t;
typedef struct event_engine_epoll_func event_engine_epoll_func_t;

struct event_engine_epoll {
    event_engine_epoll_func_t * func;
    uint64_t                    size;
    event_object_t *            head;
    event_object_t *            tail;

    event_queue_t *             queue;

    void (*cancel)(event_engine_epoll_t *);

    int                         descriptor;
};

struct event_engine_epoll_func {
    event_engine_epoll_t * (*rem)(event_engine_epoll_t *);
    int (*wait)(event_engine_epoll_t *);
    int (*reg)(event_engine_epoll_t *, event_object_t *);
    int (*unreg)(event_engine_epoll_t *, event_object_t *);
};

extern event_engine_epoll_t * event_engine_epoll_gen(void);

#endif // __SNORLAX__EVENT_ENGINE_EPOLL__H__
