/**
 * @file        snorlax/vpn/server.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_SERVER__H__
#define   __SNORLAX__VPN_SERVER__H__

#include <snorlax/socket/server.h>

extern socket_server_event_subscription_handler_t * vpn_server_event_subscription_handler_get(void);

#endif // __SNORLAX__VPN_SERVER__H__
