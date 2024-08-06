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