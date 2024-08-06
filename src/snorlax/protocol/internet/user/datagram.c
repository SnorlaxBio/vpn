#include <arpa/inet.h>

#include "datagram.h"

extern uint16_t user_datagram_protocol_checksum_cal(user_datagram_protocol_packet_t * datagram, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen) {
    uint16_t checksum = datagram->checksum;

    datagram->checksum = 0;

    uint16_t * packet = (uint16_t *) pseudo;
    uint32_t n = (pseudolen / 2);
    uint32_t v = 0;

    for(uint32_t i = 0; i < n; i++) {
        v = v + ntohs(packet[i]);
    }

    packet = (uint16_t *) datagram;
    n = (ntohs(datagram->length) / 2);
    v = 0;

    for(uint32_t i = 0; i < n; i++) {
        v = v + ntohs(packet[i]);
    }

    if(ntohs(datagram->length) % 2 == 1) {
        // TODO: UPGRADE ... FAST ...
        union {
            uint16_t v;
            struct {
                uint8_t first;
                uint8_t second;
            } uint8;
        } last;
        last.uint8.first = ((uint8_t *) datagram)[ntohs(datagram->length) - 1];
        last.uint8.second = 0;
        v = v + last.v;
    }

    while(v >> 16) {
        v = (v >> 16) + (v & 0x0000FFFFu);
    }

    datagram->checksum = checksum;

    return (int16_t) (~v);
}