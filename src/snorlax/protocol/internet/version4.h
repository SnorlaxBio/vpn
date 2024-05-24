/**
 * @file        snorlax/protocol/internet/version4.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 23, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_VERSION4__H__
#define   __SNORLAX__PROTOCOL_INTERNET_VERSION4__H__

#include <stdio.h>
#include <stdint.h>

#include <snorlax.h>
#include <snorlax/protocol.h>

struct snorlax_protocol_internet_version4 {
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t length:4;
    uint8_t version:4;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t version:4;
    uint8_t length:4;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t  service;
    uint16_t total;
    uint16_t identification;
    uint16_t fragment;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint32_t source;
    uint32_t destination;
};

struct snorlax_protocol_internet_version4_pseudo {
    uint32_t source;
    uint32_t destination;
    uint8_t  zero;
    uint8_t  protocol;
    uint16_t length;
};

typedef struct snorlax_protocol_internet_version4           snorlax_protocol_internet_version4_t;
typedef struct snorlax_protocol_internet_version4_pseudo    snorlax_protocol_internet_version4_pseudo_t;
typedef uint8_t *                                           snorlax_protocol_internet_version4_option_t;

#define snorlax_protocol_internet_version4_length_header_get(datagram)  (((snorlax_protocol_internet_version4_t *) datagram)->length * 4)

#define snorlax_protocol_internet_version4_segment_get(datagram)        addressof(datagram, snorlax_protocol_internet_version4_length_header_get(datagram))

/**
 * @todo    function: Address
 * @todo    function: Fragment
 * @todo    mechanism: Type of Service
 * @todo    mechanism: Time to Live
 * @todo    mechanism: Options
 * @todo    mechanism: Header Checksum
 */

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_internet_version4_debug(FILE * stream, const uint8_t * datagram);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION4__H__
