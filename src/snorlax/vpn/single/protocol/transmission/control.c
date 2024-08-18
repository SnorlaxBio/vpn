#include <arpa/inet.h>

#include "control.h"

#include "../../app.h"

extern int32_t transmission_control_protocol_module_func_vpn_single_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    snorlaxdbg(false, true, "debug", "");
    if(transmission_control_protocol_context_key_has(context)) {
        if(transmission_control_protocol_module_blockon(module, type, parent, context) == fail) {
            snorlaxdbg(true, false, "check", "");
        }

        snorlaxdbg(context->block, false, "check", "");

        uint8_t version = internet_protocol_context_version_get(context->parent);

        if(context->block->agent == nil) {
            snorlaxdbg(transmission_control_block_state_get(context->block) != transmission_control_state_syn_sent, false, "critical", "");

            char str[128];

            snorlaxdbg(false, true, "debug", "source: %s:%u", internet_protocol_address_to_string(version, str, internet_protocol_context_source_get(context->parent)), transmission_control_protocol_context_source_get(context));
            snorlaxdbg(false, true, "debug", "destination: %s:%u", internet_protocol_address_to_string(version, str, internet_protocol_context_destination_get(context->parent)), transmission_control_protocol_context_destination_get(context));

            transmission_control_block_agent_single_t * agent = transmission_control_block_agent_single_gen(context->block);
            context->block->agent = (transmission_control_block_agent_t *) agent;

            snorlaxdbg(agent == nil, false, "critical", "");

            vpn_single_app_t * app = vpn_single_app_get();

            snorlaxdbg(app == nil, false, "critical", "");

//            agent->client = socket_client_tcp_version6_gen();

            // agent->client = socket_client_gen(A)
        }
    } else {
        snorlaxdbg(false, true, "debug", "");
    }

    return success;
}