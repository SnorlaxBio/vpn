#include <stdlib.h>
#include <string.h>

#include "../../protocol.h"

static protocol_context_array_t * protocol_context_array_func_rem(protocol_context_array_t * collection);
static protocol_context_t * protocol_context_array_func_get(protocol_context_array_t * collection, uint64_t index);
static protocol_context_t ** protocol_context_array_func_pop(protocol_context_array_t * collection);

static protocol_context_array_func_t func = {
    protocol_context_array_func_rem,
    protocol_context_array_func_get,
    protocol_context_array_func_pop
};

extern protocol_context_array_t * protocol_context_array_gen(void) {
    protocol_context_array_t * collection = (protocol_context_array_t *) calloc(1, sizeof(protocol_context_array_t));

    collection->func = address_of(func);

    return collection;
}

static protocol_context_array_t * protocol_context_array_func_rem(protocol_context_array_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    for(uint64_t i = 0; i < collection->size; i++) {
        if(collection->container[i]) collection->container[i] = protocol_context_rem(collection->container[i]);
    }

    collection->sync = sync_rem(collection->sync);

    free(collection);

    return nil;
}

static protocol_context_t * protocol_context_array_func_get(protocol_context_array_t * collection, uint64_t index) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE

    return index < collection->size ? collection->container[index] : nil;
}

static protocol_context_t ** protocol_context_array_func_pop(protocol_context_array_t * collection) {
#ifndef   RELEASE
    snorlaxdbg(collection == nil, false, "critical", "");
#endif // RELEASE
    if(collection->capacity <= collection->size) {
        uint64_t capacity = collection->capacity;
        collection->capacity = collection->capacity ? (collection->capacity << 1) : 1;
        collection->container = memory_gen(collection->container, collection->capacity);
        memset(&collection->container[capacity], 0, (collection->capacity - capacity) * sizeof(protocol_context_t *));
    }

    protocol_context_t ** context = &collection->container[collection->size];

    collection->size = collection->size + 1;

    return context;
}
