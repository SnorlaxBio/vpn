#include <stdlib.h>

#include "../../protocol.h"

static protocol_address_path_t * protocol_address_path_func_rem(protocol_address_path_t * path);

static protocol_address_path_func_t func = {
    protocol_address_path_func_rem
};

extern protocol_address_path_t * protocol_address_path_gen(protocol_context_t * original, uint32_t type, uint64_t hint) {
#ifndef   RELEASE
    snorlaxdbg(original == nil, false, "critical", "");
#endif // RELEASE

    protocol_address_path_t * path = (protocol_address_path_t *) calloc(1, sizeof(protocol_address_path_t));

    path->func = address_of(func);
    path->size = hint;

    path->container = (protocol_address_node_t *) calloc(1, path->size);

    protocol_address_node_set(path->container, protocol_context_addrptr(original, type), protocol_module_addrlen_get(original->module));

    protocol_context_t * context = original->parent;
    uint64_t total = path->container->len + sizeof(uint16_t);

    protocol_address_node_t * next = protocol_address_node_next(path->container);

    while(context) {
        uint16_t len = protocol_module_addrlen_get(context->module);
        if(path->size < total + len + sizeof(uint16_t)) {
            path->size = total + len + sizeof(uint16_t);
            path->container = (protocol_address_node_t *) memory_gen(path->container, path->size);
            next = (protocol_address_node_t *) (&(((uint8_t *) path->container)[total]));
        }
        protocol_address_node_set(next, protocol_context_addrptr(context, type), len);
        total = total + next->len + sizeof(uint16_t);
        next = protocol_address_node_next(path->container);
        context = context->parent;
    }

    if(path->size != total) {
        path->size = total;
        path->container = (protocol_address_node_t *) memory_gen(path->container, path->size);
    }

    return path;
}

static protocol_address_path_t * protocol_address_path_func_rem(protocol_address_path_t * path) {
#ifndef   RELEASE
    snorlaxdbg(path == nil, false, "critical", "");
#endif // RELEASE

    path->container = memory_rem(path->container);

    path->sync = sync_rem(path->sync);

    free(path);

    return nil;
}
