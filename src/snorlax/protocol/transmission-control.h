/**
 * @file        snorlax/protocol/transmission-control.h
 * @brief       
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 26, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_TRANSMISSION_CONTROL__H__
#define   __SNORLAX__PROTOCOL_TRANSMISSION_CONTROL__H__

#include <stdio.h>
#include <stdint.h>

#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

struct snorlax_protocol_transmission_control {
    uint16_t source;
    uint16_t destination;
    uint32_t sequence;
    uint32_t acknowledgment;
#if       __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t reserved:4;
    uint8_t  offset:4;
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t  offset:4;
    uint8_t reserved:4;
#endif // __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t controls;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent;
};

typedef struct snorlax_protocol_transmission_control snorlax_protocol_transmission_control_t;

// typedef uint8_t *       snorlax_protocol_internet_t;

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_transmission_control_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_TRANSMISSION_CONTROL__H__
