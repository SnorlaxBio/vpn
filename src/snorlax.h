/**
 * @file        snorlax.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 22, 2024
 */

#ifndef   __SNORLAX__H__
#define   __SNORLAX__H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define success                     0
#define fail                        (-1)
#define true                        1
#define false                       0
#define nil                         ((void *) 0)
#define invalid                     (-1)

typedef void *  object_t;

typedef void (*object_func_get)(object_t *);

union bucket {
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    object_t p;
};

typedef union bucket bucket_t;
typedef void (*bucket_func_get)(bucket_t);

#define addressof(o, offset)        (&o[offset])

#define uint32of(o, offset)         (*((uint32_t *) addressof(o, offset)))

#define snorlax_string_init(s)      (s[0] = 0)

#ifdef    SNORLAX_DEBUG
#define snorlax_debug_exit()        abort()
#else  // SNORLAX_DEBUG
#define snorlax_debug_exit()        do { } while(0)
#endif // SNORLAX_DEBUG

#define snorlax_error(format, ...) do {                                 \
    fprintf(stderr, "[error|%s:%d|%s] " format "\n", __FILE__,          \
                                                     __LINE__,          \
                                                     __func__,          \
                                                     ##__VA_ARGS__);    \
    snorlax_debug_exit();                                               \
} while(0)

#define snorlax_warning(format, ...) do {                               \
    fprintf(stderr, "[warning|%s:%d|%s] " format "\n", __FILE__,        \
                                                     __LINE__,          \
                                                     __func__,          \
                                                     ##__VA_ARGS__);    \
} while(0)

#define snorlax_caution(format, ...) do {                               \
    fprintf(stderr, "[caution|%s:%d|%s] " format "\n", __FILE__,        \
                                                     __LINE__,          \
                                                     __func__,          \
                                                     ##__VA_ARGS__);    \
} while(0)

#define snorlax_notice(format, ...) do {                                \
    fprintf(stderr, "[notice|%s:%d|%s] " format "\n", __FILE__,         \
                                                     __LINE__,          \
                                                     __func__,          \
                                                     ##__VA_ARGS__);    \
} while(0)

#define snorlax_debug(format, ...) do {                                 \
    fprintf(stderr, "[debug|%s:%d|%s] " format "\n", __FILE__,          \
                                                     __LINE__,          \
                                                     __func__,          \
                                                     ##__VA_ARGS__);    \
} while(0)

#define snorlax_verbose(format, ...) do {                               \
    fprintf(stderr, "[verbose|%s:%d|%s] " format "\n", __FILE__,        \
                                                     __LINE__,          \
                                                     __func__,          \
                                                     ##__VA_ARGS__);    \
} while(0)

#define snorlax_todo(format, ...) do {                                  \
    fprintf(stderr, "[todo|%s:%d|%s] " format "\n", __FILE__,           \
                                                     __LINE__,          \
                                                     __func__,          \
                                                     ##__VA_ARGS__);    \
    snorlax_debug_exit();                                               \
} while(0)

#endif // __SNORLAX__H__
