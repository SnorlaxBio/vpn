#include <stdlib.h>

#include "map.h"

static protocol_module_map_t * protocol_module_map_func_rem(protocol_module_map_t * map);
static protocol_module_t * protocol_module_map_func_get(protocol_module_map_t * map, uint32_t no);

static protocol_module_map_func_t func = {
    protocol_module_map_func_rem,
    protocol_module_map_func_get
};

extern protocol_module_map_t * protocol_module_map_gen(protocol_module_t ** modules, uint64_t n, protocol_module_map_index_t index) {
#ifndef   RELEASE
    snorlaxdbg(modules == nil, false, "critical", "");
    snorlaxdbg(n == 0, false, "critical", "");
    snorlaxdbg(index == nil, false, "critical", "");
#endif // RELEASE

    protocol_module_map_t * map = (protocol_module_map_t *) calloc(1, sizeof(protocol_module_map_t));

    map->func = address_of(func);

    map->index = index;
    map->modules = modules;
    map->size = n;

    return map;
}

static protocol_module_map_t * protocol_module_map_func_rem(protocol_module_map_t * map) {
#ifndef   RELEASE
    snorlaxdbg(map == nil, false, "critical", "");
#endif // RELEASE

    map->sync = sync_rem(map->sync);

    free(map->modules);

    free(map);

    return nil;
}

static protocol_module_t * protocol_module_map_func_get(protocol_module_map_t * map, uint32_t no) {
#ifndef   RELEASE
    snorlaxdbg(map == nil, false, "critical", "");
#endif // RELEASE

    uint32_t index = map->index(no);

    return index < map->size ? map->modules[index] : nil;
}
