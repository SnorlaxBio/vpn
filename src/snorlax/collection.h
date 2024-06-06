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

struct collection;
struct collection_func;
struct collection_node;

typedef struct collection collection_t;
typedef struct collection_node collection_node_t;
typedef struct collection_func collection_func_t;

typedef void (*collection_node_func_get)(collection_node_t *);

struct collection {
    collection_func_t * func;       /**!< 콜렉션 타입과 콜렉션에서 사용할 메서드 테이블 */
    uint64_t            size;       /**!< 콜렉션에 저장된 아이템의 크기 */
};

/**
 * 콜렉션 노드에 버켓은 사용할 때 정의하자.
 * 버켓이 필요해보이기도 하다가도, 낭비인 듯 보이고,...
 * 
 */
struct collection_node {
    collection_t *           collection;    ///!< 노드
};

struct collection_func {
    collection_t * (*gen)(uint64_t);
    collection_t * (*rem)(collection_t *, object_func_get);
    void (*clear)(collection_t *, object_func_get);
    collection_node_t * (*add)(collection_t *, collection_node_t *);
    collection_node_t * (*del)(collection_t *, collection_node_t *, object_func_get);
    collection_node_t * (*begin)(collection_t *);
    collection_node_t * (*end)(collection_t *);
    collection_node_t * (*find)(collection_t *, object_t);
    collection_node_t * (*nodegen)(collection_t *, object_t, uint64_t);
    collection_node_t * (*noderem)(collection_node_t *, object_func_get);
};

extern collection_t * collection_gen(collection_func_t * func, uint64_t size);

#define collection_rem(collection, func)    (collection->func->rem(collection, func))
#define collection_clear(collection, func)  do {    \
    collection->func->clear(collection, func);      \
} while(0)
#define collection_add(collection, o)       (collection->func->add(collection, o))
#define collection_del(collection, o)       (collection->func->del(collection, o))
#define collection_begin(collection)        (collection->func->begin(collection))
#define collection_end(collection)          (collection->func->end(collection))
#define collection_find(collection, o)      (collection->func->find(collection, o))

#endif // __SNORLAX__COLLECTION__H__
