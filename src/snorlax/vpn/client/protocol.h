/**
 * @file        snorlax/vpn/client/protocol.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 10, 2024
 */

#ifndef   __SNORLAX__VPN_CLIENT_PROTOCOL__H__
#define   __SNORLAX__VPN_CLIENT_PROTOCOL__H__

#include <snorlax/protocol.h>

extern void vpn_client_protocol_module_array_init(void);
extern protocol_module_t ** vpn_client_protocol_module_array_transport_get(void);

#endif // __SNORLAX__VPN_CLIENT_PROTOCOL__H__
