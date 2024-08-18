#include <arpa/inet.h>

#include "internet.h"
#include "internet/version4.h"
#include "internet/version6.h"

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
/**
 * 
 * 이 함수의 파라미터 s 의 크기는 128 보다 작으면 안된다.
 */
extern const char * internet_protocol_address_to_string(uint8_t version, char * s, const uint8_t * addr) {
#ifndef   RELEASE
    snorlaxdbg(s == nil, false, "critical", "");
    snorlaxdbg(addr == nil, false, "critical", "");
#endif // RELEASE

    if(version == 4) {
        return internet_protocol_version4_address_to_string(s, *((uint32_t *) addr));
    } else if(version == 6) {
        return internet_protocol_version6_address_to_string(s, addr);
    } else {
        snorlaxdbg(true, false, "debug", "");

        s[0] = 0;

        return s;
    }

    return s;
}