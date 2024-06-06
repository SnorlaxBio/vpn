/**
 * @file        snorlax/event/engine/epoll.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 5, 2024
 */

#include <sys/epoll.h>

#include "epoll.h"
#include "../../descriptor.h"
#include "../object.h"
#include "../type.h"
#include "../flag.h"

static int snorlax_event_engine_epoll_on(snorlax_event_engine_epoll_t * engine);
static int snorlax_event_engine_epoll_off(snorlax_event_engine_epoll_t * engine);
static int snorlax_event_engine_epoll_loop(snorlax_event_engine_epoll_t * engine);
// snorlax_event_object_t * (*reg)(snorlax_event_object_t *);
// snorlax_event_object_t * (*unreg)(snorlax_event_object_t *);

static int snorlax_event_engine_epoll_on(snorlax_event_engine_epoll_t * engine) {
    if(engine->descriptor == invalid) {
        engine->descriptor = epoll_create(engine->maxevents);
        if(engine->events == nil) {
            engine->events = malloc(sizeof(struct epoll_event) * engine->maxevents);
        }
        if(engine->descriptor >= 0) {
            for(snorlax_event_object_t * object = engine->head; object != nil; object = object->next) {
                if(object->type & snorlax_event_io) {
                    uint32_t interest = object->func->interest(object, snorlax_event_io);
                    struct epoll_event event;
                    event.data.ptr = object;
                    event.events = (EPOLLRDHUP | EPOLLPRI | EPOLLERR | EPOLLHUP | EPOLLET | EPOLLONESHOT);
                    if(interest & snorlax_event_flag_in) {
                        event.events |= EPOLLIN;
                    }
                    if(interest & snorlax_event_flag_out) {
                        event.events |= EPOLLOUT;
                    }

                    if(snorlax_descriptor_get(object) < 0) {
                        snorlax_descriptor_open(((snorlax_descriptor_t *) object));
                    }

                    if(epoll_ctl(engine->descriptor, EPOLL_CTL_ADD, snorlax_descriptor_get(object), &event) < 0) {
                        // 새로운 POST 이벤트를 만든다.
                    }
                }
            }

            return success;
        }
    }
    // 이미 등록된 
    return fail;
}

static int snorlax_event_engine_epoll_off(snorlax_event_engine_epoll_t * engine) {
    if(engine->descriptor >= 0) {
        close(engine->descriptor);
        engine->descriptor = invalid;

        /**
         * TODO: CLEAR EVENT OBJECT ...
         */
    }
    return fail;
}

static int snorlax_event_engine_epoll_loop(snorlax_event_engine_epoll_t * engine) {
    while(engine->cancel == nil) {
        int nfds = epoll_wait(engine->descriptor, (struct epoll_event *) engine->events, engine->maxevents, engine->timeout);
        if(nfds > 0) {
            for(int i = 0; i < nfds; i++) {
                struct epoll_event * event = addressof(((struct epoll_event *) engine->events), i);
                snorlax_descriptor_t * object = (snorlax_descriptor_t *) event->data.ptr;
                if(event->events & (EPOLLRDHUP | EPOLLPRI | EPOLLERR | EPOLLHUP)) {
                    // TODO: ERROR LOG
                    snorlax_descriptor_close(object);
                    // 
                    engine->func->unreg(engine, object);

                    // 다시 접속이 필요하거나 오픈이 필요할 경우 NONBLOCK으로 오픈한다.
                    // 그렇지 않으면,... 메모리에서 지운다.
                    engine->func->del(engine, object, nil); // 삭제하는 노드에 애해서 고민을 해보자. 필요할까?

                    continue;
                }
                if(event->events & EPOLLIN) {
                    
                }
                if(event->events & EPOLLOUT) {
                }
            }
        } else if(nfds < 0) {
            // TODO: CHECK ERROR
        }
    }

    if(engine->cancel) {
        engine->cancel(engine);
    }
}