#include <arpa/inet.h>

#include "control.h"

#include "../../app.h"
#include "../../../client.h"

extern int32_t transmission_control_protocol_module_func_vpn_single_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    snorlaxdbg(false, true, "debug", "");
    if(type == protocol_event_in) {
        if(transmission_control_protocol_context_key_has(context)) {
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
            }

            if(transmission_control_block_state_get(context->block) == transmission_control_state_syn_sent) {
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
        } else {
            snorlaxdbg(false, true, "debug", "");
        }
    } else if(type == protocol_event_complete_in) {

    } else if(type == protocol_event_out) {

    } else if(type == protocol_event_complete_out) {
        
    }
    

    return success;
}