/**
 * @file        snorlax/protocol/user-datagram.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 23, 2024
 */

#include <arpa/inet.h>

#include "user-datagram.h"

#include "application.h"

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_user_datagram_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    snorlax_protocol_user_datagram_t * udp = (snorlax_protocol_user_datagram_t *)(segment);

    fprintf(stream, "| user datagram ");
    fprintf(stream, "| % 6d ", ntohs(udp->source));
    fprintf(stream, "| % 6d ", ntohs(udp->destination));
    fprintf(stream, "| % 6d ", ntohs(udp->length));
    fprintf(stream, "| % 6d ", ntohs(udp->checksum));
    fprintf(stream, "|\n");

    snorlax_protocol_application_debug(stream, snorlax_protocol_user_datagram_message_get(segment));
}
#endif // SNORLAX_DEBUG

/**
 * @page        UserDatagramProtocol        User Datagram Protocol
 * 
 * @tableofcontents
 * 
 * @section     Introduction                Introduction
 * 
 * This User Datagram Protocol (UDP) is defined to make available a datagram mode of packet-swtiched computer
 * communication in the environment of an interconnected set of computer networks. This protocol assumes that the
 * [Internet Protocol (IP)](https://datatracker.ietf.org/doc/html/rfc791) is used as the underlying protocol.
 * 
 * This protocol provides a procedure for application programs to send messages to other programs with a minimum of
 * protocol mechanism. The protocol is transaction oriented, and delivery and duplicate protection are not 
 * guaranteed. Applications requiring ordered reliable delivery of streams of data should use the [Transmission
 * Control Protocol (TCP)](https://datatracker.ietf.org/doc/html/rfc9293).
 * 
 * @section     Format                      Format
 * 
 * <img src="User-Datagram-Header-Format.png" alt="User Datagram Header Format" width="256">
 * 
 * @section     Fields                      Fields
 * 
 * Source Port is an optional field, when meaningful, it indicates the port of the sending process, and may be
 * assumed to be the port to which is a reply should be addressed in the absence of any other information. If
 * not used, a value of zero is inserted.
 * 
 * Destination Port has a meaning within the context of a particular internet destination address.
 * 
 * Length is the length in octets of this user datagram including this header and the data. (This means the 
 * minimum value of the length is eight.)
 * 
 * Checksum is the 16 bit one's complement of the one's complement sum of a pseudo header of information from
 * the IP header, the UDP header, and the data, padded with zero octets at the end (if necessary) to make a
 * multiple of two octets.
 * 
 * The pseudo header conceptually prefixed to the UDP header contains the source address, the destination address,
 * the protocol, and the UDP length. This information gives protection against misrouted datagrams. This checksum
 * procedure is the same as is used in TCP.
 * 
 * <img src="User-Datagram-Pseudo-Header.png" alt="Pseudo Header" width="256">
 * 
 * If the computed checksum is zero, it is transmitted as all dones (the equivalent in one's complement arithmetic).
 * An all zero tranmitted checksum value means that the transmitter generated no checksum (for debugging or for
 * higher level protocols that don't care).
 * 
 * @section     UserInterface               User Interface
 * 
 * A user interface should allow the creation of new receive ports, receive operations on the receive ports
 * that return the data octets and an indication of source port and source address, and an operation that allows
 * a datagram to be sent, specifying the data, source and destination ports and addresses to be sent.
 * 
 * @section     IPInterface                 IP Interface
 * 
 * The UDP module must be able to determine the source and destination internet addresses and the protocol field
 * from the internet header. One possible UDP/IP interface would return the whole internet datagram including all
 * of the internet header in response to a receive operation. Such an interface would also allow the UDP to pass
 * a full internet datagram complete with header to the IP to send. The IP would verify certain fields for
 * consistency and compute the internet header checksum.
 * 
 * @section     ProtocolApplication         Protocol Application
 * 
 * The major uses of this protocol is the Internet Name Server, and the Trivial File Transfer.
 * 
 * @section     ProtocolNumber              Protocol Number
 * 
 * This is protocol 17 (21 octal) when used in the Internet Protocol. Other protocol numbers are listed in
 * [ASSIGNED NUMBERS](https://datatracker.ietf.org/doc/html/rfc1700).
 * 
 * @see         [User Datagram Protocol](https://datatracker.ietf.org/doc/html/rfc768)
 */