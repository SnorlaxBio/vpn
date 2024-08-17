#include <arpa/inet.h>

#include "version4.h"

extern internet_protocol_version4_pseudo_t * internet_protocol_version4_pseudo_gen(internet_protocol_version4_packet_t * datagram) {
    internet_protocol_version4_pseudo_t * pseudo = (internet_protocol_version4_pseudo_t *) calloc(1, sizeof(internet_protocol_version4_pseudo_t));

    pseudo->destination = datagram->destination;
    pseudo->source = datagram->source;
    pseudo->length = ntohs(datagram->total) - (datagram->length) * 4;
    pseudo->protocol = datagram->protocol;

    return pseudo;
}

extern uint16_t internet_protocol_version4_checksum_cal(internet_protocol_version4_packet_t * datagram, uint64_t datagramlen) {
#ifndef   RELEASE
    snorlaxdbg(datagram == nil, false, "critical", "");
    snorlaxdbg(datagramlen == 0, false, "critical", "");
#endif // RELEASE
    uint16_t checksum = datagram->checksum;
    datagram->checksum = 0;

    uint32_t value = internet_protocol_checksum_sum((protocol_packet_t *) datagram, datagram->length * 4);

    while(value >> 16) value = (value >> 16) + (value & 0x0000FFFFu);

    datagram->checksum = checksum;

    return (int16_t) (~value);
}

extern uint32_t internet_protocol_version4_direction_cal(uint32_t source, uint32_t destination, uint32_t * local) {
    if(local == nil) return internet_protocol_direction_none;

    int32_t in = (*local == destination);
    int32_t out = (*local == source);

    if(in && out) {
        return internet_protocol_direction_internal;
    } else if(in) {
        return internet_protocol_direction_in;
    } else if(out) {
        return internet_protocol_direction_out;
    }

    return internet_protocol_direction_none;
}