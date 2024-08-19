/**
 * @file        snorlax/vpn/single/protocol/transmission/control.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 17, 2024
 */

#ifndef   __SNORLAX__VPN_SINGLE_PROTOCOL_TRANSMISSION_CONTROL__H__
#define   __SNORLAX__VPN_SINGLE_PROTOCOL_TRANSMISSION_CONTROL__H__

#include <snorlax/protocol/internet/transmission/control.h>
#include <snorlax/socket/client/event/subscription.h>
#include <snorlax/vpn/client.h>

struct transmission_control_block_agent_single;
struct transmission_control_block_agent_single_func;

typedef struct transmission_control_block_agent_single          transmission_control_block_agent_single_t;
typedef struct transmission_control_block_agent_single_func     transmission_control_block_agent_single_func_t;

struct transmission_control_block_agent_single {
    transmission_control_block_agent_single_func_t * func;
    sync_t * sync;

    ___reference transmission_control_block_t * block;

    vpn_client_t * client;
    socket_client_event_subscription_t * subscription;
};

struct transmission_control_block_agent_single_func {
    transmission_control_block_agent_single_t * (*rem)(transmission_control_block_agent_single_t *);

    int32_t (*open)(transmission_control_block_agent_single_t *);
    int32_t (*send)(transmission_control_block_agent_single_t *);
    int32_t (*recv)(transmission_control_block_agent_single_t *);
    int32_t (*close)(transmission_control_block_agent_single_t *);
};

extern transmission_control_block_agent_single_t * transmission_control_block_agent_single_gen(___notnull transmission_control_block_t * block);

#define transmission_control_block_agent_single_rem(agent)              ((agent)->func->rem(agent))

#define transmission_control_block_agent_single_open(agent)             ((agent)->func->open(agent))
#define transmission_control_block_agent_single_send(agent)             ((agent)->func->send(agent))
#define transmission_control_block_agent_single_recv(agent)             ((agent)->func->recv(agent))
#define transmission_control_block_agent_single_close(agent)            ((agent)->func->close(agent))

extern int32_t transmission_control_protocol_module_func_vpn_single_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

extern socket_client_event_subscription_handler_t * transmission_control_protocol_client_handler_get(void);

#endif // __SNORLAX__VPN_SINGLE_PROTOCOL_TRANSMISSION_CONTROL__H__
