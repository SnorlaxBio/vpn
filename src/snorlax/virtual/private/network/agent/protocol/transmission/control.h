/**
 * @file        snorlax/virtual/private/network/agent/protocol/transmission/control.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 25, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_TRANSMISSION_CONTROL__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_TRANSMISSION_CONTROL__H__

#include <snorlax.h>

#include <snorlax/protocol/internet/transmission/control.h>

extern int32_t virtual_private_network_agent_transmission_control_protocol_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_TRANSMISSION_CONTROL__H__
