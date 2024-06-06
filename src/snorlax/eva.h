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
struct snorlax_event;
struct snorlax_event_object;

typedef struct snorlax_eva snorlax_eva_t;
typedef struct snorlax_event snorlax_event_t;
typedef struct snorlax_event_object snorlax_event_object_t;

extern int snorlax_eva_run(void);

extern snorlax_event_object_t * snorlax_eva_reg(snorlax_event_object_t * o);
extern snorlax_event_object_t * snorlax_eva_unreg(snorlax_event_object_t * o);

#endif // __SNORLAX__EVA__H__
