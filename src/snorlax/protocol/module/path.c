#include "../../protocol.h"

static protocol_module_path_func_t func = {
    protocol_module_path_func_rem
};

extern protocol_module_path_t * protocol_module_path_gen(protocol_context_t * context, uint64_t hint) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    protocol_module_path_t * path = (protocol_module_path_t *) calloc(1, sizeof(protocol_module_path_t));

    path->func = address_of(func);

    path->size = hint;

    path->container = calloc(hint, sizeof(protocol_module_t *));

    uint64_t index = 0;

    path->container[index] = context->module;

    protocol_context_t * o = context->parent;

    while(o) {
        index = index + 1;
        if(path->size <= index) {
            path->size = index + 1;
            path->container = (protocol_module_t **) memory_gen(path->container, (path->size) * sizeof(protocol_module_t *));
        }
        path->container[index] = o->module;

        o = o->parent;
    }

    if(path->size != index + 1) {
        path->size = index + 1;
        path->container = (protocol_module_t **) memory_gen(path->container, path->size * sizeof(protocol_module_t *));
    }

    return path;
}

extern protocol_module_path_t * protocol_module_path_func_rem(protocol_module_path_t * path) {
#ifndef   RELEASE
    snorlaxdbg(path == nil, false, "critical", "");
#endif // RELEASE

    if(path->container) path->container = memory_rem(path->container);

    path->sync = sync_rem(path->sync);

    free(path);

    return path;
}
