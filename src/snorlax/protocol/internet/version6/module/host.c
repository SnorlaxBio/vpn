#include "../../version6.h"
#include "../control/message.h"

typedef internet_protocol_version6_module_host_t * (*internet_protocol_version6_module_host_func_rem_t)(internet_protocol_version6_module_host_t *);
typedef int32_t (*internet_protocol_version6_module_host_func_deserialize_t)(internet_protocol_version6_module_host_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);
typedef int32_t (*internet_protocol_version6_module_host_func_serialize_t)(internet_protocol_version6_module_host_t *, protocol_context_t *, internet_protocol_version6_context_t *, protocol_packet_t **, uint64_t *);
typedef void (*internet_protocol_version6_module_host_func_debug_t)(internet_protocol_version6_module_host_t *, FILE *, internet_protocol_version6_context_t *);
typedef int32_t (*internet_protocol_version6_module_host_func_in_t)(internet_protocol_version6_module_host_t *, protocol_packet_t *, uint64_t, protocol_context_t *, internet_protocol_version6_context_t **);

static int32_t internet_protocol_version6_module_host_func_control_message_context_in_discard(internet_protocol_version6_module_host_t * module, internet_control_message_protocol_version6_context_t * context);
static int32_t internet_protocol_version6_module_host_func_control_message_context_in_router_advertisement(internet_protocol_version6_module_host_t * module, internet_control_message_protocol_version6_context_router_advertisement_t * context);

static internet_protocol_version6_module_host_func_t func = {
    (internet_protocol_version6_module_host_func_rem_t) internet_protocol_version6_module_func_rem,
    (internet_protocol_version6_module_host_func_deserialize_t) internet_protocol_version6_module_func_deserialize,
    (internet_protocol_version6_module_host_func_serialize_t) internet_protocol_version6_module_func_serialize,
    (internet_protocol_version6_module_host_func_debug_t) internet_protocol_version6_module_func_debug,
    (internet_protocol_version6_module_host_func_in_t) internet_protocol_version6_module_func_in,

    internet_protocol_version6_module_host_func_control_message_context_in
};

extern internet_protocol_version6_module_host_t * internet_protocol_version6_module_host_gen(protocol_module_map_t * map, internet_protocol_version6_host_context_handler_t on) {
    internet_protocol_version6_module_host_t * module = (internet_protocol_version6_module_host_t *) calloc(1, sizeof(internet_protocol_version6_module_host_t));

    module->func = address_of(func);
    module->map = map;
    module->on = on;

    return module;
}

extern int32_t internet_protocol_version6_module_host_func_on(internet_protocol_version6_module_host_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context) {
    return success;
}

extern int32_t internet_protocol_version6_module_host_func_control_message_context_in(internet_protocol_version6_module_host_t * module, internet_control_message_protocol_version6_context_t * context) {
    switch(internet_control_message_protocol_version6_context_type_get(context)) {
        case internet_control_message_protocol_version6_type_router_solicitation:       return internet_protocol_version6_module_host_func_control_message_context_in_discard(module, context);
        case internet_control_message_protocol_version6_type_router_advertisement:      return internet_protocol_version6_module_host_func_control_message_context_in_router_advertisement(module, (internet_control_message_protocol_version6_context_router_advertisement_t *) context);
    }
    return success;
}

static int32_t internet_protocol_version6_module_host_func_control_message_context_in_discard(internet_protocol_version6_module_host_t * module, internet_control_message_protocol_version6_context_t * context) {
    return success;
}

static int32_t internet_protocol_version6_module_host_func_control_message_context_in_router_advertisement(internet_protocol_version6_module_host_t * module, internet_control_message_protocol_version6_context_router_advertisement_t * context) {
    /**
     * [6.3.4. Processing Received Router Advertisements](https://datatracker.ietf.org/doc/html/rfc4861#section-6.3.4)
     */

    snorlaxdbg(true, false, "implement", "");

#if       0
    if(internet_control_message_protocol_version6_context_router_advertisement_current_hop_limit_get(context)) {
        module->current_hop_limit = internet_control_message_protocol_version6_context_router_advertisement_current_hop_limit_get(context); 
    }

    hashtable_node_key_t key = {};

    router_t * router = (router_t *) hashtable_get(module->default_router_table, &key);

    if(router == nil) {
    }
#endif // 0

    return success;
}
