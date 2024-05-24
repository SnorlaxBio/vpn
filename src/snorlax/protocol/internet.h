/**
 * @file        snorlax/protocol/internet.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 23, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET__H__
#define   __SNORLAX__PROTOCOL_INTERNET__H__

#include <stdio.h>
#include <stdint.h>

#include <snorlax.h>

#include <snorlax/protocol.h>
#include <snorlax/protocol/internet/version4.h>

typedef uint8_t *       snorlax_protocol_internet_t;

#define snorlax_protocol_internet_version_get(datagram)     (datagram[0] >> 4)

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_internet_debug(FILE * stream, const uint8_t * datagram);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_INTERNET__H__
