#include "../internet.h"

extern internet_protocol_packet_t * internet_protocol_packet_build(internet_protocol_packet_t * datagram, uint64_t n, uint8_t version, const internet_protocol_address_t * source, const internet_protocol_address_t * destination) {
#ifndef   RELEASE
    snorlaxdbg(version != 4 || version != 6, false, "critical", "");
#endif // RELEASE

    if(version == 4) {
        return internet_protocol_version4_packet_build(datagram, n, source, destination);
    } else if(version == 6) {
        return internet_protocol_version6_packet_build(datagram, n, source, destination);
    } else {
        snorlaxdbg(version != 4 || version != 6, false, "critical", "");

        return nil;
    }

    return datagram;
}