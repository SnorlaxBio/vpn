#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#include "version6.h"

extern int32_t internet_protocol_version6_extension_check(uint32_t no) {
    switch(no) {
        case internet_protocol_version6_extension_hopbyhop_no:      return true;
        case internet_protocol_version6_extension_routing_no:       return true;
        case internet_protocol_version6_extension_fragment_no:      return true;
        case internet_protocol_version6_extension_destination_no:   return true;
        case internet_protocol_version6_extension_no_next_header:   return true;
        default:                                                    return false;
    }
}

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

extern internet_protocol_version6_pseudo_t * internet_protocol_version6_pseudo_gen(internet_protocol_version6_packet_t * datagram, uint8_t next, uint64_t len) {
    internet_protocol_version6_pseudo_t * pseudo = (internet_protocol_version6_pseudo_t *) calloc(1, sizeof(internet_protocol_version6_pseudo_t));

    memcpy(pseudo->destination, datagram->destination, 16);
    memcpy(pseudo->source, datagram->source, 16);
    pseudo->length = len;
    pseudo->next = next;

    return pseudo;
}

extern uint32_t internet_protocol_version6_direction_cal(uint8_t * source, uint8_t * destination, uint8_t * local) {
#ifndef   RELEASE
    snorlaxdbg(source == nil, false, "critical", "");
    snorlaxdbg(destination == nil, false, "critical", "");
#endif // RELEASE

    if(local == nil) return internet_protocol_direction_none;

    int32_t out = (memcmp(source, local, 16) == 0);
    int32_t in = (memcmp(destination, local, 16) == 0);

    if(in && out) {
        return internet_protocol_direction_internal;
    } else if(in) {
        return internet_protocol_direction_in;
    } else if(out) {
        return internet_protocol_direction_out;
    }

    return internet_protocol_direction_none;
}