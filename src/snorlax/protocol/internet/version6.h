/**
 * @file        snorlax/protocol/internet/version6.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 25, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET_VERSION6__H__
#define   __SNORLAX__PROTOCOL_INTERNET_VERSION6__H__

#include <stdio.h>
#include <stdint.h>

struct snorlax_protocol_internet_version6 {
    uint32_t  prefix;
    uint16_t length;
    uint8_t  next;
    uint8_t  limit;
    uint16_t source[8];
    uint16_t destination[8];
};

typedef struct snorlax_protocol_internet_version6 snorlax_protocol_internet_version6_t;

#define snorlax_protocol_internet_version6_traffic_class_get(internet)        ((prefix & 0x0FF00000u) >> 20u)
#define snorlax_protocol_internet_version6_flow_label_get(internet)           (prefix & 0x000FFFFFu)

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_internet_version6_debug(FILE * stream, const uint8_t * datagram);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_INTERNET_VERSION6__H__
