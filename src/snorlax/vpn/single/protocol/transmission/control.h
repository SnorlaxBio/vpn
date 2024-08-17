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

extern int32_t transmission_control_protocol_module_func_vpn_single_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

#endif // __SNORLAX__VPN_SINGLE_PROTOCOL_TRANSMISSION_CONTROL__H__
