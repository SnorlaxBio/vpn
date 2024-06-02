/**
 * @file        snorlax/eva/epoll.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#ifndef   __SNORLAX__EVA_EPOLL__H__
#define   __SNORLAX__EVA_EPOLL__H__

#include <sys/epoll.h>

#include <snorlax.h>

struct snorlax_eva_epoll {
    int type;

    int fd;
};

typedef struct snorlax_eva_epoll snorlax_eva_epoll_t;

extern snorlax_eva_epoll_t * snorlax_eva_epoll_gen(void);

#endif // __SNORLAX__EVA_EPOLL__H__
