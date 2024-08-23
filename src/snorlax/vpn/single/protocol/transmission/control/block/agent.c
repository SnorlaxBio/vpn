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
    transmission_control_block_agent_single_t * agent = (transmission_control_block_agent_single_t *) calloc(1, sizeof(transmission_control_block_agent_single_t));

    agent->func = address_of(func);

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
