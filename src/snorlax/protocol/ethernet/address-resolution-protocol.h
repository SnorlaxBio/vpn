/**
 * @file        snorlax/protocol/ethernet/address-resolution-protocol.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 24, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_ETHERNET_ADDRESS_RESOLUTION_PROTOCOL__H__
#define   __SNORLAX__PROTOCOL_ETHERNET_ADDRESS_RESOLUTION_PROTOCOL__H__

#include <stdio.h>
#include <stdint.h>

struct snorlax_protocol_address_resolution {
    uint16_t hardware;
    uint16_t protocol;
    struct {
        uint8_t hardware;
        uint8_t protocol;
    } length;
    uint16_t op;
};

typedef struct snorlax_protocol_address_resolution snorlax_protocol_address_resolution_t;

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_ethernet_address_resolution_debug(FILE * stream, const uint8_t * datagram);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_ETHERNET_ADDRESS_RESOLUTION_PROTOCOL__H__
