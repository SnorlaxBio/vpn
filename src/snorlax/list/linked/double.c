/**
 * @file        snorlax/list/linked/double.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 3, 2024
 */

#include "double.h"

static list_linked_double_t * list_linked_double_rem(list_linked_double_t * collection, object_func_get func);
static void list_linked_double_clear(list_linked_double_t * collection, object_func_get func);
static list_linked_double_node_t * list_linked_double_add(list_linked_double_t * collection, object_t o, uint64_t size);

static list_linked_double_func_t func = {
    list_linked_double_gen,
    list_linked_double_rem,
    list_linked_double_clear,
    // list_linked_double_node_t * (*add)(list_linked_double_t *, object_t, uint64_t);
    // list_linked_double_node_t * (*del)(list_linked_double_t *, object_func_get);
    // list_linked_double_node_t * (*begin)(list_linked_double_t *);
    // list_linked_double_node_t * (*end)(list_linked_double_t *);
    // list_linked_double_node_t * (*find)(list_linked_double_t *, object_t);
    // list_linked_double_node_t * (*nodegen)(list_linked_double_t *, object_t, uint64_t);
    // list_linked_double_node_t * (*noderem)(list_linked_double_node_t *, object_func_get);
};

extern list_linked_double_t * list_linked_double_gen(uint64_t size) {
    list_linked_double_t * collection = (list_linked_double_t *) calloc(1, sizeof(list_linked_double_t) + size);

    collection->func = &func;

    return collection;
}

static list_linked_double_t * list_linked_double_rem(list_linked_double_t * collection, object_func_get func) {
    list_linked_double_node_t * node = collection->head;

    while(node) {
        collection->head = collection->head->next;
        collection->func->noderem(node, func);
        node = collection->head;
    }

    free(collection);
    return nil;
}

static void list_linked_double_clear(list_linked_double_t * collection, object_func_get func) {
    list_linked_double_node_t * node = collection->head;

    while(node) {
        collection->head = collection->head->next;
        collection->func->noderem(node, func);
        node = collection->head;
    }

    collection->head = nil;
    collection->tail = nil;
    collection->size = 0lu;
}

static list_linked_double_node_t * list_linked_double_add(list_linked_double_t * collection, object_t o, uint64_t size) {
    list_linked_double_node_t * node = collection->func->nodegen(collection, o, size);

    if(collection->tail) {
        collection->tail->next = node;
        node->prev = collection->tail;
    } else {
        collection->head = node;
    }
    
    collection->tail = node;
    collection->size = collection->size + 1;

    return node;
}

