/**
 * @file        snorlax/buffer.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#include "buffer.h"

extern buffer_t * buffer_gen(uint64_t capacity) {
    buffer_t * o = (buffer_t *) calloc(1, sizeof(buffer_t));

    o->capacity = capacity;
    o->mem = malloc(o->capacity);

    return o;
}

extern buffer_t * buffer_rem(buffer_t * o) {
    free(o->mem);
    free(o);

    return nil;
}

extern void buffer_capacity_set(buffer_t * o, uint64_t capacity) {
    if(capacity < o->size) {
        // TODO: ERROR HANDLING
    }
    if(o->size <= capacity) {
        o->capacity = capacity;
        o->mem = (uint8_t *) realloc(o->mem, o->capacity);
    }
}

extern void buffer_reset(buffer_t * o, uint64_t capacity) {
    o->size = 0;
    o->position = 0;
    o->capacity = capacity;
    o->mem = realloc(o->mem, o->capacity);
}