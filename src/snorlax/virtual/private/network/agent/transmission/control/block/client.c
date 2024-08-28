#include "client.h"

static void transmission_control_block_agent_event_type_subscription_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_open_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_read_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_write_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_close_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_exception_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_in_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_out_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);
static void transmission_control_block_agent_event_type_none_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node);

extern void virtual_private_network_agent_transmission_control_block_client_on(transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    switch(type) {
        case transmission_control_block_agent_event_type_subscription:  transmission_control_block_agent_event_type_subscription_on(agent, type, node);     break;
        case transmission_control_block_agent_event_type_open:          transmission_control_block_agent_event_type_open_on(agent, type, node);             break;
        case transmission_control_block_agent_event_type_read:          transmission_control_block_agent_event_type_read_on(agent, type, node);             break;
        case transmission_control_block_agent_event_type_write:         transmission_control_block_agent_event_type_write_on(agent, type, node);            break;
        case transmission_control_block_agent_event_type_close:         transmission_control_block_agent_event_type_close_on(agent, type, node);            break;
        case transmission_control_block_agent_event_type_exception:     transmission_control_block_agent_event_type_exception_on(agent, type, node);        break;
        case transmission_control_block_agent_event_type_in:            transmission_control_block_agent_event_type_in_on(agent, type, node);               break;
        case transmission_control_block_agent_event_type_out:           transmission_control_block_agent_event_type_out_on(agent, type, node);              break;
        default:                                                        transmission_control_block_agent_event_type_none_on(agent, type, node);             break;
    }
}

static void transmission_control_block_agent_event_type_subscription_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_open_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "debug", "");
    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_read_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_write_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_close_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_exception_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_in_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_out_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void transmission_control_block_agent_event_type_none_on(___notnull transmission_control_block_client_t * agent, uint32_t type, void * node) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}
