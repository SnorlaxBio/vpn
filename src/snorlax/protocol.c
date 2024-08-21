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
