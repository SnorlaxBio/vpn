/**
 * @file        snorlax/eva.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#include "eva.h"

static snorlax_eva_t * eva = nil;

static snorlax_eva_t * snorlax_eva_gen(void);

extern const snorlax_eva_t * snorlax_eva_get(void) {
    if(eva == nil) {
        eva = snorlax_eva_gen();
    }

    return eva;
}

extern int snorlax_eva_reg(int fd, int type, ...) {
    
}

static snorlax_eva_t * snorlax_eva_gen(void) {
    snorlax_eva_t * o = nil;
#ifdef    __linux__
    o = snorlax_eva_epoll_gen();
#endif // __linux__
    return o;
}