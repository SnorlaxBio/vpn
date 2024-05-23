/**
 * @file        snorlax/pcap.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 22, 2024
 */

#include "pcap.h"

#include <snorlax/protocol/ethernet.h>

extern int snorlax_pcap_sniff(const char * dev, snorlax_pcap_handler_t callback) {
    pcap_t * handle = nil;
    int snaplen = BUFSIZ;
    int promisc = 1;
    int timeout = 1000;
    char errbuf[PCAP_BUF_SIZE];

    snorlax_string_init(errbuf);

    if((handle = pcap_open_live(dev, snaplen, promisc, timeout, errbuf)) != nil) {
        pcap_loop(handle, 0, callback, nil);

        pcap_close(handle);
        handle = nil;

        return success;
    }

    snorlax_error("fail to pcap_open_live(...) => %s", errbuf);

    return fail;
}

#ifdef    SNORLAX_DEBUG
extern void snorlax_pcap_debug(FILE * stream, const snorlax_pcap_header_t * header, const uint8_t * datagram) {
    fprintf(stdout, "%ld.%06ld\n", header->ts.tv_sec, header->ts.tv_usec);

    snorlax_protocol_ethernet_debug(stream, datagram);

    fprintf(stdout, "\n");
}

extern void snorlax_pcap_handler_debug(uint8_t * user, const snorlax_pcap_header_t * header, const uint8_t * datagram) {
    snorlax_pcap_debug(stdout, header, datagram);
}
#endif // SNORLAX_DEBUG