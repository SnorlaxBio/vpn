/**
 * @file        snorlax/protocol/ethernet.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 22, 2024
 */

#include <arpa/inet.h>

#include "ethernet.h"

#include "internet.h"

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_ethernet_debug(FILE * stream, const uint8_t * frame) {
    snorlax_protocol_ethernet_t * header = snorlax_protocol_ethernet_header_get(frame);
    fprintf(stream, "| ethernet ");
    fprintf(stream, "| %02x:%02x:%02x:%02x:%02x:%02x ", header->source[0],
                                                        header->source[1],
                                                        header->source[2],
                                                        header->source[3],
                                                        header->source[4],
                                                        header->source[5]);
    fprintf(stream, "| %02x:%02x:%02x:%02x:%02x:%02x ", header->destination[0],
                                                        header->destination[1],
                                                        header->destination[2],
                                                        header->destination[3],
                                                        header->destination[4],
                                                        header->destination[5]);

    uint16_t type = ntohs(header->type);

    fprintf(stream, "| %04x ", type);
    fprintf(stream, "|\n");

    switch(type) {
        case snorlax_protocol_ethernet_type_ipv4:   snorlax_protocol_internet_debug(stream, snorlax_protocol_ethernet_datagram_get(frame));     break;
        case snorlax_protocol_ethernet_type_arp:    snorlax_todo("Address Resolution Protocol");                                                break;
        case snorlax_protocol_ethernet_type_ipv6:   snorlax_todo("Internet Protocol Version 6");                                                break;
        case snorlax_protocol_ethernet_type_vlan:   snorlax_todo("VLAN Tagged Frame (IEEE 802.1Q)");                                            break;
        case snorlax_protocol_ethernet_type_lldp:   snorlax_todo("Link Layer Discovery Protocol");                                              break;
        default:                                    snorlax_todo("Unknown Protocol => %04x", type);                                             break;
    }
}
#endif // SNORLAX_DEBUG

/**
 * @page        Ethernet            Ethernet
 * 
 * The Ethernet frame includes a preamble and Frame Sequence Delimiter (FSD) so that the receiving network interfaces
 * can detect the starting bit of the data part of the frame, i.e., the packet of one and zero bits. The trailing
 * Frame Check Sequence (FCS) verifies frame's integrity. Ethernet protocol defines the frame format.
 * 
 * @tableofcontents
 * 
 * @section     EthernetPacket      Ethernet Packet
 * 
 * The Ethernet packet is composed of source and destination MAC addresses, the type of protocol data in the 
 * payload, the EtherType, or usually referred to as just the type, and finally the payload portion that carries
 * the message data. The message data could be the message itself such as `Hello world` or a packet of a layer 3
 * protocol, specified in the type field of the packet.
 * 
 * @todo        ETHERNET PACKET DIAGRAM
 * 
 * <img src="Ethernet-Protocol-Packet.png" alt="Ethernet Packet" width="360">
 * 
 * The critical component of the Ethernet protocol are:
 * 
 * 1. MAC addresses
 * 2. Payload data type
 * 3. Payload
 * 
 * @subsection  EthernetPacket_MAC_Address      1. Mac Address
 * 
 * Network interfaces are addressed by a unique 48 bits long integer called the MAC address. It is usually
 * represented as a sequence of six hexadecimal number pairs separated by a colon or a period.
 * 
 * There are reserved MAC addresses for various usage scenarios of the Ethernet protocol. The address space of
 * 6 bytes is organized into two sections of 3 bytes each: Organizationally Unique Identifier (OUI) and the
 * Network Interface Controller (NIC) specific. Organizationally Unique Identifier (OUI) section's first octet
 * last bit may be 0 for a unicast address and 1 for multicast addresses. When the bit before last one of the
 * first octet is 1, Organizationally Unique Identifier (OUI)  is globally unique and when it is 0, tje address
 * is locally adminstered.
 * 
 * Some portion of the MAC address may indicate the manufacturer's identifier for a specific hardware network
 * interface card or the hypervisor that instantiates the virtual machine or containers.
 * 
 * > __Note: Example MAC addresses and represntations:__
 * > 1. `aa:aa:bb:bb:13:9f` or `cc-89-37-15-ee-ff`, both unicast addresses, as the bit sequence in the first
 * >     octet is `10101010` and `11001100` respectively, and ending with a `0` bit for unicast.
 * > 2. `01:80:c2:00:00:00` a multicast address, as the bit sequence in the first octet is `00000001` ending
 * >     width a `1` bit for multicast addresses.
 * 
 * All sending and receiving end devices are identified by their MAC addresses in Ethernet protocol. Forwarding
 * devices rely on MAC addresses as the unique identifiers inside each layer 2 network in order to make forwarding
 * decisions for packets.
 * 
 * > __Analogy: MAC addresses are unique just like social security numbers__
 * > 
 * > Within an Ethernet network, MAC address of an end device is unique so that packets destined to this device
 * > can reach without contention with other devices. In this respect, MAC addresses are similar to Social Security
 * > Number (SSN).
 * 
 * A unique MAC address is a unicast address that identifies an end device among all other devices in an Ethernet
 * network. On the other hand, multicast MAC addresses are used among a specific set of devices that are 
 * programmed to receive on and send to those addresses. Multicast addresses are assigned to be used by specific
 * protocol messages using the Ethernet packet format.
 * 
 * > __Analogy: Multicast vs Unicast__
 * >
 * > In a large party, when addressing a specific group of people such as designated drivers of all attending 
 * > people, the communication is analogous to multicast. When addressing all people in the party, the communcation
 * > is a broadcast. When only a pair are talking to each other, the communication is analogous to unicast.
 * 
 * The MAC address that is composed of all `1` bits has a special name, broacast MAC address: `FF:FF:FF:FF:FF:FF`.
 * The broadcast address is used to reach all end devices within a particular Ethernet network which will be
 * covered in depth the learning module on Ethernet bridge MAC learning.
 * 
 * > __Analogy: Multicast vs Unicast__
 * >
 * > Your subscription to a cable channel is a special form of multicast where all subscribers are able to view
 * > the same programming from the content provider. However, there is still the option to utilize an antenna with
 * > your TV to access the local `broadcast` channels in your region, which are meant to reach everybody with a 
 * > receiving TV device.
 * 
 * @subsection  EthernetPacket_Payload_Data_Type      2. Payload Data Type
 * 
 * The type of protocol that is carried in the payload portion of the packet is indicated by a type code which
 * is called the EtherType, a 16 bit integer that is usually represented in hexadecimal form. Example Ethernet
 * type codes are listed in the following table:
 * 
 * | EtherType | Protocol                             |
 * | --------- | ------------------------------------ |
 * | 0x0800    | Internet Protocol Version 4 (IPv4)   |
 * | 0x0806    | Address Resolution Protocol (ARP)    |
 * | 0x86DD    | Internet Protocol Version 6 (IPv6)   |
 * | 0x8100    | VLAN-tagged frame (IEEE 802.1Q)      |
 * | 0x88CC    | Link Layer Discovery Protocol (LLDP) |
 * 
 * > __Analogy: Letter, Packet, Box, or Postcard__
 * >
 * > The type of payload data being carried is indicated in the EtherType field so that the receiving end device
 * > can decode the expected data structure correctly when reading the payload portion of this packet.
 * 
 * @see     [Ethernet Protocol](https://cot-cn.cougarnet.uh.edu/docs/compnet/012-ethernet.html)
 */