/**
 * @file        snorlax/virtual/private/network/agent/transmission/control/block/client.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 25, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_TRANSMISSION_CONTROL_BLOCK_CLIENT__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_TRANSMISSION_CONTROL_BLOCK_CLIENT__H__

// #include <snorlax/socket/client/event/subscription.h>

#include <snorlax/protocol/internet/transmission/control.h>

extern void virtual_private_network_agent_transmission_control_block_client_on(transmission_control_block_client_t * agent, uint32_t type, void * node);

// extern transmission_control_block_client_handler_t * virtual_private_network_agent_transmission_control_block_client_handler_get(void);

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_TRANSMISSION_CONTROL_BLOCK_CLIENT__H__