/**
 * @file        snorlax/vpn/client/app/tun.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_CLIENT_APP_TUN__H__
#define   __SNORLAX__VPN_CLIENT_APP_TUN__H__

#include <snorlax.h>
#include <snorlax/descriptor.h>

extern descriptor_event_subscription_handler_t * vpn_client_app_tun_event_subscription_handler_get(void);

#endif // __SNORLAX__VPN_CLIENT_APP_TUN__H__
