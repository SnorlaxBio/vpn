/**
 * @file        snorlax/vpn/single/internet.h
 * @brief       
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 22, 2024
 */

#ifndef   __SNORLAX__VPN_SINGLE_INTERNET__H__
#define   __SNORLAX__VPN_SINGLE_INTERNET__H__

#include <snorlax/protocol/internet.h>

extern int32_t internet_protocol_module_func_vpn_single_on(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);

#endif // __SNORLAX__VPN_SINGLE_INTERNET__H__