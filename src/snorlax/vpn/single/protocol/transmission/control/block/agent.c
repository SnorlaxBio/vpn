#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "../../control.h"

static transmission_control_block_agent_single_t * transmission_control_block_agent_single_func_rem(transmission_control_block_agent_single_t * agent);

static int32_t transmission_control_block_agent_single_func_open(transmission_control_block_agent_single_t * agent);
static int32_t transmission_control_block_agent_single_func_send(transmission_control_block_agent_single_t * agent, uint8_t * data, uint64_t datalen);
static int32_t transmission_control_block_agent_single_func_recv(transmission_control_block_agent_single_t * agent);
static int32_t transmission_control_block_agent_single_func_close(transmission_control_block_agent_single_t * agent);

static transmission_control_block_agent_single_func_t func = {
    transmission_control_block_agent_single_func_rem,
    transmission_control_block_agent_single_func_open,
    transmission_control_block_agent_single_func_send,
    transmission_control_block_agent_single_func_recv,
    transmission_control_block_agent_single_func_close
};

extern transmission_control_block_agent_single_t * transmission_control_block_agent_single_gen(___notnull transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_agent_single_t * agent = (transmission_control_block_agent_single_t *) calloc(1, sizeof(transmission_control_block_agent_single_t));

    agent->func = address_of(func);

    agent->block = block;

    // uint8_t version = internet_protocol_context_version_get(context->parent);

    // snorlaxdbg(version != 4 && version != 6, false, "critical", "");

    // uint8_t * addr = internet_protocol_context_destination_get(context->parent);
    // uint16_t port = transmission_control_protocol_context_destination_get(context);

    // agent->client = (version == 4 ? vpn_client_tcp4_gen(*((uint32_t *) addr), port) : vpn_client_tcp6_gen(addr, port));


    //
    //         uint16_t port = transmission_control_protocol_context_destination_get(context);
    //         agent->client = (version == 4 ? vpn_client_tcp4_gen(*((uint32_t *) addr), port) : vpn_client_tcp6_gen(addr, port));

    return agent;
}

static transmission_control_block_agent_single_t * transmission_control_block_agent_single_func_rem(transmission_control_block_agent_single_t * agent) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    agent->sync = sync_rem(agent->sync);

    free(agent);

    return nil;
}

static int32_t transmission_control_block_agent_single_func_open(transmission_control_block_agent_single_t * agent) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    if(agent->client == nil) {
        uint8_t version = agent->block->version;

        protocol_path_node_t * port = protocol_path_begin(agent->block->path);
        protocol_path_node_t * addr = protocol_path_node_next(port);

        snorlaxdbg(false, true, "debug", "agent open port => %u", ntohs(uint16_of(protocol_path_node_source_get(port))));

        agent->clinet = version == 4 ? socket_client_tcp4_gen() : socket_client_tcp6_gen();
    }



    

    
    // snorlaxdbg(false, true, "debug", )

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t transmission_control_block_agent_single_func_send(transmission_control_block_agent_single_t * agent, uint8_t * data, uint64_t datalen) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "send");

    return socket_client_event_subscription_write(agent->subscription, data, datalen);
}

static int32_t transmission_control_block_agent_single_func_recv(transmission_control_block_agent_single_t * agent) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t transmission_control_block_agent_single_func_close(transmission_control_block_agent_single_t * agent) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}
