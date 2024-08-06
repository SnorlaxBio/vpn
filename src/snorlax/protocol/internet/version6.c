#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

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

extern internet_protocol_version6_pseudo_t * internet_protocol_version6_pseudo_gen(internet_protocol_version6_packet_t * datagram, uint8_t next, uint64_t len) {
    internet_protocol_version6_pseudo_t * pseudo = (internet_protocol_version6_pseudo_t *) calloc(1, sizeof(internet_protocol_version6_pseudo_t));

    memcpy(pseudo->destination, datagram->destination, 16);
    memcpy(pseudo->source, datagram->source, 16);
    pseudo->length = len;
    pseudo->next = next;

    return pseudo;
}