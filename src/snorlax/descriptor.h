/**
 * @file        snorlax/descriptor.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 4, 2024
 */

#ifndef   __SNORLAX__DESCRIPTOR__H__
#define   __SNORLAX__DESCRIPTOR__H__

struct snorlax_descriptor;
struct snorlax_descriptor_func;

typedef struct snorlax_descriptor snorlax_descriptor_t;
typedef struct snorlax_descriptor_func snorlax_descriptor_func_t;

struct snorlax_descriptor {
    snorlax_descriptor_func_t * func;
    snorlax_event_engine_t * engine;

    snorlax_event_object_t * prev;
    snorlax_event_object_t * next;

    uint32_t type;
    int descriptor;
};

struct snorlax_descriptor_func {
    int (*open)(snorlax_descriptor_t *);
};

#define snorlax_descriptor_get(object)      (((snorlax_descriptor_t *) object)->descriptor)
#define snorlax_descriptor_open(object)     (object->func->open(object))

#endif // __SNORLAX__DESCRIPTOR__H__
