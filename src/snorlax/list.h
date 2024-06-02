/**
 * @file        snorlax/list.h
 * @brief   
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#ifndef   __SNORLAX__LIST__H__
#define   __SNORLAX__LIST__H__

#include <stdint.h>
#include <stdio.h>

#define snorlax_list_double_linked          1

struct snorlax_list {
    int type;
};

typedef struct snorlax_list snorlax_list_t;

extern snorlax_list_t * snorlax_list_gen(uint32_t type);

#endif // __SNORLAX__LIST__H__
