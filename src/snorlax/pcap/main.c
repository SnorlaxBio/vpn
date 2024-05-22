/**
 * @file        snorlax/pcap/main.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 22, 2024
 */

#include <snorlax/pcap.h>

int main(int argc, char ** argv) {
    return snorlax_pcap_sniff("eth0", snorlax_pcap_handler_debug);
}