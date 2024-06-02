/**
 * @file        snorlax/vpn/tun.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 1, 2024
 * 
 * 이 헤더 파일은 사용자에게 노출 시키지 않는다. 객체 지향적으로 이야기 하면
 * 프라이뱃 속성이다.
 */

#ifndef   __SNORLAX__VPN_TUNTAP__H__
#define   __SNORLAX__VPN_TUNTAP__H__

#include <stdio.h>
#include <stdint.h>

#include <net/if.h>

#include <snorlax.h>

#include <snorlax/vpn/config.h>

struct snorlax_vpn {
    int fd;
};

typedef struct snorlax_vpn snorlax_vpn_t;

extern const snorlax_vpn_t * snorlax_vpn_get(void);

extern int snorlax_vpn_tuntap_open(const snorlax_vpn_config_t * config);
extern void snorlax_vpn_tuntap_close(void);
extern int snorlax_vpn_descriptor_get(void);

#endif // __SNORLAX__VPN_TUNTAP__H__
