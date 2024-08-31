/**
 * @file        snorlax/vpn/agent.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 19, 2024
 */

#ifndef   __SNORLAX__VPN_AGENT__H__
#define   __SNORLAX__VPN_AGENT__H__

#include <snorlax.h>
#include <snorlax/event/engine.h>

struct vpn_agent;
struct vpn_agent_func;

typedef struct vpn_agent vpn_agent_t;
typedef struct vpn_agent_func vpn_agent_func_t;

struct vpn_agent {
    vpn_agent_func_t * func;
    sync_t * sync;
    event_engine_t * engine;

    descriptor_event_subscription_t * tun;
    socket_event_subscription_t * netlink;
};

struct vpn_agent_func {
    vpn_agent_t * (*rem)(vpn_agent_t *);
    int32_t (*on)(vpn_agent_t *);
    int32_t (*off)(vpn_agent_t *);
    int32_t (*run)(vpn_agent_t *);
};

extern void vpn_agent_set(vpn_agent_t * agent);
extern vpn_agent_t * vpn_agent_get(void);

#endif // __SNORLAX__VPN_AGENT__H__
