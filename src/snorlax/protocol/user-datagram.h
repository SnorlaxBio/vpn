/**
 * @file        snorlax/protocol/user-datagram.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 23, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_USER_DATAGRAM__H__
#define   __SNORLAX__PROTOCOL_USER_DATAGRAM__H__

#include <stdio.h>
#include <stdint.h>

#include <snorlax/protocol.h>
#include <snorlax/protocol/internet.h>

struct snorlax_protocol_user_datagram {
    uint16_t source;
    uint16_t destination;
    uint16_t length;
    uint16_t checksum;
};

typedef struct snorlax_protocol_user_datagram snorlax_protocol_user_datagram_t;

#define snorlax_protocol_user_datagram_message_get(segment)         addressof(segment, sizeof(snorlax_protocol_user_datagram_t))

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_user_datagram_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_USER_DATAGRAM__H__
