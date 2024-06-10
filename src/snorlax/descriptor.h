/**
 * @file        snorlax/descriptor.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#ifndef   __SNORLAX__DESCRIPTOR__H__
#define   __SNORLAX__DESCRIPTOR__H__

#include <snorlax.h>
#include <snorlax/buffer.h>
#include <event/object.h>
#include <descriptor/event.h>

struct descriptor;
struct descriptor_func;

typedef struct descriptor descriptor_t;
typedef struct descriptor_func descriptor_func_t;

/**
 * 사용자는 디스크립터 객체에 IN, OUT, OPEN, EXCEPTION 등의
 * 이벤트 핸들링 함수를 등록할 수 있으며, 그 때마다 관련한 
 * 함수가 호출된다.
 */
struct descriptor {
    descriptor_func_t * func;
    event_engine_t *    engine;
    event_object_t *    prev;
    event_object_t *    next;

    event_queue_t *     queue;
    uint32_t            status;

    int                 descriptor;
    struct {
        buffer_t *      in;
        buffer_t *      out;
    } buffer;

    struct {
        descriptor_event_handler_t open;
        descriptor_event_handler_t close;
        descriptor_event_handler_t read;
        descriptor_event_handler_t write;
        descriptor_event_handler_t exception;
    } handler;
};
/**
 * 이벤트 핸들러를 어떻게 정의를 해야 하는가?
 */

struct descriptor_func {
    descriptor_t * (*rem)(descriptor_t *);

    int (*open)(descriptor_t *);
    int (*close)(descriptor_t *);
    int64_t (*read)(descriptor_t *);
    int64_t (*write)(descriptor_t *);
};

extern descriptor_t * descriptor_gen(int descriptor);

extern descriptor_t * descriptor_rem(descriptor_t * o);
extern int descriptor_open(descriptor_t * o);
extern int descriptor_close(descriptor_t * o);

// #define descriptor_rem(o)       (o->func->rem(o))
// #define descriptor_open(o)      (o->func->open(o))
// #define descriptor_write(o)     (o->func->write(o))
// #define descriptor_read(o)      (o->func->read(o))
// #define descriptor_close(o)     (o->func->close(o))

#define descriptor_state_set(o, state)      (o->status |= state)

#endif // __SNORLAX__DESCRIPTOR__H__
