/**
 * @file        snorlax/vpn/single/app/netlink.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 15, 2024
 * 
 * @deprecated
 * 
 * 공통 모듈로 빼자.. NET 프로젝트로 이동
 */

#ifndef   __SNORLAX__VPN_SINGLE_APP_NETLINK__H__
#define   __SNORLAX__VPN_SINGLE_APP_NETLINK__H__

#include <snorlax/socket.h>

extern socket_event_subscription_handler_t * vpn_single_app_netlink_event_subscription_handler_get(void);

#endif // __SNORLAX__VPN_SINGLE_APP_NETLINK__H__
