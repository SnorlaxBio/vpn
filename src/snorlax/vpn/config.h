/**
 * @file        snorlax/vpn/config.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 * 
 * Config 는 싱글톤이어야 한다.
 * 사용자 라이브러리에 노출되어서는 안된다.
 */

#ifndef   __SNORLAX__VPN_CONFIG__H__
#define   __SNORLAX__VPN_CONFIG__H__

#include <stdio.h>
#include <stdint.h>

#include <net/if.h>

#include <snorlax.h>

#define snorlax_vpn_layer_datalink          1   // TAP
#define snorlax_vpn_layer_network           2   // TUN

struct snorlax_vpn_config {
    struct {
        uint8_t multi;
    } queue;
    uint8_t layer;
    uint8_t packet;             // PROVIDE PACKET INFORMATION
    char name[IFNAMSIZ];        // PACKET NAME
    int txqueuelen;
};

typedef struct snorlax_vpn_config snorlax_vpn_config_t;

extern const snorlax_vpn_config_t * snorlax_vpn_config_get(void);

#endif // __SNORLAX__VPN_CONFIG__H__
