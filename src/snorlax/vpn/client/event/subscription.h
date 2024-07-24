/**
 * @file        snorlax/vpn/client/subscription.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 23, 2024
 */


#ifndef   __SNORLAX__VPN_CLIENT_EVENT_SUBSCRIPTION__H__
#define   __SNORLAX__VPN_CLIENT_EVENT_SUBSCRIPTION__H__

#include <snorlax/descriptor/event/type.h>
#include <snorlax/socket/client/event/subscription.h>

extern socket_client_event_subscription_handler_t * vpn_client_subscription_handler_get(void);

#endif // __SNORLAX__VPN_CLIENT_EVENT_SUBSCRIPTION__H__

