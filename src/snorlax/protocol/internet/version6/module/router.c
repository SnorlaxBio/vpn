#include "../../version6.h"

typedef internet_protocol_version6_module_router_t * (*internet_protocol_version6_module_router_func_rem_t)(internet_protocol_version6_module_router_t *);
typedef int32_t (*internet_protocol_version6_module_router_func_deserialize_t)(internet_protocol_version6_module_router_t *, protocol_packet_t *, uint32_t, protocol_context_t *, internet_protocol_version6_context_t **);
typedef int32_t (*internet_protocol_version6_module_router_func_serialize_t)(internet_protocol_version6_module_router_t *, protocol_context_t *, internet_protocol_version6_context_t *, protocol_packet_t **, uint32_t *);
typedef void (*internet_protocol_version6_module_router_func_debug_t)(internet_protocol_version6_module_router_t *, FILE *, internet_protocol_version6_context_t *);

static internet_protocol_version6_module_router_func_t func = {
    (internet_protocol_version6_module_router_func_rem_t) internet_protocol_version6_module_func_rem,
    (internet_protocol_version6_module_router_func_deserialize_t) internet_protocol_version6_module_func_deserialize,
    (internet_protocol_version6_module_router_func_serialize_t) internet_protocol_version6_module_func_serialize,
    (internet_protocol_version6_module_router_func_debug_t) internet_protocol_version6_module_func_debug
};

extern internet_protocol_version6_module_router_t * internet_protocol_version6_module_router_gen(protocol_module_map_t * map) {
    internet_protocol_version6_module_router_t * module = (internet_protocol_version6_module_router_t *) calloc(1, sizeof(internet_protocol_version6_module_router_t));

    module->func = address_of(func);
    module->map = map;

    return module;
}
