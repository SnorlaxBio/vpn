/**
 * @file        snorlax/protocol/application.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 24, 2024
 */

#include "application.h"

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_application_debug(FILE * stream, const uint8_t * message, ...) {
    snorlax_notice("need to implement");
}
#endif // SNORLAX_DEBUG