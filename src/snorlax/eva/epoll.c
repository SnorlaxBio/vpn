#include "epoll.h"

#include "type.h"

extern snorlax_eva_epoll_t * snorlax_eva_epoll_gen(void) {
    snorlax_eva_epoll_t * o = (snorlax_eva_epoll_t *) calloc(1, sizeof(snorlax_eva_epoll_t));

    o->type = snorlax_eva_engine_type_epoll;
    o->fd = invalid;

    return nil;
}