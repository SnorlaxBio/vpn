/**
 * @file        snorlax/vpn.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#include <unistd.h>

#include "vpn.h"

#include "vpn/tuntap.h"
#include "vpn/config.h"

#include "eva.h"

extern int snorlax_vpn_run(void) {
    int ret = success;
    
    if((ret = snorlax_vpn_tuntap_open(snorlax_vpn_config_get())) < 0) {
        snorlax_error("fail to snorlax_vpn_tuntap_open(...)");

        return ret;
    }

    snorlax_eva_t * eva = snorlax_eva_get();

    snorlax_eva_reg(snorlax_vpn_descriptor_get());

    // REGISTER TUN & TAP 

    while(true) {
        usleep(100);
    }

    return success;
}
