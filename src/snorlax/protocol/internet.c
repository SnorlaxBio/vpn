/**
 * @file        snorlax/protocol/internet.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 23, 2024
 */

#include "internet.h"
#include "internet/version4.h"

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_internet_debug(FILE * stream, const uint8_t * datagram) {
    uint8_t version = snorlax_protocol_internet_version_get(datagram);

    if(version == 4) {
        snorlax_protocol_internet_version4_debug(stream, datagram);
    } else if(version == 6) {
        snorlax_implement("internet protocol version 6");
    } else {
        snorlax_error("unknown internet protocol version => %d", version);
    }
}
#endif // SNORLAX_DEBUG

