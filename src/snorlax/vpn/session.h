/**
 * @file        snorlax/vpn/session.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_SESSION__H__
#define   __SNORLAX__VPN_SESSION__H__

#include <snorlax/socket/session.h>

extern socket_session_event_subscription_handler_t * vpn_session_event_subscription_handler_get(void);

#endif // __SNORLAX__VPN_SESSION__H__
