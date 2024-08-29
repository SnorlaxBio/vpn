#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

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

extern int32_t transmission_control_func_check_acceptable_seq(uint32_t sequence, uint32_t window, uint32_t n, uint32_t length) {
    if(length == 0) {
        if(window == 0) return sequence == n;

        return n - sequence < window;
    }

    if(window > 0) return ((n - sequence < window) || (n + length - sequence < window));

    return false;
}