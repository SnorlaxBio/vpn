/**
 * @file        snorlax/pcap.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 22, 2024
 */

#ifndef   __SNORLAX__PCAP__H__
#define   __SNORLAX__PCAP__H__

#include <pcap/pcap.h>

#include <snorlax.h>

typedef pcap_handler        snorlax_pcap_handler_t;
typedef struct pcap_pkthdr  snorlax_pcap_header_t;

extern int snorlax_pcap_sniff(const char * dev, snorlax_pcap_handler_t callback);

#ifdef    SNORLAX_DEBUG
extern void snorlax_pcap_debug(FILE * stream, const snorlax_pcap_header_t * header, const uint8_t * packet);
extern void snorlax_pcap_handler_debug(uint8_t * user, const snorlax_pcap_header_t * header, const uint8_t * packet);
#endif // SNORLAX_DEBUG

#endif // __SNORLAX__PCAP__H__
