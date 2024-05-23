/**
 * @file        snorlax/protocol/ethernet.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 22, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_ETHERNET__H__
#define   __SNORLAX__PROTOCOL_ETHERNET__H__

#include <stdint.h>

#include <snorlax.h>

#define snorlax_protocol_ethernet_addrlen       6

#define snorlax_protocol_ethernet_type_ipv4     0x0800u     // Internet Protocol Version 4
#define snorlax_protocol_ethernet_type_arp      0x0806u     // Address Resolution Protocol
#define snorlax_protocol_ethernet_type_ipv6     0x08DDu     // Internet Protocol Version 6
#define snorlax_protocol_ethernet_type_vlan     0x8100u     // VLAN tagged frame (IEEE 802.1Q)
#define snorlax_protocol_ethernet_type_lldp     0x88CCu     // Link Layer Discovery Protocol (LLDP)

struct snorlax_protocol_ethernet {
    uint8_t  destination[snorlax_protocol_ethernet_addrlen];
    uint8_t  source[snorlax_protocol_ethernet_addrlen];
    uint16_t type;
};

typedef struct snorlax_protocol_ethernet snorlax_protocol_ethernet_t;

#define snorlax_protocol_ethernet_header_get(datagram)      ((snorlax_protocol_ethernet_t *) datagram)
#define snorlax_protocol_ethernet_segment_get(datagram)     addressof(datagram, sizeof(snorlax_protocol_ethernet_t))

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_ethernet_debug(FILE * stream, const uint8_t * datagram);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_ETHERNET__H__