/**
 * @file        snorlax/virtual/private/network/agent/protocol/transmission/control/block.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 25, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_TRANSMISSION_CONTROL_BLOCK__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_TRANSMISSION_CONTROL_BLOCK__H__

#include <snorlax.h>

#include <snorlax/protocol/internet/transmission/control.h>

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block);
extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block);
extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_exception(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block);
extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_complete(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block);
extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_complete_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block);
extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_complete_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block);
extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_none(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block);

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_PROTOCOL_TRANSMISSION_CONTROL_BLOCK__H__
