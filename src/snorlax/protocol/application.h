/**
 * @file        snorlax/protocol/application.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 24, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_APPLICATION__H__
#define   __SNORLAX__PROTOCOL_APPLICATION__H__

#include <stdint.h>
#include <stdio.h>

#include <snorlax.h>
#include <snorlax/protocol.h>

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_application_debug(FILE * stream, const uint8_t * message, ...);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PROTOCOL_APPLICATION__H__
