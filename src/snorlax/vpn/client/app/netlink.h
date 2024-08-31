/**
 * @file        snorlax/vpn/client/app/netlink.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_CLIENT_APP_NETLINK__H__
#define   __SNORLAX__VPN_CLIENT_APP_NETLINK__H__

#include <snorlax.h>
#include <snorlax/socket.h>

extern socket_event_subscription_handler_t * vpn_client_app_netlink_event_subscription_handler_get(void);

#endif // __SNORLAX__VPN_CLIENT_APP_NETLINK__H__
