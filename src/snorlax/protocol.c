#include <stdio.h>
#include <string.h>

#include "protocol.h"

extern char * protocol_address_to_hexadecimalstr(char * s, const protocol_address_t * addr, uint16_t len) {
#ifndef   RELEASE
    snorlaxdbg(s == nil, false, "critical", "");
#endif // RELEASE

    for(uint16_t i = 0; i < len; i++) {
        sprintf(&s[i*2], "%02x", addr[i]);
    }

    return s;
}

extern void protocol_context_buffer_reserve_reversal(protocol_context_t * context, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(context->bufferlen < n, false, "critical", "");
#endif // RELEASE

    if(n > 0) {
        context->packet = context->packet - n;
        context->packetlen = context->packetlen + n;
        context->bufferlen = context->bufferlen - n;
        memset(context->packet, 0, n);
    }
}
