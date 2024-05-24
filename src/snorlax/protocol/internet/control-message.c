/**
 * @file        snorlax/protocol/internet/control-message.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 24, 2024
 */

#include <arpa/inet.h>

#include "control-message.h"

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_internet_control_message_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    snorlax_protocol_internet_control_message_t * message = (snorlax_protocol_internet_control_message_t *) segment;
    fprintf(stream, "| internet control message ");
    fprintf(stream, "| % 3d ", message->type);
    fprintf(stream, "| % 3d ", message->code);
    fprintf(stream, "| % 6d ", ntohs(message->checksum));

    switch(message->type) {
        case snorlax_protocol_internet_control_message_type_echo_req:                   snorlax_protocol_internet_control_message_echo_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_echo_res:                   snorlax_protocol_internet_control_message_echo_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_destination_unreachable:    snorlax_protocol_internet_control_message_destination_unreachable_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_source_quench:              snorlax_protocol_internet_control_message_source_quench_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_redirect:                   snorlax_protocol_internet_control_message_redirect_debug(stream, internet, segment);    break;
        case snorlax_protocol_internet_control_message_type_time_exceeded:              snorlax_protocol_internet_control_message_time_exceeded_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_parameter_problem:          snorlax_protocol_internet_control_message_parameter_problem_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_timestamp_req:              snorlax_protocol_internet_control_message_timestamp_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_timestamp_res:              snorlax_protocol_internet_control_message_timestamp_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_information_req:            snorlax_protocol_internet_control_message_information_debug(stream, internet, segment); break;
        case snorlax_protocol_internet_control_message_type_information_res:            snorlax_protocol_internet_control_message_information_debug(stream, internet, segment); break;
        default:                                                                        snorlax_error("unknown internet control message type => %d", message->type);
    }
}

extern void snorlax_protocol_internet_control_message_destination_unreachable_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    // TODO:
    fprintf(stream, "|\n");
}

extern void snorlax_protocol_internet_control_message_time_exceeded_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    // TODO:
    fprintf(stream, "|\n");
}

extern void snorlax_protocol_internet_control_message_parameter_problem_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    snorlax_protocol_internet_control_message_parameter_problem_t * message = (snorlax_protocol_internet_control_message_parameter_problem_t *) segment;

    fprintf(stream, "| % 3d ", message->pointer);
    // TODO: 
    fprintf(stream, "|\n");
}

extern void snorlax_protocol_internet_control_message_source_quench_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    // TODO:
    fprintf(stream, "|\n");
}

extern void snorlax_protocol_internet_control_message_redirect_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    snorlax_protocol_internet_control_message_redirect_t * message = (snorlax_protocol_internet_control_message_redirect_t *) segment;

    fprintf(stream, "| %15s ", inet_ntoa((struct in_addr) { .s_addr = message->address }));

    // TODO:

    fprintf(stream, "\n");
}

extern void snorlax_protocol_internet_control_message_echo_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    snorlax_protocol_internet_control_message_echo_t * message = (snorlax_protocol_internet_control_message_echo_t *) segment;

    fprintf(stream, "| % 6d ", ntohs(message->identifier));
    fprintf(stream, "| % 6d ", ntohs(message->sequence));

    // TODO:

    fprintf(stream, "|\n");
}

extern void snorlax_protocol_internet_control_message_timestamp_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    snorlax_protocol_internet_control_message_timestamp_t * message = (snorlax_protocol_internet_control_message_timestamp_t *) segment;

    fprintf(stream, "| % 6d ", ntohs(message->identifier));
    fprintf(stream, "| % 6d ", ntohs(message->sequence));

    // TODO: 

    fprintf(stream, "|\n");
}

extern void snorlax_protocol_internet_control_message_information_debug(FILE * stream, const snorlax_protocol_internet_t internet, const uint8_t * segment) {
    snorlax_protocol_internet_control_message_information_t * message = (snorlax_protocol_internet_control_message_information_t *) segment;

    fprintf(stream, "| % 6d ", ntohs(message->identifier));
    fprintf(stream, "| % 6d ", ntohs(message->sequence));

    // TODO: 

    fprintf(stream, "|\n");
}
#endif // SNORLAX_DEBUG

