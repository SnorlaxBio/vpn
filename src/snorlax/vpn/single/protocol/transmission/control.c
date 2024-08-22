#include <arpa/inet.h>

#include "control.h"

#include "../../app.h"
#include "../../../client.h"

static int32_t transmission_control__protocol_module_func_vpn_single_on_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t transmission_control__protocol_module_func_vpn_single_on_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t transmission_control__protocol_module_func_vpn_single_on_exception(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t transmission_control__protocol_module_func_vpn_single_on_complete(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t transmission_control__protocol_module_func_vpn_single_on_complete_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t transmission_control__protocol_module_func_vpn_single_on_complete_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t transmission_control__protocol_module_func_vpn_single_on_default(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

extern int32_t transmission_control_protocol_module_func_vpn_single_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    switch(type) {
        case protocol_event_in:             return transmission_control__protocol_module_func_vpn_single_on_in(module, type, parent, context);
        case protocol_event_out:            return transmission_control__protocol_module_func_vpn_single_on_out(module, type, parent, context);
        case protocol_event_exception:      return transmission_control__protocol_module_func_vpn_single_on_exception(module, type, parent, context);
        case protocol_event_complete:       return transmission_control__protocol_module_func_vpn_single_on_complete(module, type, parent, context);
        case protocol_event_complete_in:    return transmission_control__protocol_module_func_vpn_single_on_complete_in(module, type, parent, context);
        case protocol_event_complete_out:   return transmission_control__protocol_module_func_vpn_single_on_complete_out(module, type, parent, context);
        default:                            return transmission_control__protocol_module_func_vpn_single_on_default(module, type, parent, context);
    }
}

static int32_t transmission_control__protocol_module_func_vpn_single_on_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    snorlaxdbg(transmission_control_protocol_context_key_has(context) == false, false, "critical", "");

    if(transmission_control_protocol_module_blockon(module, type, parent, context) == fail) {
        snorlaxdbg(true, false, "check", "");
    }

    snorlaxdbg(context->block == nil, false, "check", "");

    uint8_t version = internet_protocol_context_version_get(context->parent);
    transmission_control_block_agent_single_t * agent = (transmission_control_block_agent_single_t *) (context->block->agent);

    if(context->block->agent == nil) {
        char str[128];

        snorlaxdbg(false, true, "debug", "source: %s:%u", internet_protocol_address_to_string(version, str, internet_protocol_context_source_get(context->parent)), transmission_control_protocol_context_source_get(context));
        snorlaxdbg(false, true, "debug", "destination: %s:%u", internet_protocol_address_to_string(version, str, internet_protocol_context_destination_get(context->parent)), transmission_control_protocol_context_destination_get(context));

        context->block->agent = (transmission_control_block_agent_t *) (agent = transmission_control_block_agent_single_gen(context->block));

        if(transmission_control_block_state_get(context->block) == transmission_control_state_syn_rcvd) {
            vpn_single_app_t * app = vpn_single_app_get();
            event_engine_t * engine = app->engine;

            if(agent->client == nil) {
                uint8_t * addr = internet_protocol_context_destination_get(context->parent);
                uint16_t port = transmission_control_protocol_context_destination_get(context);

                agent->client = (version == 4 ? vpn_client_tcp4_gen(ntohs(*((uint32_t *) addr)), port) : vpn_client_tcp6_gen(addr, port));
            }

            if(agent->subscription == nil) {
                agent->subscription = event_engine_socket_client_sub(engine, (socket_client_t *) agent->client, transmission_control_protocol_client_handler_get(), nil, (event_subscription_meta_t *) agent);
            }
        }
    }

    return success;
}

static int32_t transmission_control__protocol_module_func_vpn_single_on_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
    return success;
}

static int32_t transmission_control__protocol_module_func_vpn_single_on_exception(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
    return success;
}

static int32_t transmission_control__protocol_module_func_vpn_single_on_complete(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
    return success;
}

static int32_t transmission_control__protocol_module_func_vpn_single_on_complete_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    snorlaxdbg(transmission_control_protocol_context_key_has(context) == false, false, "critical", "");

    if(transmission_control_protocol_module_blockon(module, type, parent, context) == fail) {
        snorlaxdbg(true, false, "check", "");
    }

    // if(transmission_control_block_state_get(context->block) == transmission_control_state_syn_rcvd) {

    // }
    return success;
}

static int32_t transmission_control__protocol_module_func_vpn_single_on_complete_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
    return success;
}

static int32_t transmission_control__protocol_module_func_vpn_single_on_default(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "type => %u", type);

    return success;
}
