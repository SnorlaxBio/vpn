#include <stdlib.h>
#include <string.h>

#include "../protocol.h"

static protocol_path_t * protocol_path_func_rem(protocol_path_t * path);
static protocol_path_node_t * protocol_path_func_add(protocol_path_t * path, protocol_path_node_t * node, protocol_context_t * context, uint32_t type);

static protocol_path_func_t func = {
    protocol_path_func_rem,
    protocol_path_func_add
};

extern protocol_path_t * protocol_path_gen(protocol_context_t * original, uint32_t type, uint64_t hint) {
#ifndef   RELEASE
    snorlaxdbg(original == nil, false, "critical", "");
#endif // RELEASE

    protocol_path_t * path = (protocol_path_t *) calloc(1, sizeof(protocol_path_t));

    path->func = address_of(func);
    path->size = hint;

    protocol_path_node_t * node = (path->node = (protocol_path_node_t *) malloc(hint));
    protocol_context_t * context = original;

    do {
        path->end = (node = protocol_path_add(path, node, context, type));
    } while(context = original->parent);

    uint64_t n = ((uint64_t) (((uint8_t *) path->end) - ((uint8_t *) path->node))) + sizeof(protocol_path_node_t);

    if(n != path->size) {
        path->node = (protocol_path_node_t *) memory_gen(path->node, (path->size = n));
        path->end = (protocol_path_node_t *) (&((uint8_t *) path->node)[n - sizeof(protocol_path_node_t)]);
    }

    return path;
}

static protocol_path_t * protocol_path_func_rem(protocol_path_t * path) {
#ifndef   RELEASE
    snorlaxdbg(path == nil, false, "critical", "");
#endif // RELEASE

    if(path->node) path->node = memory_rem(path->node);

    path->sync = sync_rem(path->sync);

    free(path);

    return nil;
}

static protocol_path_node_t * protocol_path_func_add(protocol_path_t * path, protocol_path_node_t * node, protocol_context_t * context, uint32_t type) {
#ifndef   RELEASE
    snorlaxdbg(path == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint64_t n = (uint64_t) (((uint8_t *) node) - ((uint8_t *) path->node));

    protocol_module_t * module = context->module;
    uint16_t addrlen = protocol_module_addrlen_get(module);

    if(path->size <= n + (sizeof(protocol_path_node_t) * 2) + addrlen) {
        path->size = n + (sizeof(protocol_path_node_t) * 2) + addrlen;
        path->node = (protocol_path_node_t *) memory_gen(path->node, path->size);
        node = (protocol_path_node_t *) (&((uint8_t *) path->node)[n]);
    }

    node->path = path;
    node->module = module;
    node->length = addrlen;
    memcpy(&((uint8_t *) node)[sizeof(protocol_path_node_t)], protocol_context_addrptr(context, type), addrlen);

    node = (protocol_path_node_t *) (&((uint8_t *) node)[sizeof(protocol_path_node_t) + addrlen]);
    memset(node, 0, sizeof(protocol_path_node_t));

    return node;
}