/**
 * @page        InternetControlMessageProtocol      Internet Control Message Protocol
 * 
 * @tableofcontents
 * 
 * @section     Introduction        Introduction
 * 
 * The [Internet Protocol (IP)](https://datatracker.ietf.org/doc/html/rfc791) is used for host-to-host datagram service
 * in a system of interconnected networks called the Catenet. The network connecting devices are called Gateways.
 * These gateways to communicate between themselves for control purposes via a Gateway to Gateway Protocol (GGP).
 * Occasionally a gateway or destination host will communicate with a source host, for example, to report an error
 * in datagram processing. For such purposes this protocol, the Internet Control Message Protocol (ICMP), is used.
 * ICMP, uses the basic support of IP as if it were a higher level protocol, however, ICMP is actually an integral
 * part of IP, and must be implemented by every IP module.
 * 
 * ICMP messages are sent in several situations: for example, when a datagram cannot reach its destination, when the
 * gateway does not have the buffering capacity to forward a datagram, and when the gateway can direct the host to send
 * traffic on a shorter route.
 * 
 * The Internet Protocol is not designed to be absolutely reliable. The purpose of these control messages is to provide
 * feedback about problems in the communication environment, not to make IP reliable. There are still no guarantees that
 * a datagram will be delivered or a control message will be returned. Some datagrams may still be undelivered without
 * any report of their loss. The higher evel protocols that use IP must implement their own reliability procesures
 * if reliable communication is required.
 * 
 * The ICMP messages typically report errors in the processing of datagrams. To avoid the infinite regress of messages
 * about messages etc., no ICMP messages are sent about ICMP messages. Also ICMP messages are only sent about errors
 * in handling fragment zero of fragmented datagrams. (Fragment zero has the fragment offset equal zero).
 * 
 * @section     MessageFormats          Message Formats
 * 
 * ICMP messages are sent using the basic IP header. The first octet of the data portion of the datagram is a ICMP
 * type field; the value of this field determines the format of the remaining data. Any field labeled "unused" is
 * reserved for later extensions and must be zero when sent, but receivers should not use these fields (except to
 * include them in the checksum). Unless otherwise noted under the individual format descriptions, the values of
 * the internet header fields are as follows:
 * 
 * | Field                                  | Description |
 * | -------------------------------------- | ----------- |
 * | Version                                | 4 |
 * | Internet Header Length (IHL)           | Internet Header Length in 32 bit words. |
 * | Type of Service                        | 0 |
 * | Total Length                           | Length of internet header and data in octets. |
 * | Identification, Flags, Fragment Offset | Used in fragmentation |
 * | Time to Live                           | Time to live in seconds; as this field is decremented at each machine in which the datagram is processed, the value in this field should be at least as great as the number of gateway which this datagram will traverse. |
 * | Protocol                               | ICMP = 1 |
 * | Header Checksum                        | The 16 bit one's complement of the one's complement sum of all 16 bit words in the header. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Source Address                         | The address of the gateway or host that composes the ICMP message. Unless otherwise noted, this can be any of a gateway's addresses. |
 * | Destination Address                    | The address of the gateway or host to which the message should be sent. |
 * 
 * @subsection      MessageFormats_DestinationUnreachableMessage        Destination Unreachable Message
 * 
 * <img src="Internet-Control-Message-Protocol-Destination-Unreachable-Message.png" alt="Destination Unreachable Message" width="256">
 * 
 * | Field                                 | Target | Description |
 * | ------------------------------------- | ------ | ----------- |
 * | Destination Address                   | IP     | The source network and address from the original datagram's data. |
 * | Type                                  | ICMP   | 3 |
 * | Code                                  | ICMP   | 0 = net unreachable; 1 = host unreachable; 2 = protocol unreachable; 3 = port unreachable; 4 = fragmentation needed and DF set; 5 = source route failed. |
 * | Checksum                              | ICMP   | The checksum is the 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP type. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Internet Header + 64 bits of Datagram | ICMP   | The internet header plus the first 64 bits of the original datagram's data. This data is used by the host to machine the message to the appropriate process. If a higher level protocol uses port numbers, they are assumed to be in the first 64 data bits of the original datagram's data. |
 * 
 * ### Description
 * 
 * If, according to the information in the gateway's routing tables, the network specified in the internet destination
 * field of a datagram is unreachable, e.g., the distance ot the network is infinity, the gateway may send a destination
 * unreachable message to the internet source host of the datagram. In addition, in some networks, the gateway may be
 * able to determine if the internet destination unreachable. Gateways in these networks may send destination
 * unreachable messages to the source host when the destination host is unreachable.
 * 
 * If, in the destination host, the IP module cannot deliver the datagram because the indicated protocol module or
 * process port is not active, the destination host may send a destination unreachable message to the source host.
 * 
 * Another case is when a datagram must be fragmented to be forwarded by a gatewy yet the "Don't Fragment" flag is on.
 * In this case the gateway must discard the datagram and may return a destination unreachable message.
 * 
 * Codes 0, 1, 4, and 5 may be received from a gateway. Codes 2 and 3 may be received from a host.
 * 
 * @subsection      MessageFormats_TimeExceededMessage      Time Exceeded Message
 * 
 * <img src="Internet-Control-Message-Protocol-Time-Exceeded-Message.png" alt="Time Exceeded Message" width="256">
 * 
 * | Field                                        | Target | Description |
 * | -------------------------------------------- | ------ | ----------- |
 * | Destination Address                          | IP     | The source network and address from the original datagram's data. |
 * | Type                                         | ICMP   | 11 |
 * | Code                                         | ICMP   | 0 = Time to live exceeded in transit; 1 = Fragment reassembly time exceeded. |
 * | Checksum                                     | ICMP   | The checksum is the 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Internet Header + 64 bits of Data Datagram | | ICMP   | The internet header plus the first 64 bits of the original datagram's data. This data is used by the host to match the mssage to the appropriate process. If a higher level protocol uses port numbers, they are assumed to be in the first 64 data bits of the original datagram's data. |
 * 
 * ### Description
 * 
 * If the gateway processing a datagram finds the time to live field is zero it must discard the datagram. The gateway
 * may also notify the source host via the time exceeded message.
 * 
 * If a host reassembling a fragmented datagram cannot complete the reassembly due to missing fragments within its time
 * limit it discards the datagram, and it may send a time exceeded message.
 * 
 * If fragment zero is not available then no time exceeded need be sent at all.
 * 
 * Code 0 may be received from a gateway. Code 1 may be received from a host.
 * 
 * @subsection  MessageFormats_ParameterProblemMessage      Parameter Problem Message
 * 
 * <img src="Internet-Control-Message-Protocol-Parameter-Problem-Message.png" alt="Parameter Problem Message" width="256">
 * 
 * | Field                                      | Target | Description |
 * | ------------------------------------------ | ------ | ----------- |
 * | Destination Address                        | IP     | The source network and address from the original datagram's data. |
 * | Type                                       | ICMP   | 12 |
 * | Code                                       | ICMP   | 0 = pointer indicates the error. |
 * | Checksum                                   | ICMP   | The checksum is the 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Pointer                                    | ICMP   | If code = 0, identifies the octet where an error was detected. |
 * | Internet Header + 64 bits of Data Datagram | ICMP   | The internet header plus the first 64 bits of the orignal datagram's data. This data is used by the host to match the message to the appropriate process. If a higher level protocol uses port numbers, they are assumed to be in the first 64 data bits of the original datagram's data. |
 * 
 * ### Description
 * 
 * If the gateway or host processing a datagram finds a problem with the header parameters such that it cannot complete
 * processing the datagram it must discard the datagram. One potential source of such a problem is with incorrect arguments
 * in an option. The gateway or host may also notify the source host via the parameter problem message. This message
 * is only sent if the error caused the datagram to be discarded.
 * 
 * The pointer identifies the octet of the original datagram's header where the error was detected (it may be in the
 * middle of an option). For example, 1 indiates something is wrong with the Type of Service, and (if there are options
 * present) 20 indiates something is wrong with the type code of the first option.
 * 
 * Code 0 may be received from a gateway or a host.
 * 
 * @subsection      MessageFormats_Source_Quench_Message    Source Quench Message
 * 
 * <img src="Internet-Control-Message-Protocol-Source-Quench-Message.png" alt="Source Quench Message" width="256">
 * 
 * | Field | Target | Description |
 * | ----- | ------ | ----------- |
 * | Destination Address | IP | The source network and address of the original datagram's data. |
 * | Type                | ICMP | 4 |
 * | Code                | ICMP | 0 |
 * | Checksum            | ICMP | The checksum is the 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Internet Header + 64 bits of Data Datagram | ICMP | The internet plus the first 64 bits of the original datagram's data. This data is used by the host to match the message to the approriate process. If a higher level protocol uses port numbers, they are assumed to be in the first 64 data bits of the original datagram's data. |
 * 
 * ### Description
 * 
 * A gateway may discard internet datagrams if it does not have the buffer space needed to queue the datagrams for output
 * to the next network on the route to the destination network. If a gateway discards a datagram, it may send a source
 * quench message if datagrams arrive too fast to be processed. The source quench message is a request to the host to
 * cut back the rate at which it is sending traffic to the internet destination. The gateway may send a source quench
 * message for every message that it discards. On receipt of a source quench message, the source host should cut back
 * the rate at which it is sending traffic to the specified destination until it no longern sending source quench messages
 * from the gateway. The source host can then gradually increase the rate at which it sends traffic to the destination
 * until it again receives source quench messages.
 * 
 * The gateway or host may send the source quench message when it approaches its capacity limit rather than waiting until
 * the capacity is exceeded. This means that the data datagram which triggered the source quench message may be delivered.
 * 
 * Code 0 may be received from a gateway or a host.
 * 
 * @subsection      MessageFormats_Redirect_Message         Redirect Message
 * 
 * <img src="Internet-Control-Message-Protocol-Redirect-Message.png" alt="Redirect Message" width="256">
 * 
 * | Field | Target | Description |
 * | ----- | ------ | ----------- |
 * | Destination Address | IP | The source network and address of the original datagram's data. |
 * | Type                | ICMP | 5 |
 * | Code                | ICMP | 0 = Redirect datagrams for the network; 1 = Redirect datagrams for the Host; 2 = Redirect datagrams for the Type of Service and Network; 3 = Redirect datagrams for the Type of Service and Host. |
 * | Checksum            | ICMP | The checksum is the 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Gateway Internet Address | ICMP | Address of the gateway to which traffic for the network specified in the internet destination network field of the original datagram's data should be sent. |
 * | Internet Header + 64 bits of Data Datagram | ICMP | The internet header plus the first 64 bits of the original datagram's data. This data is used by the host to match the message to the approrpiate process. If a higher level protocol uses port numbers, they are assumed to be in the first 64 data bits of the original datagram's data. |
 * 
 * ### Description
 * 
 * The gateway sends a redirect message to a host in the following situation. A gateway, G1, receives an internet datagram
 * from a host on a network to which the gateway is attached. The gateway, G1, checks its routing table and obtains the
 * address of the next gateway, G2, on the route to the datagram's internet destination network, X. If G2 and the host 
 * identified by the internet source address of the datagram are on the same network, a redirect message is sent to the
 * host. The redirect message advises the host to send its traffic for network X directly to gateway G2 as this is a
 * shorter path to the destination. The gateway forwards the original datagram's data to its internet destination.
 * 
 * For datagrams with the IP source route options and the gateway address in the destination address field, a redirect
 * message is not sent even if there is a better route to the ultimate destination than the next address in the source
 * route.
 * 
 * Codes 0, 1, 2, and 3 may be received from a gateway.
 * 
 * @subsection      MessageFormats_Echo_or_EchoReplyMessage     Echo or Echo Reply Message
 * 
 * <img src="Internet-Control-Message-Protocol-Echo-or-Echo-Reply-Message.png" alt="Echo or Echo Reply Message" width="256">
 * 
 * | Field | Target | Description |
 * | ----- | ------ | ----------- |
 * | Addresses | IP | The address of the source in an echo message will be the destination of the echo reply message. To form an echo reply message, the source and destinaion addresses are simply reversed, the type code changed to 0, and the checksum recomputed. |
 * | Type      | ICMP | 8 for echo message; 0 for echo reply message. |
 * | Code      | ICMP | 0 |
 * | Checksum  | ICMP | The checksum is the 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type. For computing the checksum, the checksum field should be zero. If the total length is odd, the received data is padded with one octet of zeros for computing the checksum. This checksum may be replaced in the future. |
 * | Identifier | ICMP | If code = 0, an identifier to aid in matching echos and replies, may be zero. |
 * | Sequence Number | ICMP | If code = 0, a sequence number to aid in matching echos and replies, may be zero. |
 * 
 * ### Description
 * 
 * The data received in the echo message must be returned in the echo reply message.
 * 
 * The identifier and sequence number may be used by the echo sender to aid in matching the replies with the echo requests.
 * For example, the identifier might be used like a port in TCP or UDP to identify a session, and the sequence number
 * might be incremented on each echo request sent. The echoer returns these same values in the echo reply.
 * 
 * Code 0 may be received from a gateway or a host.
 * 
 * @subsection      MessageFormats_Timestamp_or_TimestampReplyMessage       Timestamp or Timestamp Reply Message
 * 
 * <img src="Internet-Control-Message-Protocol-Timestamp-or-Timestamp-Reply-Message.png" alt="Timestamp or Timestamp Reply Message" width="256">
 * 
 * | Field | Target | Description |
 * | ----- | ------ | ----------- |
 * | Addresses | IP | The address of the source in a timestamp message will be the destination of the timestamp reply message. To form a timestamp reply message, the source and destination addresses are simply reversed, the type of code changed to 14, and the checksum recomputed. |
 * | Type      | ICMP | 13 for timestamp message; 14 for timestamp reply message |
 * | Code      | ICMP | 0 |
 * | Checksum  | ICMP | The checksum is the 16 bit one's complement of the one complement sum of the ICMP starting with the ICMP Type. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Identifier | ICMP | If code = 0, an identifier to aid in matching timestamp and replies, may be zero. |
 * | Sequence Number | ICMP | If code = 0, a sequence number to aid in matching timestamp and replies, may be zero |
 * 
 * ### Description
 * 
 * The data received (a timestap) in the message is returned in the reply together with an additional timestamp. The timestamp
 * is 32 bits of milliseconds since midnight UT. One use of these timestamps is described by [Millis](https://datatracker.ietf.org/doc/html/rfc778).
 * 
 * The Originate Timestamp is the time the sender last touched the message before sending it, the Receive Timestamp is
 * the time the echoer first touched it on receipt, and the Transmit Timestap is the time the echoer last touched the
 * message on sending it.
 * 
 * If the time is not availabe in milliseconds or cannot be provided with respect to midnight UT then any time can be
 * inserted in a timestamp provided the high order bit of the timestamp is also set to indicate this non-standard value.
 * 
 * The identifier and sequence number may be used by the echo sender to aid in matching the replies with the requests.
 * For example, the identifier might be used like a port in TCP or UDP to identifiy a session, and the sequence number
 * might be incremented on each request sent. The destination returns these same values in the reply.
 * 
 * Code 0 may be received from a gateway or a host.
 * 
 * @subsection      MessageFormats_InformationRequest_or_InformationReplyMessage        Information Request or Information Reply Message
 * 
 * <img src="Internet-Control-Message-Protocol-Information-Request-or-Information-Reply-Message.png" alt="Information Request or Information Reply Message" width="256">
 * 
 * | Field      | Target | Description |
 * | ---------- | ------ | ----------- |
 * | Addresses  | IP     | The address of the source in a information request message will be the destination of the information reply message. To form a information reply message, the source and destination addresses are simply reversed, the type code changed to 16, and the checksum recomputed. |
 * | Type       | ICMP   | 15 for information request message; 16 for information reply message. |
 * | Code       | ICMP   | 0 |
 * | Checksum   | ICMP   | The checksum is the 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type. For computing the checksum, the checksum field should be zero. This checksum may be replaced in the future. |
 * | Identifier | ICMP   | If code = 0, an identifier to aid in matching request and replies, may be zero. |
 * | Sequence Number | ICMP | If code = 0, a sequence number to aid in matching request and replise, may be zero. |
 * 
 * ### Description
 * 
 * This message may be sent with the source network in the IP header source and destination address feilds zero (which
 * means "this" network). The replying IP module should send the reply with the addresses fully specified. This message
 * is a way for a host to find out the number of the network it is on.
 * 
 * The identifier and sequence number be used by the echo sender to aid in matching the replies with the requests.
 * For example, the identifier might be used like a port in TCP or UDP to identify a session, and the sequence number
 * might be incremented on each request sent. The destination returns these same values in the reply.
 * 
 * Code 0 may be received from a gateway or a host.
 * 
 * @subsection  Summary_of_Message_Types    Summary of Message Types
 * 
 * - 0: Echo Reply
 * - 3: Destination Unreachable
 * - 4: Source Quench
 * - 5: Redirect
 * - 8: Echo
 * - 11: Time Exceeded
 * - 12: Parameter Problem
 * - 13: Timestamp
 * - 14: Timestamp Reply
 * - 15: Information Request
 * - 16: Information Reply
 * 
 * @see         [Internet Control Message Protocol](https://datatracker.ietf.org/doc/html/rfc792)
 */