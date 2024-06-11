/**
 * @file        snorlax/event/engine/epoll.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>

#include "epoll.h"

#include "../queue.h"
#include "../object.h"
#include "../engine.h"

#include "../../event/processor/pool.h"

#include "../../descriptor.h"
#include "../../descriptor/state.h"
#include "../../descriptor/event/on.h"
#include "../../descriptor/event/type.h"

static event_engine_epoll_t * event_engine_epoll_rem(event_engine_epoll_t * engine);
static int event_engine_epoll_wait(event_engine_epoll_t * engine);

// int (*wait)(event_engine_epoll_t *);
// int (*reg)(event_engine_epoll_t *, event_object_t *);
// int (*unreg)(event_engine_epoll_t *, event_object_t *);

static event_engine_epoll_func_t func = {
    event_engine_epoll_rem,
    event_engine_epoll_wait,
};


extern event_engine_epoll_t * event_engine_epoll_gen(void) {
    event_engine_epoll_t * engine = (event_engine_epoll_t *) calloc(1, sizeof(event_engine_epoll_t));

    engine->func = &func;
    engine->queue = event_queue_gen();
    engine->maxevents = 1024;
    engine->events = malloc(sizeof(struct epoll_event) * engine->maxevents);
    engine->descriptor = invalid;
    engine->timeout = 1;
    engine->processors = event_processor_pool_gen();

    return engine;
}

static event_engine_epoll_t * event_engine_epoll_rem(event_engine_epoll_t * engine) {
    // close epoll file descriptor
    close(engine->descriptor);
    engine->descriptor = invalid;
    // clear event queue
    // todo: graceful remove event
    engine->queue = event_queue_rem(engine->queue, nil);
    // clear registered object
    event_object_t * object = engine->head;
    while(object) {
        engine->head = engine->head->next;
        // todo: graceful remove object
        free(object);
        object = engine->head;
    }

    engine->head = nil;
    engine->tail = nil;
    engine->size = 0lu;

    engine->processors = event_processor_pool_rem(engine->processors);

    free(engine->events);
    engine->events = nil;

    free(engine);

    return nil;
}

static int event_engine_epoll_wait(event_engine_epoll_t * engine) {
    struct epoll_event * events = (struct epoll_event *) engine->events;

    int nfds = epoll_wait(engine->descriptor, events, engine->maxevents, engine->timeout);

    if(nfds > 0) {
        for(int i = 0; i < nfds; i++) {
            descriptor_t * descriptor = (descriptor_t *) events[i].data.ptr;
            if(events[i].events & (EPOLLRDHUP | EPOLLPRI | EPOLLERR | EPOLLHUP)) {
                event_engine_dispatch_event_descriptor(engine,
                                                       descriptor,
                                                       descriptor_event_handler_get(descriptor, descriptor_event_type_exception),
                                                       (bucket_t) { 0, });
                continue;
            }
            // EPOLLOUT 부터 체크하는 것은 EPOLL IN 에서 읽은 후에 바로 쓸 수 있도록 하기 위해서이다.
            if(events[i].events & EPOLLOUT) {
                descriptor_state_set(descriptor, descriptor_state_writable);
                int64_t n = descriptor_write(descriptor);
                if(n > 0) {
                    event_engine_dispatch_event_descriptor(engine,
                                                           descriptor,
                                                           descriptor_event_handler_get(descriptor, descriptor_event_type_out),
                                                           (bucket_t) { .i64 = n });
                } else if(n == 0) {
                    // TODO: CHECK THIS
                } else {
                    event_engine_dispatch_event_descriptor(engine,
                                        descriptor,
                                        descriptor_event_handler_get(descriptor, descriptor_event_type_out),
                                        (bucket_t) { .i32 = errno });
                }
            }
            if(events[i].events & EPOLLIN) {
                descriptor_state_set(descriptor, descriptor_state_readable);
                int64_t n = descriptor_read(descriptor);
                // 나중을 위해서 EVENT QUEUE 에 삽입하는 방법을 사용하자.
            }
        }
    } else if(nfds < 0) {

    }

    return success;
}
