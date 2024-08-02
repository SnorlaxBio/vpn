/**
 * @file        snorlax/protocol/context.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 29, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_CONTEXT__H__
#define   __SNORLAX__PROTOCOL_CONTEXT__H__

#include <snorlax.h>

struct protocol_context;
struct protocol_context_func;

typedef struct protocol_context protocol_context_t;
typedef struct protocol_context_func protocol_context_func_t;

struct protocol_context {
    protocol_context_func_t * func;
    sync_t * sync;
    protocol_context_t * parent;
    protocol_context_t * subcontext;
    int32_t error;
    uint8_t * packet;
    uint64_t packetlen;
};

struct protocol_context_func {
    protocol_context_t * (*rem)(protocol_context_t *);
};

#define protocol_context_rem(context)               ((context)->func->rem(context))

#define protocol_context_error_get(context)         ((context)->error)
#define protocol_context_error_set(context, v)      ((context)->error = v)

#endif // __SNORLAX__PROTOCOL_CONTEXT__H__
