#include <stdlib.h>

#include "../../protocol.h"

static protocol_module_map_t * protocol_module_map_func_rem(protocol_module_map_t * map);

static protocol_module_map_func_t func = {
    protocol_module_map_func_rem
};

extern protocol_module_map_t * protocol_module_map_gen(protocol_module_t ** modules, uint64_t n, protocol_module_map_get_t get) {
#ifndef   RELEASE
    snorlaxdbg(modules == nil, false, "critical", "");
    snorlaxdbg(n == 0, false, "critical", "");
    snorlaxdbg(get == nil, false, "critical", "");
#endif // RELEASE

    protocol_module_map_t * map = (protocol_module_map_t *) calloc(1, sizeof(protocol_module_map_t));

    map->func = address_of(func);

    map->get = get;
    map->size = n;
    map->modules = calloc(n, sizeof(protocol_module_t *));
    
    for(uint64_t i = 0; i < n; i++) {
        map->modules[i] = modules[i];
    }

    return map;
}

static protocol_module_map_t * protocol_module_map_func_rem(protocol_module_map_t * map) {
#ifndef   RELEASE
    snorlaxdbg(map == nil, false, "critical", "");
#endif // RELEASE

    map->sync = sync_rem(map->sync);

    for(uint64_t i = 0; i < map->size; i++) {
        map->modules[i] = protocol_module_rem(map->modules[i]);
    }

    free(map->modules);

    free(map);

    return nil;
}
