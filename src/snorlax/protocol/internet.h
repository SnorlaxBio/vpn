/**
 * @file        snorlax/protocol/internet.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 29, 2024
 */

#ifndef   __SNORLAX__PROTOCOL_INTERNET__H__
#define   __SNORLAX__PROTOCOL_INTERNET__H__

#include <snorlax.h>

#if       __BYTE_ORDER == __LITTLE_ENDIAN
#define internet_protocol_version_get(datagram)     (datagram[0] >> 4)
#else  // __BYTE_ORDER == __LITTLE_ENDIAN
#define internet_protocol_version_get(datagram)     (datagram[0] & 0x0Fu)
#endif // __BYTE_ORDER == __LITTLE_ENDIAN


#endif // __SNORLAX__PROTOCOL_INTERNET__H__
