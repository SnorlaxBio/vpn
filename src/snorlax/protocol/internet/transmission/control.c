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

/**
 * Check acceptable acknowledge number.
 * 
 * A new acknowledgment (called an "acceptable ack") is one for which the inequality below holds:
 * 
 * SND.UNA < SEG.ACK =< SND.NXT
 * 
 * A segment on the retransmission queue is fully acknowledged if the sum of its sequence number and length is less than or equal to the acknowledgment value in the incoming segment.
 * 
 * 이 함수가 필요할까? SEND ACCEPTABLE ACK 는 받았기 때문에,
 * 올바른 패킷이라면 그리고 중간에 받지 않는 패킷이 존재하지 않으면
 * 맨 마지막 혹은 중간에 받지 않은 패킷의 없는 세그먼트의 계산된 ACK 값을 설정하면 된다.
 * 
 * @param in    unacknowledged | uint32_t | Oldest unacknowlegded sequence number. (Send Unacknowledged <sup>SND.UNA</sup>)
 * @param in    next | uint32_t | Next sequence number to be sent. (Send Next <sup>SND.NXT</sup>)
 * @param in    value | uint32_t | Acknowledgment from the receiving Transmission Control Protocol <sup>TCP</sup> peer. (Segment Acknowledgment <sup>SEG.ACK</sup>)
 *              (next sequence number expected by the receiving Transmission Control Protocol <sup>TCP</sup> peer)
 * @return      bool    If return true, acknowledge number is acceptable acknowledge, otherwise not accetable.
 * @see         [3.4. Sequence Numbers / Transmission Control Protocol](https://www.ietf.org/rfc/rfc9293.html#section-3.4)
 */
extern int32_t transmission_control_protocol_ack_acceptable(uint32_t unacknowledged, uint32_t next, uint32_t value) {
    uint32_t length = next - unacknowledged;

    if(length == 0) return unacknowledged == value;

    if(unacknowledged < value) return (value - unacknowledged <= length);

    return false;
}
