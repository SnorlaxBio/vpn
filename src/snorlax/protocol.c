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

extern void protocol_context_buffer_reversal_reserve(protocol_context_t * context, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(context->bufferlen == nil, false, "critical", "");
    snorlaxdbg(*context->bufferlen < n, false, "critical", "");
#endif // RELEASE

    if(n > 0) {
        context->packet = context->packet - n;
        context->packetlen = context->packetlen + n;
        *context->bufferlen = *context->bufferlen - n;
        memset(context->packet, 0, n);
    }
}

extern uint64_t protocol_context_buffer_reversal_push(protocol_context_t * context, const uint8_t * data, uint64_t n) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(context->bufferlen == nil, false, "critical", "");
    snorlaxdbg(*context->bufferlen < n, false, "critical", "");
#endif // RELEASE

    if(n > 0) {
        snorlaxdbg(context->packet == nil, false, "critical", "");
        snorlaxdbg(data == nil, false, "critical", "");
        snorlaxdbg(n == 0, false, "critical", "");

        snorlaxdbg(false, true, "debug", "packet => %p, packetlen => %lu, bufferlen => %lu", context->packet, context->packetlen, *context->bufferlen);

        context->packet = context->packet - n;
        context->packetlen = context->packetlen + n;
        *context->bufferlen = *context->bufferlen - n;

        snorlaxdbg(false, true, "debug", "packet => %p, packetlen => %lu, bufferlen => %lu", context->packet, context->packetlen, *context->bufferlen);
        
        memcpy(context->packet, data, n);
    }
}

___pure extern void protocol_context_func_checksum_build(protocol_context_t * context, const uint8_t * pseudo, uint64_t pseudolen) {    
}
