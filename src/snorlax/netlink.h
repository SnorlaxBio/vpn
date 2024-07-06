/**
 * @file        snorlax/netlink.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 6, 2024
 */

#ifndef   __SNORLAX__NETLINK__H__
#define   __SNORLAX__NETLINK__H__

#include <snorlax.h>

// internet/protocol/route

/**
 * 
 */


extern int32_t netlink_ip_route_add();
extern int32_t netlink_ip_route_del();
extern int32_t netlink_ip_route_default_gateway_set();
extern int32_t netlink_ip_route_default_gateway_del();

// iface up / iface down

extern int32_t netlink_ip_iface_up();
extern int32_t netlink_ip_iface_down();
extern int32_t netlink_ip_route_bypass_set();

// add_bypass_route

#endif // __SNORLAX__NETLINK__H__
