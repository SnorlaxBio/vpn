/**
 * @file        snorlax/eva.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#include <sys/epoll.h>

#include "eva.h"
#include "eva/epoll.h"

static snorlax_eva_t * eva = nil;

struct snorlax_eva {

    snorlax_eva_epoll_t * epoll;
    int descriptor;
};

extern int snorlax_eva_run(void) {
    if(eva == nil) {
        eva = calloc(1, sizeof(snorlax_eva_t));

        eva->descriptor = invalid;

        eva->descriptor = epoll_create(4096);
    }
    return success;
}

extern snorlax_event_object_t * snorlax_eva_reg(snorlax_event_object_t * o) {
    return nil;
}

extern snorlax_event_object_t * snorlax_eva_unreg(snorlax_event_object_t * o) {
    return nil;
}
