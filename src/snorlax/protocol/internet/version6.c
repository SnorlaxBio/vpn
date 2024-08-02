#include <arpa/inet.h>

#include "version6.h"

extern const char * internet_protocol_version6_addr_to_str(char * destination, uint8_t * addr) {
#ifndef   RELEASE
    snorlaxdbg(destination == nil, false, "critical", "");
    snorlaxdbg(addr == nil, false, "critical", "");
#endif // RELEASE

    uint16_t * array = (uint16_t *) addr;

    int n = 0;

    for(int i = 0; i < 8; i++) {
        n = n + sprintf(&destination[n], "%04x%c", ntohs(array[i]), i + 1 == 8 ? '\0' : ':');
    }

    return destination;
}