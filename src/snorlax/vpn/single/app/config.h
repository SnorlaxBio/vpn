/**
 * @file        snorlax/vpn/single/app/config.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 15, 2024
 */

#ifndef   __SNORLAX__VPN_SINGLE_APP_CONFIG__H__
#define   __SNORLAX__VPN_SINGLE_APP_CONFIG__H__

#include <snorlax.h>

struct vpn_single_app_config;

typedef struct vpn_single_app_config vpn_single_app_config_t;

struct vpn_single_app_config {
    int32_t dummy;
};

extern const vpn_single_app_config_t * vpn_single_app_config_get(void);

#endif // __SNORLAX__VPN_SINGLE_APP_CONFIG__H__
