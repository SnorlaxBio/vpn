/**
 * @file        snorlax/eva.h
 * @brief       Snorlax Event Engine
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#ifndef   __SNORLAX__EVA__H__
#define   __SNORLAX__EVA__H__

#include <snorlax.h>

struct snorlax_eva;

struct snorlax_eva {
    int type;
    // 전역 객체....
};

typedef struct snorlax_eva snorlax_eva_t;

extern const snorlax_eva_t * snorlax_eva_get(void);
extern int snorlax_eva_reg(int fd, int type, ...);
extern int snorlax_eva_run(void);

#endif // __SNORLAX__EVA__H__
