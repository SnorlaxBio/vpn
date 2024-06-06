/**
 * @file        snorlax/list/linked/double.h
 * @brief
 * @details
 * 
 * 이렇게 짜는 것은 LONG JUMP 가 많아 보인다.
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 3, 2024
 */

#ifndef   __SNORLAX__LIST_LINKED_DOUBLE__H__
#define   __SNORLAX__LIST_LINKED_DOUBLE__H__

#include <stdint.h>
#include <stdio.h>

#include <snorlax.h>

struct list_linked_double;
struct list_linked_double_func;
struct list_linked_double_node;

typedef struct list_linked_double list_linked_double_t;
typedef struct list_linked_double_func list_linked_double_func_t;
typedef struct list_linked_double_node list_linked_double_node_t;

struct list_linked_double {
    list_linked_double_func_t * func;
    uint64_t                    size;

    list_linked_double_node_t * head;
    list_linked_double_node_t * tail;
};

/**
 * 콜렉션에 가상 함수 테이블이 필요할까?
 */
struct list_linked_double_node {
    list_linked_double_t *           collection;

    list_linked_double_node_t *      prev;
    list_linked_double_node_t *      next;
};

struct list_linked_double_func {
    list_linked_double_t * (*gen)(uint64_t);
    list_linked_double_t * (*rem)(list_linked_double_t *, object_func_get);
    void (*clear)(list_linked_double_t *, object_func_get);
    list_linked_double_node_t * (*add)(list_linked_double_t *, object_t, uint64_t);
    list_linked_double_node_t * (*del)(list_linked_double_t *, object_func_get);
    list_linked_double_node_t * (*begin)(list_linked_double_t *);
    list_linked_double_node_t * (*end)(list_linked_double_t *);
    list_linked_double_node_t * (*find)(list_linked_double_t *, object_t);
    list_linked_double_node_t * (*nodegen)(list_linked_double_t *, object_t, uint64_t);
    list_linked_double_node_t * (*noderem)(list_linked_double_node_t *, object_func_get);
};

extern list_linked_double_t * list_linked_double_gen(uint64_t size);

/*******************************************************/

// struct snorlax_list_linked_double;
// struct snorlax_list_linked_double_node;
// struct snorlax_list_linked_double_func;

// typedef struct snorlax_list_linked_double snorlax_list_linked_double_t;
// typedef struct snorlax_list_linked_double_node snorlax_list_linked_double_node_t;
// typedef struct snorlax_list_linked_double_func snorlax_list_linked_double_func_t;

// struct snorlax_list_linked_double {
//     // INHERITED COLLECTION
//     snorlax_list_linked_double_func_t * func;
//     uint64_t size;
//     // SPECIFIED MEMBER OF DOUBLE LINKED LIST
//     snorlax_list_linked_double_node_t * head;
//     snorlax_list_linked_double_node_t * tail;
// };

// struct snorlax_list_linked_double_node {
//     // INHERITED COLLECTION NODE
//     snorlax_list_linked_double_t * collection;
//     snorlax_bucket_t bucket;
//     // SPECIFIED MEMBER OF DOUBLE LINKED LIST ITEM
//     snorlax_list_linked_double_node_t * prev;
//     snorlax_list_linked_double_node_t * next;
// };

// /**
//  * 노출 시켜야 할 필요가 있다.
//  * 
//  * PRIVATE & PUBLIC
//  */
// struct snorlax_list_linked_double_func {
//     // INHERIED METHOD OF COLLECTION
//     snorlax_list_linked_double_t * (*gen)(void);
//     snorlax_list_linked_double_t * (*rem)(snorlax_list_linked_double_t *, snorlax_bucket_func_get);
//     void (*clr)(snorlax_list_linked_double_t *, snorlax_bucket_func_get);
//     snorlax_list_linked_double_node_t * (*add)(snorlax_list_linked_double_t *, snorlax_bucket_t);
//     snorlax_list_linked_double_node_t * (*del)(snorlax_list_linked_double_t *, snorlax_bucket_t);
//     snorlax_list_linked_double_node_t * (*begin)(snorlax_list_linked_double_t *);
//     snorlax_list_linked_double_node_t * (*end)(snorlax_list_linked_double_t *);
//     snorlax_list_linked_double_node_t * (*find)(snorlax_list_linked_double_t *, snorlax_bucket_t);
//     // SPECIFIED METHOD OF DOUBLE LINKED LIST
//     snorlax_list_linked_double_node_t * (*insert_node_prev)(snorlax_list_linked_double_t *, snorlax_list_linked_double_node_t *, snorlax_bucket_t);
//     snorlax_list_linked_double_node_t * (*insert_node_next)(snorlax_list_linked_double_t *, snorlax_list_linked_double_node_t *, snorlax_bucket_t);
//     snorlax_list_linked_double_node_t * (*push_front)(snorlax_list_linked_double_t *, snorlax_bucket_t);
//     snorlax_list_linked_double_node_t * (*push_back)(snorlax_list_linked_double_t *, snorlax_bucket_t);
//     snorlax_list_linked_double_node_t * (*delete_node)(snorlax_list_linked_double_t *, snorlax_list_linked_double_node_t *, snorlax_bucket_func_get);
// };

#endif // __SNORLAX__LIST_LINKED_DOUBLE__H__
