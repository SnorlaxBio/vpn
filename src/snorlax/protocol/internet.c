#include <arpa/inet.h>

#include "internet.h"

union lastval {
    uint16_t uint16;
    struct {
        uint8_t first;
        uint8_t second;
    };
};

typedef union lastval lastval_t;

extern uint32_t internet_protocol_checksum_sum(protocol_packet_t * packet, uint64_t packetlen) {
    uint32_t value = 0;
    uint64_t n = packetlen = packetlen / 2;
    uint16_t * values = (uint16_t *) packet;

    for(uint64_t i = 0; i < n; i++) {
        value = value + htons(values[i]);
    }
    
    if(packetlen % 2) {
        lastval_t last = { .first = packet[packetlen - 1], .second = 0 };

        value = value + last.uint16;
    }

    return value;
}