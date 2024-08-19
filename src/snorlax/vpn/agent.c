#include "agent.h"

static vpn_agent_t * app = nil;

extern void vpn_agent_set(vpn_agent_t * agent) {
    app = agent;
}

extern vpn_agent_t * vpn_agent_get(void) {
    return app;
}