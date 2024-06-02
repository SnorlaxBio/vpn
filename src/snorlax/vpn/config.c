/**
 * @file        snorlax/vpn/config.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#include <linux/if_ether.h>

#include "config.h"

static snorlax_vpn_config_t config = {
    .queue = {
        .multi = 0
    },
    .layer = snorlax_vpn_layer_network,
    .packet = false,
    .name = { 0, },
    .txqueuelen = ETH_DATA_LEN
};

extern const snorlax_vpn_config_t * snorlax_vpn_config_get(void) {
    return &config;
}