/**
 * @file        snorlax/virtual/private/network/agent/protocol/user/datagram.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 25, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_USER_DATAGRAM__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_USER_DATAGRAM__H__

#include <snorlax.h>

#include <snorlax/protocol/internet/user/datagram.h>

extern int32_t virtual_private_network_agent_user_datagram_protocol_on(user_datagram_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, user_datagram_protocol_context_t * context);

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_USER_DATAGRAM__H__
