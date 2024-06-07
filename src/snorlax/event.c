/**
 * @file        snorlax/event.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 7, 2024
 * 
 */

#include "event.h"

extern event_t * event_gen(uint32_t type, uint32_t flags, bucket_t o) {
    event_t * event = (event_t *) calloc(1, sizeof(event_t));

    event->type = type;
    event->flags = flags;
    event->o = o;

    return event;
}

/**
 * @comment     이벤트 객체에 EVENT QUEUE 를 두면,...?????? 메모리 사용량은 증가
 *              여러 개의 큐를 둘 수 있다.
 *              메모리 사용량이 우선이다.
 * @comment     오랜 만에 빌드를 할까?
 * @comment     이벤트 큐를 짜자
 * @comment     이벤트가 큐에서 빠져 나오면, 객체에 종속되어야 하기 때문에,...
 *              큐가 여러 개일 수 있겠구나.
 *              그러면 EVENT 객체에 QUEUE 가 정의되어져야 하네...
 */
extern event_t * event_rem(event_t * e, bucket_func_get get) {
    if(get) get(e->o);
    free(e);
    return nil;
}