#include <string.h>

#include "../../protocol.h"

extern protocol_address_node_t * protocol_address_node_set(protocol_address_node_t * address, const uint8_t * addr, uint16_t len) {
#ifndef   RELEASE
    snorlaxdbg(address == nil, false, "critical", "");
#endif // RELEASE

    address->len = len;

    if(addr && len) {
        memcpy(protocol_address_node_addrptr_get(address), addr, len);
    } else if(len) {
        memset(protocol_address_node_addrptr_get(address), 0, len);
    }

    return address;
}