// static snorlax_list_linked_double_t * snorlax_list_linked_double_gen(void);
// static snorlax_list_linked_double_t * snorlax_list_linked_double_rem(snorlax_list_linked_double_t * o, snorlax_bucket_func_get func);
// static void snorlax_list_linked_double_clr(snorlax_list_linked_double_t * o, snorlax_bucket_func_get func);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_add(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_del(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_begin(snorlax_list_linked_double_t * o);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_end(snorlax_list_linked_double_t * o);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_find(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket);

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_insert_node_prev(snorlax_list_linked_double_t * o, snorlax_list_linked_double_node_t * next, snorlax_bucket_t bucket);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_insert_node_next(snorlax_list_linked_double_t * o, snorlax_list_linked_double_node_t * prev, snorlax_bucket_t bucket);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_push_front(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_push_back(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket);
// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_delete_node(snorlax_list_linked_double_t * o, snorlax_list_linked_double_node_t * node, snorlax_bucket_func_get func);

// static snorlax_list_linked_double_func_t func = {
//     snorlax_list_linked_double_gen,
//     snorlax_list_linked_double_rem,
//     snorlax_list_linked_double_clr,
//     snorlax_list_linked_double_add,
//     snorlax_list_linked_double_del,
//     snorlax_list_linked_double_begin,
//     snorlax_list_linked_double_end,
//     snorlax_list_linked_double_find,
//     snorlax_list_linked_double_insert_node_prev,
//     snorlax_list_linked_double_insert_node_next,
//     snorlax_list_linked_double_push_front,
//     snorlax_list_linked_double_push_back,
//     snorlax_list_linked_double_delete_node
// };

// static snorlax_list_linked_double_t * snorlax_list_linked_double_gen(void) {
//     snorlax_list_linked_double_t * o = (snorlax_list_linked_double_t *) calloc(1, sizeof(snorlax_list_linked_double_t));

//     o->func = &func;

//     return o;
// }

// static snorlax_list_linked_double_t * snorlax_list_linked_double_rem(snorlax_list_linked_double_t * o, snorlax_bucket_func_get func) {
//     if(o) {
//         snorlax_list_linked_double_node_t * node = o->head;
//         while(node) {
//             if(func) {
//                 func(o->head->bucket);
//             }
//             o->head = o->head->next;
//             free(node);
//             node = o->head;
//         }
//         /**
//          * TODO: IMPLEMENT THIS
//          */
//         free(o);
//         o = nil;
//     }
//     return o;
// }

// static void snorlax_list_linked_double_clr(snorlax_list_linked_double_t * o, snorlax_bucket_func_get func) {
//     if(o) {
//         snorlax_list_linked_double_node_t * node = o->head;
//         while(node) {
//             if(func) {
//                 func(o->head->bucket);
//             }
//             o->head = o->head->next;
//             free(node);
//             node = o->head;
//         }
//         o->head = nil;
//         o->tail = nil;
//         o->size = 0lu;
//     }
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_add(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket) {
//     if(o) {
//         snorlax_list_linked_double_node_t * node = (snorlax_list_linked_double_node_t *) calloc(1, sizeof(snorlax_list_linked_double_node_t));
//         node->bucket = bucket;
//         node->collection = o;

//         if(o->tail) {
//             o->tail->next = node;
//             node->prev = o->tail;
//             o->tail = node;
//         } else {
//             o->head = node;
//             o->tail = node;
//         }

//         o->size = o->size + 1;

//         return node;
//     }

//     return nil;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_del(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket) {
//     snorlax_list_linked_double_node_t * node = snorlax_list_linked_double_find(o, bucket);
//     if(node) {
//         snorlax_list_linked_double_node_t * prev = node->prev;
//         snorlax_list_linked_double_node_t * next = node->next;

//         if(prev) {
//             prev->next = next;
//         } else {
//             o->head = next;
//         }

//         if(next) {
//             next->prev = prev;
//         } else {
//             o->tail = prev;
//         }

//         free(node);
//         o->size = o->size - 1;
//     }

//     return node;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_begin(snorlax_list_linked_double_t * o) {
//     return o ? o->head : nil;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_end(snorlax_list_linked_double_t * o) {
//     return o ? o->tail : nil;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_find(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket) {
//     if(o) {
//         for(snorlax_list_linked_double_node_t * node = o->head; node != nil; node = node->next) {
//             if(node->bucket.u64 = bucket.u64) {
//                 return node;
//             }
//         }

//         return nil;
//     }

//     return nil; 
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_insert_node_prev(snorlax_list_linked_double_t * o, snorlax_list_linked_double_node_t * next, snorlax_bucket_t bucket) {
//     if(o) {
//         snorlax_list_linked_double_node_t * node = (snorlax_list_linked_double_node_t *) calloc(1, sizeof(snorlax_list_linked_double_node_t));
//         node->bucket = bucket;
//         node->collection = o;

//         snorlax_list_linked_double_node_t * prev = next ? next->prev : nil;

//         if(prev) {
//             prev->next = node;
//             node->prev = prev;
//         } else {
//             o->head = node;
//         }

//         if(next) {
//             next->prev = node;
//             node->next = next;
//         } else {
//             o->tail = node;
//         }

//         o->size = o->size + 1;

//         return node;
//     }

//     return nil;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_insert_node_next(snorlax_list_linked_double_t * o, snorlax_list_linked_double_node_t * prev, snorlax_bucket_t bucket) {
//     if(o) {
//         snorlax_list_linked_double_node_t * node = (snorlax_list_linked_double_node_t *) calloc(1, sizeof(snorlax_list_linked_double_node_t));
//         node->bucket = bucket;
//         node->collection = o;

//         snorlax_list_linked_double_node_t * next = prev ? prev->next : nil;

//                 if(prev) {
//             prev->next = node;
//             node->prev = prev;
//         } else {
//             o->head = node;
//         }

//         if(next) {
//             next->prev = node;
//             node->next = next;
//         } else {
//             o->tail = node;
//         }

//         o->size = o->size + 1;

//         return node;
//     }

//     return nil;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_push_front(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket) {
//     if(o) {
//         snorlax_list_linked_double_node_t * node = (snorlax_list_linked_double_node_t *) calloc(1, sizeof(snorlax_list_linked_double_node_t));
//         node->bucket = bucket;
//         node->collection = o;

//         node->next = o->head;

//         if(o->head) {
//             o->head->prev = node;
//         } else {
//             o->tail = node;
//         }

//         o->head = node;
//         o->size = o->size + 1;

//         return node;
//     }

//     return nil;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_push_back(snorlax_list_linked_double_t * o, snorlax_bucket_t bucket) {
//     if(o) {
//         snorlax_list_linked_double_node_t * node = (snorlax_list_linked_double_node_t *) calloc(1, sizeof(snorlax_list_linked_double_node_t));
//         node->bucket = bucket;
//         node->collection = o;

//         node->prev = o->tail;

//         if(o->tail) {
//             o->tail->next = node;
//         } else {
//             o->head = node;
//         }

//         o->tail = node;
//         o->size = o->size + 1;

//         return node;
//     }

//     return nil;
// }

// static snorlax_list_linked_double_node_t * snorlax_list_linked_double_delete_node(snorlax_list_linked_double_t * o, snorlax_list_linked_double_node_t * node, snorlax_bucket_func_get func) {
//     if(o && node) {
//         snorlax_list_linked_double_node_t * prev = node->prev;
//         snorlax_list_linked_double_node_t * next = node->next;

//         if(prev) {
//             prev->next = next;
//         } else {
//             o->head = next;
//         }

//         if(next) {
//             next->prev = prev;
//         } else {
//             o->tail = prev;
//         }

//         o->size = o->size -1;

//         if(func) {
//             func(node->bucket);
//         }

//         free(node);
//         return nil;
//     }

//     // TODO: CHECK NOT REMOVED
//     return node;
// }

