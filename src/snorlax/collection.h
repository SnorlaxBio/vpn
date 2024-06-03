/**
 * @file        snorlax/collection.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#ifndef   __SNORLAX__COLLECTION__H__
#define   __SNORLAX__COLLECTION__H__

#include <stdint.h>

#include <snorlax.h>
#include <snorlax/bucket.h>

struct snorlax_collection;
struct snorlax_collection_func;
struct snorlax_collection_node;

typedef struct snorlax_collection snorlax_collection_t;
typedef struct snorlax_collection_func snorlax_collection_func_t;
typedef struct snorlax_collection_node snorlax_collection_node_t;

struct snorlax_collection {
    snorlax_collection_func_t * func;
    uint64_t size;
};

struct snorlax_collection_node {
    snorlax_bucket_t bucket;
};

struct snorlax_collection_func {
    snorlax_collection_t * (*gen)(void);
    snorlax_collection_t * (*rem)(snorlax_collection_t *, snorlax_bucket_func_get);
    void (*clr)(snorlax_collection_t *, snorlax_bucket_func_get);
    snorlax_collection_node_t * (*add)(snorlax_collection_t *, snorlax_bucket_t);
    void (*del)(snorlax_collection_t *, snorlax_bucket_t);
    snorlax_collection_node_t * (*begin)(snorlax_collection_t *);
    snorlax_collection_node_t * (*end)(snorlax_collection_t *);
    snorlax_collection_node_t * (*find)(snorlax_collection_t *, snorlax_bucket_t);
};

#define snorlax_collection_size(o)      (((snorlax_collection_t *) o)->size)

extern snorlax_collection_t * snorlax_collection_gen(const snorlax_collection_func_t * func);

#define snorlax_collection_rem(o, func)     (o ? o->func->rem(o, func) : nil)
#define snorlax_collection_clr(o, func)     do {    \
    if(o) {                                         \
        o->func->clr(o, func);                      \
    }                                               \
} while(0)
#define snorlax_collection_add(o, bucket)   (o ? o->func->add(o, bucket) : nil)
#define snorlax_collection_del(o, bucket)   do {    \
    if(o) {                                         \
        o->func->del(o, bucket);                    \
    }                                               \
while(0)
#define snorlax_collection_begin(o)         (o ? o->func->begin(o) : nil)
#define snorlax_collection_end(o)           (o ? o->func->end(o) : nil)
#define snorlax_collection_find(o, bucket)  (o ? o->func->find(o) : nil)

#endif // __SNORLAX__COLLECTION__H__
