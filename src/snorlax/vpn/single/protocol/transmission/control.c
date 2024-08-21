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

                uint8_t buffer[protocol_packet_max];

                

                // snorlaxdbg(true, false, "implement", "");

                // if(transmission_control_protocol_module_out(module, transmission_control_protocol_context_gen_fake_connect_synack(context->block, buffer + protocol_packet_max, protocol_packet_max), context->block->modulepath, 0) == fail) {
                //     snorlaxdbg(false, true, "debug", "fail");
                // }

                // transmission_control_protocol_context_t * ctx = transmssion_control_block_context_gen_fake_connect_synack(context->block, buffer + protocol_packet_max, protocol_packet_max);



                // 앞으로 패킷을 생성하면서 간다.

                // MODULE PATH ,... 

                // 어떻게 DESTINATION 으로 보낼까?

                /**
                 * 지금 구조는 너무 많이 밀접하게 묶여 있다.
                 * 느슨한 연결이 필요한가?
                 * l
                 */

                /**
                 * PROTOCOL IN > .... > OUT PROTOCOL
                 * FAST CONNECT ?
                 */

                // transmission_control_protocol_module
                /**
                 * 현 구조에서 외부에서 나가는 패킷을 어떻게 구조화할까?
                 * 
                 * TUN MODULE 로 나간다.... 
                 */
                // protocol_packet_t packet[protocol_packet_max];
                // uint64_t packetlen = 0;
                // transmission_control_protocol_context_t * transmission = transmission_control_protocol_context_gen_reversal(context, packet, protocol_packet_max);
                // internet_protocol_context_t * internet = internet_protocol_context_gen_reversal(context->parent, transmission);
                // 보다 좋은 방법을 찾아 보자.
                // if(transmission_control_protocol_module_out(module, context->parent, , &packet, &packetlen) == success) {
                // }
                // transmission_control_protocol_context_t * 
                // transmission_control_blcok_agent_open
                /**
                 * 외부로부터 RCV SYN 이라고 판단한다.
                 */

                // transmission_control_protocol_context_t * response = transmission_control_protocol_context_gen_connect_synack(context->module, context->block);
                // transmission_control_block_context_gen_fake_connect_rcv_synack(context->block, context);
                // internet_protocol_context_t * response2 = internet_protocol_context_gen_reversal(context->parent->module, context->parent, (protocol_context_t *) transmission_control_protocol_context_gen_connect_synack(context->module, context->block));
            }

            

            // uint8_t version = internet_protocol_context_version_get(context->parent);

            // if(context->block->agent == nil) {
            //     snorlaxdbg(transmission_control_block_state_get(context->block) != transmission_control_state_syn_sent, false, "critical", "");

            //     char str[128];

            //     snorlaxdbg(false, true, "debug", "source: %s:%u", internet_protocol_address_to_string(version, str, internet_protocol_context_source_get(context->parent)), transmission_control_protocol_context_source_get(context));
            //     snorlaxdbg(false, true, "debug", "destination: %s:%u", internet_protocol_address_to_string(version, str, internet_protocol_context_destination_get(context->parent)), transmission_control_protocol_context_destination_get(context));

            //     transmission_control_block_agent_single_t * agent = transmission_control_block_agent_single_gen(context->block);
            //     context->block->agent = (transmission_control_block_agent_t *) agent;

            //     snorlaxdbg(agent == nil, false, "critical", "");

            //     vpn_single_app_t * app = vpn_single_app_get();

            //     snorlaxdbg(app == nil, false, "critical", "");

            //     event_engine_t * engine = app->engine;

            //     uint8_t * addr = internet_protocol_context_destination_get(context->parent);
            //     uint16_t port = transmission_control_protocol_context_destination_get(context);
            //     agent->client = (version == 4 ? vpn_client_tcp4_gen(ntohs(*((uint32_t *) addr)), port) : vpn_client_tcp6_gen(addr, port));
            //     agent->subscription = event_engine_socket_client_sub(engine, (socket_client_t *) agent->client, transmission_control_protocol_client_handler_get(), nil, (event_subscription_meta_t *) agent);

            //     /**
            //      * 싱글 VPN 에서 소켓을 이벤트 엔진에 등록하고 나면 SYNC
            //      */

            //     // transmission_control_block_

            //     // transmission_control_block_gen_connect_synack()

            //     // transmission_control_protocol_module_reply(module, context);

            //     // internet_protocol_packet_t buffer[2048];

            //     // memset(buffer, 0, sizeof(buffer));

            //     // internet_protocol_packet_t * datagram = internet_protocol_packet_build(buffer, 2048, version, internet_protocol_context_destination_get(context->parent), internet_protocol_context_source_get(context->parent));
            //     // {
            //     //     internet_protocol_context_t * parent = internet_protocol_context_build(version, internet_protocol_context_destination_get(context->parent), internet_protocol_context_source_get(context->parent));
            //     // }
            //     // transmission_control_protocol_context_t * transmission_control_protocol_context_build_connect_synack();
            //     // transmission_control_protocol_module_out
            //     // internet_protocol_context_t * parent = internet_protocol_context_get();
            //     // transmission_control_protocol_context_gen(module, )
            //     // 상태를 SYN RECEIVED 로 변경한다.
            //     snorlaxdbg(false, true, "debug", "");
            // } else {
            //     // TODO: CHECK THIS LOGIC
            // }
        } else {
            snorlaxdbg(false, true, "debug", "");
        }
    }
    

    return success;
}