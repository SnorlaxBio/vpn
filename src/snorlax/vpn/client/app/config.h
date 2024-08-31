/**
 * @file        snorlax/vpn/client/app/config.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       July 23, 2024
 */

#ifndef   __SNORLAX__VPN_CLIENT_APP_CONFIG__H__
#define   __SNORLAX__VPN_CLIENT_APP_CONFIG__H__

#include <snorlax.h>

struct vpn_client_app_config;

typedef struct vpn_client_app_config vpn_client_app_config_t;

struct vpn_client_app_config {
    int32_t client_pool_size;
};

extern const vpn_client_app_config_t * vpn_client_app_config_get(void);

#endif // __SNORLAX__VPN_CLIENT_APP_CONFIG__H__
