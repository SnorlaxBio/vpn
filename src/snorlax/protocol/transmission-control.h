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

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_transmission_control_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_TRANSMISSION_CONTROL__H__
