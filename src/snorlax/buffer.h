/**
 * @file        snorlax/buffer.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 8, 2024
 */

#ifndef   __SNORLAX__BUFFER__H__
#define   __SNORLAX__BUFFER__H__

#include <stdint.h>

#include <snorlax.h>

struct buffer;

typedef struct buffer buffer_t;

struct buffer {
    uint8_t * mem;
    uint64_t  position;
    uint64_t  size;
    uint64_t  capacity;
};

extern buffer_t * buffer_gen(uint64_t capacity);
extern buffer_t * buffer_rem(buffer_t * o);
extern void buffer_capacity_set(buffer_t * o, uint64_t capacity);
extern void buffer_reset(buffer_t * o, uint64_t capacity);

#define buffer_front(o)             (&o->mem[o->position])
#define buffer_back(o)              (&o->mem[o->size])
#define buffer_len(o)               (o->size - o->position)
#define buffer_remain(o)            (o->capacity -  o->size)

#endif // __SNORLAX__BUFFER__H__
