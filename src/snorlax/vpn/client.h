/**
 * @file        snorlax/vpn/client.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_CLIENT__H__
#define   __SNORLAX__VPN_CLIENT__H__

#include <snorlax.h>

struct vpn_client;
struct vpn_client_func;

typedef struct vpn_client vpn_client_t;
typedef struct vpn_client_func vpn_client_func_t;

struct vpn_client {
    vpn_client_func_t * func;
    sync_t * sync;
};

struct vpn_client_func {
    vpn_client_t * (*rem)(vpn_client_t *);
};

#endif // __SNORLAX__VPN_CLIENT__H__
