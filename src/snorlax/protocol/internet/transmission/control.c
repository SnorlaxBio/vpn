#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

#include "control.h"

#include "../version4.h"
#include "../version6.h"

extern uint16_t transmission_control_protocol_checksum_cal(transmission_control_protocol_packet_t * segment, uint64_t segmentlen, internet_protocol_pseudo_t * pseudo, uint64_t pseudolen) {
#ifndef   RELEASE
    snorlaxdbg(segment == nil, false, "critical", "");
    snorlaxdbg(segmentlen == 0, false, "critical", "");
    snorlaxdbg(pseudo == nil, false, "critical", "");
    snorlaxdbg(pseudolen == 0, false, "critical", "");
#endif // RELEASE

    uint16_t checksum = segment->checksum;
    segment->checksum = 0;

    snorlaxdbg(false, true, "debug", "segmentlen => %lu", segmentlen);

    uint32_t value = internet_protocol_checksum_sum((protocol_packet_t *) pseudo, pseudolen);
    value = value + internet_protocol_checksum_sum((protocol_packet_t *) segment, segmentlen);

    while(value >> 16) value = (value >> 16) + (value & 0x0000FFFFu);

    segment->checksum = checksum;

    return (int16_t) (~value);
}

/**
 * Generate Initial Sequence Number <sup>ISN</sup>.
 * 
 * @param in        version  | uint8_t   | Internet Protocol <sup>IP</sup> version (4 or 6)
 * @param in        remote   | uint8_t * | remote Internet Protocol <sup>IP</sup> address
 * @param in        local    | uint8_t * | local Internet Protocol <sup>IP</sup> address
 * @param in        ports    | uint32_t  | unsigned 32 bit integer to build with remote and local port (`uint32_from_u16(remote, local)`)
 * @param in        secret   | uint32_t  | secret key 
 * 
 * @return          uint32_t | generated Initial Sequence Number <sup>ISN</sup>
 * 
 * @see             [3.4.1. Initial Sequence Number Selection](https://www.ietf.org/rfc/rfc9293.html)
 */
extern uint32_t transmission_control_func_sequence_gen(uint8_t version, uint8_t * remote, uint8_t * local, uint32_t ports, uint32_t secret) {
#ifndef   RELEASE
    snorlaxdbg(version !=4 && version != 6, false, "critical", "");
    snorlaxdbg(remote == nil, false, "critical", "");
    snorlaxdbg(local == nil, false, "critical", "");
#endif // RELEASE

    uint32_t ret = 0;
    if(version == 4) {
        ret = time(nil);
        ret = ret + uint32_of(remote);
        ret = ret + uint32_of(local);
        ret = ret + ports;
        ret = ret + secret;
    } else if(version == 6) {
        ret = time(nil);
        for(int i = 0; i < 4; i++) {
            ret = ret + uint32_of((remote + i * 4));
            ret = ret + uint32_of((local + i * 4));
        }
        ret = ret + ports;
        ret = ret + secret;
    } else {
        snorlaxdbg(true, false, "critical", "");
    }

    return ret;
}

extern int32_t transmission_control_func_check_acceptable_seq(uint32_t sequence, uint32_t window, uint32_t n, uint32_t length) {
    if(length == 0) {
        if(window == 0) return sequence == n;

        return n - sequence < window;
    }

    if(window > 0) return ((n - sequence < window) || (n + length - sequence < window));

    return false;
}