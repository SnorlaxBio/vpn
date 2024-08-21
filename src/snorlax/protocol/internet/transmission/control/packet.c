#include <string.h>

#include "../control.h"

extern uint8_t * transmission_control_protocol_packet_reserve_header(uint8_t * buffer, uint64_t * bufferlen) {
#ifndef   RELEASE
    snorlaxdbg(buffer == nil, false, "critical", "");
    snorlaxdbg(bufferlen == nil, false, "critical", "");
#endif // RELEASE

    buffer = buffer - transmission_control_protocol_header_len;
    *bufferlen = *bufferlen - transmission_control_protocol_header_len;

    memset(buffer, 0, transmission_control_protocol_header_len);

    return buffer;
}
