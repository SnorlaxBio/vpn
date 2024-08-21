#include <stdlib.h>
#include <string.h>

#include "../protocol.h"

static protocol_path_t * protocol_path_func_rem(protocol_path_t * path);
static protocol_path_node_t * protocol_path_func_add(protocol_path_t * path, protocol_path_node_t * node, protocol_context_t * context);
static void protocol_path_func_debug(protocol_path_t * path, FILE * stream);

static protocol_path_func_t func = {
    protocol_path_func_rem,
    protocol_path_func_debug,
    protocol_path_func_add
};

extern protocol_path_t * protocol_path_gen(protocol_context_t * original, uint64_t hint) {
#ifndef   RELEASE
    snorlaxdbg(original == nil, false, "critical", "");
#endif // RELEASE

    protocol_path_t * path = (protocol_path_t *) calloc(1, sizeof(protocol_path_t));

    path->func = address_of(func);
    path->size = hint;

    protocol_path_node_t * node = (path->node = (protocol_path_node_t *) malloc(hint));
    protocol_context_t * context = original;

    do {
        path->end = (node = protocol_path_add(path, node, context));
    } while(context = context->parent);

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

static protocol_path_node_t * protocol_path_func_add(protocol_path_t * path, protocol_path_node_t * node, protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(path == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    uint64_t n = (uint64_t) (((uint8_t *) node) - ((uint8_t *) path->node));

    protocol_module_t * module = context->module;
    uint16_t addrlen = protocol_module_addrlen_get(module);

    if(path->size <= n + ((sizeof(protocol_path_node_t) + addrlen) * 2)) {
        path->size = n + ((sizeof(protocol_path_node_t) + addrlen) * 2);
        path->node = (protocol_path_node_t *) memory_gen(path->node, path->size);
        node = (protocol_path_node_t *) (&((uint8_t *) path->node)[n]);
    }

    node->path = path;
    node->module = module;
    node->length = addrlen;
    if(addrlen) {
        memcpy(&((uint8_t *) node)[sizeof(protocol_path_node_t)], protocol_context_addrptr(context, protocol_address_type_source), addrlen);
        memcpy(&((uint8_t *) node)[sizeof(protocol_path_node_t) + addrlen], protocol_context_addrptr(context, protocol_address_type_destination), addrlen);
    }

    node = (protocol_path_node_t *) (&((uint8_t *) node)[sizeof(protocol_path_node_t) + (addrlen * 2)]);
    memset(node, 0, sizeof(protocol_path_node_t));

    return node;
}

static void protocol_path_func_debug(protocol_path_t * path, FILE * stream) {
#ifndef   RELEASE
    snorlaxdbg(path == nil, false, "critical", "");
#endif // RELEASE

    char str[256];
    fprintf(stream, "| protocol path |\n");
    for(protocol_path_node_t * node = protocol_path_begin(path); node != protocol_path_end(path); node = protocol_path_node_next(node)) {
        fprintf(stream, "| %u ", node->length);
        fprintf(stream, "| %p ", node->module);
        fprintf(stream, "| %p ", node->path);
        fprintf(stream, "| %s ", protocol_address_to_hexadecimalstr(str, protocol_path_node_source_get(node), node->length));
        fprintf(stream, "| %s ", protocol_address_to_hexadecimalstr(str, protocol_path_node_destination_get(node), node->length));
        fprintf(stream, "|\n");
    }
}
