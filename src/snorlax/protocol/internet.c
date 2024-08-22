#include <arpa/inet.h>

#include "internet.h"
#include "internet/version4.h"
#include "internet/version6.h"

extern uint32_t internet_protocol_checksum_sum(protocol_packet_t * packet, uint64_t packetlen) {
    uint32_t value = 0;
    uint64_t n = (packetlen / 2);
    uint16_t * values = (uint16_t *) packet;

    for(uint64_t i = 0; i < n; i++) {
        value = value + ntohs(values[i]);
    }
    
    if(packetlen % 2){
        uint16_t last = packet[packetlen - 1];
        printf("checksum => %x\n", last);
        last = (last << 8u);
        printf("checksum => %x\n", last);
        value = value + last;
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
