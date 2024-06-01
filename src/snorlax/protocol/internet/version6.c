/**
 * @file        snorlax/protocol/internet/version6.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       May 25, 2024
 */

#include <arpa/inet.h>

#include "version6.h"

#include "../internet.h"

#ifdef    SNORLAX_DEBUG
extern void snorlax_protocol_internet_version6_debug(FILE * stream, const uint8_t * datagram) {
    const snorlax_protocol_internet_version6_t * internet = (snorlax_protocol_internet_version6_t *) datagram;

    uint32_t prefix = ntohl(internet->prefix);

    fprintf(stream, "| internet version 6 ");
    fprintf(stream, "| %d ", snorlax_protocol_internet_version_get(datagram));
    fprintf(stream, "| %02x ", snorlax_protocol_internet_version6_traffic_class_get(prefix));
    fprintf(stream, "| %05x ", snorlax_protocol_internet_version6_flow_label_get(prefix));
    fprintf(stream, "| % 6d ", ntohs(internet->length));
    fprintf(stream, "| % 3d ", internet->next);
    fprintf(stream, "| % 3d ", internet->limit);
    fprintf(stream, "| %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x ", ntohs(internet->source[0]),
                                                                  ntohs(internet->source[1]),
                                                                  ntohs(internet->source[2]),
                                                                  ntohs(internet->source[3]),
                                                                  ntohs(internet->source[4]),
                                                                  ntohs(internet->source[5]),
                                                                  ntohs(internet->source[6]),
                                                                  ntohs(internet->source[7]));
    fprintf(stream, "| %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x ", ntohs(internet->destination[0]),
                                                                  ntohs(internet->destination[1]),
                                                                  ntohs(internet->destination[2]),
                                                                  ntohs(internet->destination[3]),
                                                                  ntohs(internet->destination[4]),
                                                                  ntohs(internet->destination[5]),
                                                                  ntohs(internet->destination[6]),
                                                                  ntohs(internet->destination[7]));
    fprintf(stream, "|\n");

    snorlax_todo("check");
}
#endif // SNORLAX_DEBUG

/**
 * @page        InternetProtocolVersion6Specification       Internet Protocol, Version 6 (IPv6) Specification
 * 
 * @tableofcontents
 * 
 * @section     Introduction        1. Introduction
 * 
 * IP version 6 (IPv6) is a new version of the Interner Protocol (IP), designed as the successor to [IP version
 * 4 (IPv4)](https://datatracker.ietf.org/doc/html/rfc791). The changes from IPv4 to IPv6 fall primarily into
 * the following categories:
 * 
 * - Expanded Addressing Capabilities
 * 
 *   IPv6 increases the IP address size from 32 bits to 128 bits, to support more levels of addressing hierarchy,
 *   a much greater number of addressable nodes, and simpler autoconfiguration of addresses. The scalability of
 *   multicast addresses. And a new type of address called an "anycast address" is defined; it is used to send
 *   a packet to any one of a group of nodes.
 * 
 * - Header Format Simplication
 * 
 *   Some IPv4 header fields have been dropped or made optional, to reduce the common-cast processing cost of
 *   packet handling and to limit the bandwidth cost of the IPv6 header.
 * 
 * - Improved Support for Extensions and Options
 *   
 *   Changes in the way IP header options are encoded allows for more efficient forwarding, less stringent
 *   limits on the length of options, and greater flexibility for introducing new options in the future.
 * 
 * - Flow Labeling Capability
 * 
 *   A new capability is added to enable the labeling of sequences of packets that the sender requests to be
 *   treated in the network as a single flow.
 * 
 * - Authentication and Privacy Capabilities
 * 
 *   Extensions to support authentication, data integrity, and (optional) data confidentially are specified
 *   for IPv6.
 * 
 * This document specifies the basic IPv6 header and the initially defined IPv6 extension headers and options.
 * It also discusses packet size issues, the semantics of flow labels and traffic classes, and the effects
 * of IPv6 on upper-layer protocols. The format and semantics of IPv6 addresses are specified separately
 * in [IP Version 6 Addressing Architecture](https://datatracker.ietf.org/doc/html/rfc4291).
 * The IPv6 version of ICMP, which all IPv6 implementations are required to include, is specified in
 * [Internet Control Message Protocol (ICMPv6) for the Internet Protocol Version 6 (IPv6) Specification](https://datatracker.ietf.org/doc/html/rfc4443).
 * 
 * The data transmission order for IPv6 is the same as for IPv4 as defined in [Appendix B of Internet Protocol](https://datatracker.ietf.org/doc/html/rfc791).
 * 
 * > Note: As this document obsoletes [Internet Protocol, Version 6 (IPv6) Specification](https://datatracker.ietf.org/doc/html/rfc2460),
 * > any document referenced in this document that includes pointers to [Internet Protocol, Version 6 (IPv6) Specification](https://datatracker.ietf.org/doc/html/rfc2460)
 * > should be interpreted as referencing this document.
 * 
 * @section         Terminology         2. Terminology
 * 
 * | Term | Description |
 * | ---- | ----------- |
 * | node | a device that implement IPv6 |
 * | router | a node that forwards IPv6 packets not explicitly addressed to itself. |
 * | host   | any node that is not a router. |
 * | upper layer | a protocol layer immediately above IPv6. Examples are transport protocols such as TCP and UDP, control protocols such as ICMP, routing protocols such as OSPF, and internet-layer or lower-layer protocols being "tunneled" over (i.e., encapsulated in) IPv6 such as Internetwork Packet Exchange (IPX), AppleTalk, or IPv6 itself. |
 * | link | a communication facility or medium over which nodes can communicate at the link layer, i.e., the layer immediately below IPv6. Examples are Ethernets (simple or bidged); PPP links; X.25, Frame Relay, or ATM networks; and internet-layer or higher-layer "tunnels", such as tunnels over IPv4 or IPv6 itself. |
 * | neighbors | nodes attached to the same link. |
 * | interface | a node's attachment to a link. |
 * | address | an IPv6-layer identifier for an interface or a set of interfaces. |
 * | packet | an IPv6 header plus payload. |
 * | link MTU | the maximum transmission unit, i.e., maximum packet size in octets, that can be conveyed over a link. |
 * | path MTU | the minimum link MTU of all the links in a path between a source node and a destination node. |
 * 
 * > Note: it is possible for a device with multiple interfaces to be configured to forward non-self-destined
 * > packets arriving from some set (fewer than all) of its interfaces and to discard non-self-destined packets
 * > arriving from its other interfaces. Such a device must obey the protocol requirements for routers when
 * > receiving packets from, and interacting with neighbors over, the former (forwarding) interfaces.
 * > It must obey the protocol requirements for hosts when receiving packets from, and interacting with
 * > neighbors over, the latter (non-forwarding) interfaces.
 * 
 * @section     IPv6_Header_Format      3. IPv6 Header Format
 * 
 * <img src="Internet-Protocol-Version6-Header-Format.png" alt="IPv6 Header Format" width="360">
 * 
 * - Version
 * 
 *   4 bit Internet Protocol version number = 6
 * 
 * - Traffic Class
 * 
 *   8 bit Traffic Class field.
 * 
 * - Flow Label
 * 
 *   20 bit flow label.
 * 
 * - Payload Length
 * 
 *   16 bit unsigned integer. Length of the IPv6 payload, i.e., the rest of the packet following this IPv6
 *   header, in octets. (Note that any extension headers present are considered part of the payload, i.e.,
 *   included in the length count.)
 * 
 * - Next Header
 * 
 *   8 bit selector. Identifies the type of header immediately following the IPv6 header. Uses the same
 *   values as the [IPv4 Protocol field](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml).
 * 
 * - Hop Limit
 * 
 *   8 bit unsigned integer. Decremented by 1 by each node that forwards the packet. When forwarding, the 
 *   packet is discarded if Hop Limit was zero when received or is decremented to zero. A node that is the
 *   destination of a packet should not discard a packet with Hop Limit equal to zero; it should process the
 *   packet normally.
 * 
 * - Source Address
 * 
 *   128 bit address of the originator of the packet. See [IP Version 6 Addressing Architecture](https://datatracker.ietf.org/doc/html/rfc4291)
 * 
 * - Destination Address
 * 
 *   128 bit address of the intended recipient of the packet (possibly not the ultimate recipient, if a Routing
 *   header is present). See [IP Version 6 Addressing Architecture](https://datatracker.ietf.org/doc/html/rfc4291) and Section 4.4.
 * 
 * @section         IPv6_Extension_Headers      4. IPv6 Extension Headers
 * 
 * In IPv6, optional internet-layer information is encoded in separate headers that may be placed between
 * the IPv6 header and the upper layer header in a packet. There is a small number of such extension headers,
 * each one identified by a distinct Next Header value.
 * 
 * Extension headers are numbered from [IANA IP Protocol Numbers](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml),
 * the same values used for IPv4 and IPv6. When processing a sequence of Next Header values in a packet, the
 * first one that is not an extension header [Internet Protocol Version 6 (IPv6) Parameters](https://www.iana.org/assignments/ipv6-parameters/ipv6-parameters.xhtml)
 * indicates that the next item in the packet is the corresponding upper layer header. A special
 * "No Next Header" value is used if there is no upper-layer header.
 * 
 * As illustrated in these examples, an IPv6 packet may carry zero, one, or more extension headers,
 * each identified by the Next Header field of the preceding header:
 * 
 * <img src="Internet-Protocol-Version6-Next-Header.png" alt="Next Header" width="360">
 * 
 * Extension headers (except for the Hop-by-Hop Options header) are not processed, inserted, or deleted by
 * any node along a packet's delivery path, until the packet reaches the node (or each of the set of nodes,
 * in the case of multicast) identified in the Destination Address field of the IPv6 header.
 * 
 * The Hop-by-Hop Options header is not inserted or deleted, but may be examined or processed by any node
 * along a packet's delivery path, until the packet reaches the node (or each of the set of nodes, in the case
 * of multicast) identified in the Destination Address field of the IPv6 header. The Hop-by-Hop Options header,
 * when present, must immediately follow the IPv6 header. Its presence is indicated by the value zero in the
 * Next Header field of the IPv6 header.
 * 
 * > Note
 * >
 * > While [Internet Protocol, Version 6 (IPv6) Specification](https://datatracker.ietf.org/doc/html/rfc2460)
 * > required that all nodes must examine and process the Hop-by-Hop Options header, it is now expected that
 * > nodes along a packet's delivery path only examine and process the Hop-by-Hop Options header if explicitly
 * > configured to do so.
 * 
 * At the destination node, normal demultiplexing on the Next Header field of the IPv6 header invokes the module
 * to process the first extension header, or the upper-layer header if no extension header is present.
 * The contents and semantics of each extension header determine whether or not to proceed to the next
 * header. Therefore, extension headers must be processed strictly in the order they appear in the packet;
 * a receiver must not, for example, scan through a packet looking for a particular kind of extension header
 * and process that header prior to processing all preceding ones.
 * 
 * If, as a result of processing a header, the destination node is required to proceed to the next header
 * but the Next Header value in the current header is unrecognized by the node, it should discard the packet
 * and send an ICMP Parameter Problem message to the source of the packet, with an ICMP Code value of 1
 * ("unrecognized Next Header type encountered") and the ICMP Pointer field containing the offset of the 
 * unrecognized value within the original packet. The same action should be taken if a node encounters
 * a Next Header value of zero in any header other than an IPv6 header.
 * 
 * Each extension header is an integer multiple of 8 octets long, in order to retain 8 octet alignment
 * for subsequent headers. Multi-octet fields within each extension header are aligned on their natural
 * boundaries, i.e., fields of width n octets are placed at aon integer multiple of n octets from the
 * start of the header, for n = 1, 2, 4, or 8.
 * 
 * A full implementation of IPv6 includes implementation of the following extension headers:
 * 
 * - Hop-by-Hop Options
 * - Fragment
 * - Destination Options
 * - Routing
 * - Authentication
 * - Encapsulating Security Payload
 * 
 * The first four are specified in this document; the last two are specified in [IP Authentication Header](https://datatracker.ietf.org/doc/html/rfc4302)
 * and [IP Encapsulating Security Payload (ESP)](https://datatracker.ietf.org/doc/html/rfc4303),
 * respectively. The current list of IPv6 extension headers can be found at [Internet Protocol Version 6 (IPv6) Parameters](https://www.iana.org/assignments/ipv6-parameters/ipv6-parameters.xhtml).
 * 
 * @subsection      IPv6_Extension_Headers_Extension_Header_Order   4.1. Extension Header Order
 * 
 * When more than one extension header is used in the same packet, it is recommended that those headers
 * appear in the following order:
 * 
 * - IPv6 header
 * - Hop-by-Hop Options header
 * - Destination Options header
 * 
 *   for options to be processed by the first destination that appears in the IPv6 Destination Address field
 *   plus subsequent destinations listed in the Routing header.
 * 
 * - Routing header
 * - Fragment header
 * - Authentication header
 * 
 *   additional recoomendations regarding the relative order of the Authentication and Encapsulating Security
 *   Payload headers are given in [IP Encapsulating Security Payload (ESP)](https://datatracker.ietf.org/doc/html/rfc4303).
 * 
 * - Encapsulating Security Payload header 
 * 
 *   additional recoomendations regarding the relative order of the Authentication and Encapsulating Security
 *   Payload headers are given in [IP Encapsulating Security Payload (ESP)](https://datatracker.ietf.org/doc/html/rfc4303).
 * 
 * - Destination Options header
 * 
 *   for options to be processed only by the final destination of the packet.
 * 
 * - Upper-Layer header
 * 
 * Each extension header should occur at most once, except for the Destination Options header, which should
 * occur at most twice (once before a Routing header and once before the upper-layer header).
 * 
 * If the upper-layer header is another IPv6 header (in the case of IPv6 being tunneled over or encapsulated
 * in IPv6), it may be followed by its own extension headers, which are separately subject to the same 
 * ordering recommendations.
 * 
 * If and when other extension headers are defined, their ordering constraints relative to the above listed
 * headers must be specified.
 * 
 * IPv6 nodes must accept and attempt to process extension headers in any order and occurring any number of
 * times in the same packet, except for the Hop-by-Hop Options header, which is restricted to appear immediately
 * after an IPv6 header only. Nonetheless, it is strongly advised that sources of IPv6 packets adhere to the
 * above recommended order until and unless subsequent specifications revise that recommendation.
 * 
 * @subsection      IPv6_Extension_Headers_Options      4.2. Options
 * 
 * Two of the currently defined extension headers specified in this document -- Hop-by-Hop Options header
 * and the Destination Options header -- carry a variable number of "options" that are type-length-value (TLV)
 * encoded in the following format:
 * 
 * <img src="Internet-Protocol-Version6-Options-Type-Length-Value.png" alt="Options Type-Length-Value" width="360">
 * 
 * | Field | Description |
 * | ----- | ----------- |
 * | Option Type | 8 bit identifier of the type of option. |
 * | Option Data Len | 8 bit unsigned integer. Length of the Option field of this option, in octets. |
 * | Option Data | Variable-length field. Option-Type-specific data. |
 * 
 * The sequence of options within a header must be processed strictly in the order they appear in the header;
 * a receiver must not, for example, scan through the header looking for a particular kind of option and
 * process that option prior to processing all preceding ones.
 * 
 * The Option Type identifiers are internally encoded such that their highest-order 2 bits specify the action
 * that must be taken if the processing IPv6 node does not recognize the Option Type:
 * 
 * - 00 - skip over this option and continue procesing the header.
 * - 01 - discard the packet.
 * - 10 - discard the packet and, regardless of whether or not the packet's Destination Address was multicast
 *   address, send an ICMP Parameter Problem, Code 2, message to the packet's Source Address, pointing to the
 *   unrecognized Option Type.
 * - 11 - discard the packet and, only if the packet's Destination Address was not a multicast address, send
 *   an ICMP Parameter Problem, Code 2, message to the packet's Source Address, pointing to the unrecoginized
 *   Option Type.
 * 
 * The third-highest-order bit of the Option Type specifies whether or not the Option Data of that option can
 * change en route to the packet's final destination. When an Authentication header is present in the packet,
 * for any option whose data may change en route, its entire Option Data field must be treated as zero-value
 * octets when computing or verifying the packet's authenticating value.
 * 
 * - 0 - Option Data does not change en route
 * - 1 - Option Data may change en route
 * 
 * The three high-order bits described above are to be treated as part of the Option Type, not independent of
 * the Option Type. That is, a particular option is identified by a full 8 bit Option Type, not just the
 * low-order 5 bits of an Option Type.
 * 
 * The same Option Type numbering space is used for both the Hop-by-Hop Options header and the Destination
 * Options header. However, the specification of a particular option may restrict its use to only one of
 * those two headers.
 * 
 * Individual options may have specific alignment requirements, to ensure that multi-octet values within
 * Option Data fields fall on natural boundaries. The alignment requirement of an option is specified using
 * the notation xn + y, meaning the Option Type must appear at an integer multiple of x octets from the 
 * start of the header, plus y octets. For example:
 * 
 * - 2n: means any 2-octet offset from the start of the header.
 * - 8n + 2: means any 8-octet offset from the start of the header, plus 2 octets.
 * 
 * There are two padding options that are used when necessary to align subsequent options and to pad out the
 * containing header to a multiple of 8 octets in length. These padding options must be recognized by all IPv6
 * implementations:
 * 
 * ### Pad1 option (alignment requirement: none)
 * 
 * <img src="Internet-Protocol-Version6-Option-Pad1.png" alt="Option Pad1" width="128">
 * 
 * > Note: The format of the Pad1 option is a special case -- it does not have length and value fields.
 * 
 * The Pad1 option is used to insert 1 octet of padding into the Options area of a header. If more than one
 * octet of padding is required, the PadN option, described next, should be used, rather than multiple Pad1
 * options.
 * 
 * ### PadN option (alignment requirement: none)
 * 
 * <img src="Internet-Protocol-Version6-Option-PadN.png" alt="Option PadN" width="128">
 * 
 * The PadN option is used to insert two or more octets of padding into the Options area of a header. 
 * For N octets of padding, the Opt Data Len field contains the value N - 2, and the Option Data consists
 * of N - 2 zero-valued octets.
 * 
 * Appendix A contains formatting guidelines for designing new options.
 * 
 * @subsection  IPv6_Extension_Headers_Hop_by_Hop_Options_Header    4.3. Hop-by-Hop Options Header
 * 
 * The Hop-by-Hop Options header is used to carry optional information that may be examined and processed
 * by every node along a packet's delivery path. The Hop-by-Hop Options header is identified by a Next
 * Header value of 0 in the IPv6 header and has the following format:
 * 
 * <img src="Internet-Protocol-Version6-Hop-by-Hop-Options.png" alt="Hop-by-Hop Options" alt="256">
 * 
 * | Field | Description |
 * | ----- | ----------- |
 * | Next Header | 8 bit selector. Identifies the type of header immediately following the Hop-by-Hop Options header. Uses the same values as the IPv4 Protocol field [Protocol Numbers](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml). |
 * | Hdr Ext Len | 8 bit unsigned integer. Length of the Hop-by-Hop Options header in 8 octet units, not including the first 8 octets. |
 * | Options     | Variable-length field, of length such that the complete Hop-by-Hop Options header is an integer multiple of 8 octets long. Contains one or more TLV-encoded options, as described in Section 4.2. |
 * 
 * The only hop-by-hop options defined in this document are the Pad1 and PadN options specifeid in Section 4.2.
 * 
 * @subsection  IPv6_Extension_Headers_Routing_Header   4.4. Routing Header
 * 
 * The Routing header is used by an IPv6 source to list one or more intermediate nodes to be "visited" on the
 * way to a packet's destination. This function is very similar to IPv4's Loose Source and Record Route option.
 * The Routing header is identified header and has the following format:
 * 
 * <img src="Internet-Protocol-Version6-Option-Routing-Header.png" alt="Routing Header" width="360">
 * 
 * | Field | Description |
 * | ----- | ----------- |
 * | Next Header | 8 bit selector. Identifies the type of header immediately following the Routing header. Uses the same values as the [IPv4 Protocol field](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml). |
 * | Hdr Ext Len | 8 bit unsigned integer. Length of the Routing header in 8 octet units, not including the first 8 octets. |
 * | Routing Type | 8 bit identifier of a particular Routing header variant. |
 * | Segments Left | 8 bit unsigned integer. Number of route segments remaining, i.e., number of explicitly listed intermediate nodes still to be visited before reaching the final destination. |
 * | tpe-specific data | Variable-length field, of format determined by the Routing Type, and of length such that the complete Routing header is an integer multiple of 8 octets long. |
 * 
 * If, while processing a received packet, a node encounters a Routing header with an unrecognized Routing Type
 * value, the required behavior of the node depends on the value of the Segments Left field, as follows:
 * 
 * - If Segment Left is zero, the node must ignore the Routing header and proceed to process the next header
 *   in the packet, whose type is identified by the Next Header field in the Routing header.
 * - If Segment Left is non-zero, the node must discard the packet and send an ICMP Parameter Problem, Code 0,
 *   message to the packet's Source Address, pointing to the unrecognized Routing Type.
 * 
 * If, after processing a Routing header of a received packet, an intermediate node determines that the packet
 * is to be forwarded onto a link whose link MTU is less than the size of the packet, the node must discard
 * the packet and send an ICMP Packet Too Big message to the packet's Source Address.
 * 
 * The currently defined IPv6 Routing Headers and their status can be found at [Internet Protocol Version 6 (IPv6) Parameters: Routing Types](https://www.iana.org/assignments/ipv6-parameters/ipv6-parameters.xhtml#ipv6-parameters-3).
 * Allocation guidelines for IPv6 Routing Headers can be found in [IANA Allocation Guidelines for the IPv6 Routing Header](https://datatracker.ietf.org/doc/html/rfc5871).
 * 
 * @subsection  IPv6_Extension_Headers_Fragment_Header      4.5. Fragment Header
 * 
 * The Fragment header is used by an IPv6 source to send a packet larger than would fit in the path MTU to
 * its destination. (Note: unlike IPv4, fragmentation in IPv6 is performed only by source nodes, not by
 * routers along a packet's delivery path -- see Section 5). The Fragment header is identified by a Next
 * Header value of 44 in the immediately preceding header and has the following format:
 * 
 * <img src="Internet-Protocol-Version6-Option-Fragment-Header.png" alt="Fragment Header" width="360">
 * 
 * | Field           | Description |
 * | --------------- | ----------- |
 * | Next Header     | 8 bit selector. Identifies the initial header type of the Fragmentable Part of the original packet. Uses the same values as the [IPv4 Protocol field](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml). |
 * | Reserved        | 8 bit reserved field. Initialized to zero for transmission; ignored on reception. |
 * | Fragment Offset | 13 bit unsigned integer. The offset, in 8 octet units, of the data following this header, relative to the start of the Fragmentable Part of the original packet. |
 * | Res             | 2 bit reserved field. Initialized to zero for transmission; ignored on reception. |
 * | M Flag          | 1 = more fragments; 0 = last fragment. |
 * | Identification  | 32 bits |
 * 
 * In order to send a packet that is too large to fit in the MTU of the path to its destination, a source node may
 * divide the packet into fragments and send each fragment as a separate packet, to be reassembled at the receiver.
 * 
 * For every packet that is to be fragmented, the source node generates an Identification value. The Identification
 * must be different than that of any other fragmented packet sent recently with the same Source Address and
 * Destination Address. If a Routing header is present, the Destination Address of concern is that of the final
 * destination.
 * 
 * > "recently" means within the maximum likely lifetime of a packet, including transit time from source to
 * > destination and time spent awaiting reassembly with other fragments of the same packet. However, it is
 * > not required that a source node knows the maximum packet lifetime. Rather, it is assumed that the 
 * > requirement can be met by implementaing an algorithm that results in a low identification reuse frequency.
 * > Examples of algorithms that can meet this requirement are described in [Security Implications of Predictable Fragment Identification Values](https://datatracker.ietf.org/doc/html/rfc7739).
 * 
 * The initial, large, unfragmented packet is referred to as the "original packet", and it is considered to 
 * consist of three parts, as illustrated:
 * 
 * ### Original Packet
 * 
 * <img src="Internet-Protocol-Version6-Fragment-Original-Packet.png" alt="Fragment Original Packet" width="360">
 * 
 * The Per-Fragment headers must consist of the IPv6 header plus any extension headers that must be processed by
 * nodes en route to the destination, that is, all headers up to and including the Routing header if present,
 * else the Hop-by-Hop Options header if present, else no extension headers.
 * 
 * The Extension headers are all other extension headers that are not included in the Per-Fragment headers
 * part of the packet. For this purpose, the Encapsulating Security Payload (ESP) is not considered an extension
 * header. The Upper-Layer header is the first upper-layer header that is not an IPv6 extension header. Examples
 * of upper-layer headers include TCP, UDP, IPv6, IPv6, ICMPv6, and as noted ESP.
 * 
 * The Fragmentable Part consists of the rest of the packet after the upper layer header or after any header
 * (i.e., initial IPv6 header or extension header) that contains a Next Header value of No Next Header.
 * 
 * The Fragmentable Part of the original packet is divided into fragments. The lengths of the fragments must be
 * chosen such that the resulting fragment packets fit within the MTU of the path to the packet's destination(s).
 * Each complete fragment, except possibly the last ("rightmost") one, is an integer multiple of 8 octets long.
 * 
 * The fragments are transmitted in separate "fragment packets" as illustrated:
 * 
 * Original packet:
 * 
 * <img src="Internet-Protocol-Version6-Fragment-Original-Packet-Example.png" alt="Original Packet" width="360">
 * 
 * Fragment packets:
 * 
 * <img src="Internet-Protocol-Version6-Fragment-Packets-Example.png" alt="Fragment Packets" width="360">
 * 
 * The first fragment packet is composed of:
 * 
 * 1. The Per-Fragment headers of the original packet, with the Payload Length of the original IPv6 header changed
 *    to contain the length of this fragment packet only (excluding the length of the IPv6 header itself),
 *    and the Next Header field of the last header of the Per-Fragment headers changed to 44.
 * 2. A Fragment header containing:
 * 
 *    The Next Header value that identifies the first header after the Per-Fragment headers of the original packet.
 * 
 *    A Fragment Offset containing the offset of the fragment, in 8 octet units, relative to the start of the
 *    Fragmentable Part of the original packet. The Fragment Offset of the first ("leftmost") fragment is 0.
 * 
 *    An M flag value of 1 as this is the first fragment.
 * 
 *    The Identification value generated for the original packet.
 * 3. Extension headers, if any, and the Upper-Layer header. These headers must be in the first fragment. 
 *    Note: This restricts the size of the headers through the Upper-Layer header to the MTU of the path to
 *    the packet's destinations(s).
 * 4. The first fragment.
 * 
 * The subsequent fragment packets are composed of:
 * 
 * 1. The Per-Fragment headers of the original packet, with the Payload Length of the original IPv6 header changed
 *    to contain the length of this fragment packet only (excluding the length of the IPv6 header itself), and
 *    the Next Header field of the last header of the Per-Fragment headers changed to 44.
 * 2. A Fragment header containing:
 *    
 *    The Next Header value that identifies the first header after the Per-Fragment headers of the original packet.
 * 
 *    A Fragment Offset containing the offset of the fragment, in 8 octet units, relative to the start of the 
 *    Fragmentable Part of the original packet.
 * 
 *    An M flag value of 0 if the fragment is the last ("rightmost") one, else an M flag value o 1.
 * 
 *    The Identification value generated for the original packet.
 * 3. The fragment itself.
 * 
 * Fragments must not be created that overlap with any other fragments created from the original packet.
 * 
 * At the destination, fragment packets are reassembled into their original, unfragmented form, as illustrated:
 * 
 * reassembled original packet:
 * 
 * <img src="Internet-Protocol-Version6-Fragment-Reassembled-Original-Packet.png" alt="Reassembled Original Packet" width="360">
 * 
 * The following rules govern reassembly:
 * 
 * 1. An original packet is reassembled only from fragment packets that have the same Source Address, Destination
 *    Address, and Fragment Identification.
 * 
 * 2. The Per-Fragment headers of the reassembled packet consists of all headers up to, but not including, the
 *    Fragment header of the first fragment packet (that is, the packet whose Fragment Offset is zero), with
 *    the following two changes:
 * 
 *    1. The Next Header field of the last header of the Per-Fragment headers is obtained from the Next Header
 *       field of the first fragment's Fragment header.
 *    2. The Payload Length of the reassembled packet is computed from the length of the Per-Fragment headers and
 *       the length and offset the last fragment. For example, a formula for computing the Payload Length of the
 *       reassembled original packet is:
 *       
 *       PL.orig = PL.first - FL.first - 8 + (8 * FO.last) + FL.last
 * 
 *       where
 * 
 *       - PL.orig = Payload Length field of reassembled packet.
 *       - PL.first = Payload Length field of first fragment packet.
 *       - FL.first = length of fragment following Fragment header of first fragment packet.
 *       - FO.last = Fragment Offset field of Fragment header of last fragment packet.
 *       - FL.last = length of fragment following Fragment header of last fragment packet.
 * 
 *    3. The Fragmetable Part of the reassembled packet is constructued from the fragments following the
 *       Fragment headers in each of the fragment packets. The length of each fragment is computed by substracting
 *       from the packet's Payload Length the length of the headers between the IPv6 header and fragment itself;
 *       its relative position in Fragmentable Part is computed from its Fragment Offset value.
 *    4. The Fragment header is not present in the final, reassembled packet.
 *    5. If the fragment is a whole datagram (that is, both the Fragment Offset field and the M flag are zero),
 *       then it does not need any further reassembly and should be processed as a fully reassembled packet
 *       (i.e., updating Next Header, adjust Payload Length, removing the Fragment header, etc.). Any other
 *       fragments that match this packet (i.e., the same IPv6 Source Address, IPv6 Destination Address, and
 *       Fragment Identification) should be processed independently.
 * 
 * The following error conditions may arise when reassembling fragmented packets:
 * 
 * - If insufficient fragments are received to complete reassembly of a packet within 60 seconds of the reception
 *   of the first arriving fragment of that packet, reassembly of that packet must be abondoned and all the 
 *   fragments that have been received for that packet must be discarded. If the first fragment (i.e., the one
 *   with a Fragment Offset or zero) has been received, an ICMP Time Exceeded -- Fragment Reassembly Time Exceeded
 *   message should be sent to the source of that fragment.
 * - If the length of a fragment, as derived from the fragment packet's Payload Length field, is not a multiple
 *   of 8 octets and the M flag of that fragment is 1, then that fragment must be discarded and an ICMP Parameter
 *   Problem, Code 0, message should be sent to the source of fragment, pointing to the Payload Length field of
 *   the fragment packet.
 * - If the length and offset of a fragment are such that the Payload Length of the packet reassembled from that
 *   fragment would exceeded 65,535 octets, then that fragment must be discarded and an ICMP Parameter Problem,
 *   Code 0, message should be sent to the source of the fragment, pointing to the Fragment Offset field of the
 *   fragment packet.
 * - If the first fragment does not include all headers through an Upper-Layer header, then that fragment should
 *   be discarded and an ICMP Parameter Problem, Code 3, message should be sent to the source of the fragment,
 *   with the Pointer field set to zero.
 * - If any of the fragments being reassembled overlap with any other fragments being reassembled for the same
 *   packet, reassembly of that packet must be abandoned and all the fragments that have been received for that
 *   packet muset be discarded, and no ICMP error messages should be sent.
 * 
 *   It should be noted that fragments may be duplicated in the network. Instead of treating these exact duplicate
 *   fragments as overlapping fragments, an implementation may choose to detect this case and drop exact duplicate
 *   fragments while keeping the other fragments belonging to the same packet.
 * 
 * The following conditions are not expected to occur frequently but are not considered errors if they do:
 * 
 * - The number and content of the headers preceding the Fragment header of different fragments of the same
 *   original packet may differ. Whatever headers are present, prceding the Fragment header in each fragment
 *   packet, are processed when the packets arrive, prior to queueing the fragments for reassembly. Only those
 *   headers in the Offset zero fragment packet are retained in the reassembled packet.
 * 
 * - The Next Header values in the Fragment headers of different fragments of the same original packet may differ.
 *   Only the value from the Offset zero fragment packet is used for reassembly.
 * 
 * - Other fields in the IPv6 header may also vary across the fragments being reassembled. Specifications that 
 *   use these fields may provide additional instructions if the basic mechanism of using the values from the
 *   Offset zero fragment is not sufficient. For example, [Section 5.3. of The Addition of Explicit Congestion Notification (ECN) to IP](https://datatracker.ietf.org/doc/html/rfc3168#section-5.3)
 *   describes how to combine the Explicit Congestion Notification (ECN) bits from different fragments to derive
 *   the ECN bits of the reassembled packet.
 * 
 * @subsection      IPv6_Extension_Headers_Destination_Options_Header   4.6. Destination Options Header
 * 
 * The Destination Options header is used to carry optional information that need be examined only by a packet's
 * destination node(s). The Destination Options header is identified by a Next Header value of 60 in the 
 * immediately preceding header and has the following format:
 * 
 * <img src="Internet-Protocol-Version6-Fragment-Destination-Options-Header.png" alt="Desitnation Options Header" width="360">
 * 
 * - Next Header
 * 
 *   8 bit selector. Identifies the type of header immediately following the Destination Options header. Uses
 *   the same value as the IPv4 Protocol field [Protocol Numbers](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml).
 * 
 * - Hdr Ext Len
 * 
 *   8 bit unsigned integer. Length of the Destination Options header in 8 octet units, not including the first
 *   8 octets.
 * 
 * - Options
 * 
 *   Variable-length field, of length such that the complete Destination Options header is an integer multiple of
 *   8 octets long. (Contains one or more TLV-encoded options, as described in Section 4.2.)
 * 
 * The only destination options defined in this document are the Pad1 and PadN options specified in Section 4.2.
 * 
 * Note that there are two possible ways to encode optional destination information in an IPv6 packet: either
 * as an option in the Destination Options header or as a separate extension header. The Fragment header and
 * the Authentication header are examples of the latter approach. Which approach can be used depends on what action
 * is desired of a destination node that does not understand the optional information:
 * 
 * - If the desired actionis for destination node to discard the packet and, only if the packet's Destination
 *   Address is not a multicast address, send an ICMP Unrecognized Type message to the packet's Source Address,
 *   then the information may be encoded either as a separate header or as an option in the Destination Options
 *   header whose Option Type has the value 11 in its highest-order 2 bits. The choice may depend on such factors
 *   as which takes fewer octets, or which yield better alignment or more efficient parsing.
 * - If any other action is desired, the information must be encoded as an option in the Destination Options header
 *   whose Option Type has the value 00, 01, or 10 in tis highest-order 2 bits, specifying the desired action.
 * 
 * @subsection      IPv6_Extension_Headers_No_Next_Header   4.7. No Next Header
 * 
 * The value 59 in the Next Header field of an IPv6 header of any extension header indicates that there is nothing
 * following that header. If they Payload Length field of the IPv6 header indicates the presence of octets past
 * the end of a header whose Next Header field contains 59, those octets must be ignored and passed on unchanged
 * if the packet is forwarded.
 * 
 * @subsection      IPv6_Extension_Headers_Defining_New_Extension_Headers_and_Options   4.8. Defining New Extension Headers and Options
 * 
 * Defining new IPv6 extension headers is not recommended, unless there are no existing IPv6 extension headers
 * that can be used by specifying a new option for that IPv6 extension header. A proposal to specify a new IPv6
 * extension header must a detailed technical explanation of why an existing IPv6 extension header can not be used
 * for the desired new function. See [A Uniform Format for IPv6 Extension Headers](https://datatracker.ietf.org/doc/html/rfc6564)
 * for additional background information.
 * 
 * Note: New extension headers that require hop-by-hop behavior must not be defined because, as specified in 
 * Section 4 of this document, the only extension header that has hop-by-hop behavior is the Hop-by-Hop Options
 * header.
 * 
 * New hop-by-hop options are not recommended because nodes may be configured to ignore the Hop-by-Hop Options
 * header, drop packets containing a Hop-by-Hop Option header, or assign packets containing a Hop-by-Hop Options
 * header to a slow processing path. Designers considering defining new hop-by-hop options needs to be aware of
 * this likely behavior. There has to be a very clear justification why any new hop-by-hop option is needed before
 * it is standardized.
 * 
 * Instead of defining new extension headers, it is recommended that the Destination Options header is used to
 * carry optional information that must be examined only by a packet's destination node(s), because they provide
 * better handling and backward compatibility.
 * 
 * If new extension headers are defined, they need to use the following format:
 * 
 * <img src="Internet-Protocol-Version6-Option-Define-Extensio-Header.png" alt="Define Extension Header" width="360">
 * 
 * | Field | Description |
 * | ----- | ----------- |
 * | Next Header | 8 bit selector. Identifies the type of header immediately following the extension header. Uses the same values as the IPv4 Protocol field [Protocol Numbers](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml). |
 * | Hdr Ext Len | 8 bit unsigned integer. Length of the Destination Options header in 8 octet units, not including the first 8 octets. |
 * | Header Sepcific Data | Variable-length field. Fields specific to the extension header. |
 * 
 * @section     PacketSizeIssues        5. Packet Size Issues
 * 
 * IPv6 requieres that every link in the Internet have an MTU of 1280 octets or greater. This is known as the IPv6
 * minimum link MTU. On any link that cannot convey a 1280 octet packet in one piece, link-specific fragmentation
 * and reassembly must be provided at a layer below IPv6.
 * 
 * Links taat have a configurable MTU (for example, ppp links [The Point-to-Point Protocol (PPP)](https://datatracker.ietf.org/doc/html/rfc1661))
 * must be configured to have an MTU of at least 1280 octets; it is recommended that they be configured with an
 * MTU of 1500 octets or greater, to accommodate possible encapsulations (i.e., tunneling) without incurring
 * IPv6-layer fragmentation.
 * 
 * From each link to which a node is directly attached, the node must be able to accept packets as large as that
 * link's MTU.
 * 
 * It is strongly recommended that IPv6 nodes implement Path MTU Discovery [Path MTU Discovery for IP version 6](https://datatracker.ietf.org/doc/html/rfc8201),
 * in order to discover and take advantage of path MTUs greater than 1280 octets. However, a miinmal IPv6 
 * implementation (e.g., in a boot ROM) may simply restrict itself to sending packets no larger than 1280 octets,
 * and imit implementation of Path MTU Discovery.
 * 
 * In order to send a packet larger than a path's MTU, a node may use IPv6 Fragment header to fragment the packet
 * at the source and have it reassembled at the destination(s). However, the use of such fragmentation is discouraged
 * in any application that is able to adjust its packets to fit the measured path MTU (i.e., down to 1280 octets).
 * 
 * A node must be able to accept a fragmented packet that, after reassembly, is as large as 1500 octets. A node
 * is permitted to accept fragmented packets that reassemble to more than 1500 octets. An upper-layer protocol
 * or application that depends on IPv6 fragmentation to send packets larger than the MTU of a path should not
 * send packets larger than 1500 octets unless it has assurance that the destination is capable of reassembling
 * packets of that larger size.
 * 
 * @section     FlowLabels      6. Flow Labels
 * 
 * The 20 bit Flow Label field in the IPv6 header is used by a source to label sequences of packets to be treated in
 * the network as a single flow.
 * 
 * The current definition of the IPv6 Flow Label can be found in [IPv6 Flow Label Specification](https://datatracker.ietf.org/doc/html/rfc6437).
 * 
 * @section     TrafficClasses      7. Traffic Classes
 * 
 * The 8 bit Traffic Class field in the IPv6 header is used by the network for traffic management. The value of
 * the Traffic Class bits in a received packet or fragment might be different from the value sent by the packet's
 * source.
 * 
 * The current use of the Traffic Class field for Differentiated Services and Explicit Congestion Notification
 * is specified in [Definition of the Differentiated Services Field (DS Field) in the IPv4 and IPv6 Headers](https://datatracker.ietf.org/doc/html/rfc2474)
 * and [The Addition of Explicit Congestion Notification (ECN) to IP](https://datatracker.ietf.org/doc/html/rfc3168).
 * 
 * @section     UpperLayerProtocolIssues    8. Upper-Layer Protocol Issues
 * 
 * @subsection  UpperLayerProtocolIssues_Upper-Layer Checksums       8.1. Upper-Layer Checksums
 * 
 * Any transport or other upper-layer protocol that includes the addresses from the IP header in its checksum
 * computation must be modified for use over IPv6, to include that 128 bit IPv6 addresses instead of 32 bit
 * IPv4 addresses. In particular, the following illustration shows the TCP and UDP "pseudo-header" for IPv6:
 * 
 * <img src="Internet-Protocol-Version6-Pseudo-Header.png" alt="Pseudo Header" width="360">
 * 
 * - If the IPv6 packet contains a Routing header, the Destination Address used in the pseudo-header it that of
 *   the final destination. At the originating node, that address will be in the laste element of the Routing header;
 *   at the recipient(s), that address will be in the Destination Address field of the IPv6 header.
 * - The Next Header value in the pseudo-header identifies the upper-layer protocol (e.g., 6 for TCP or 17 for UDP).
 *   It will differ from the Next Header value int the IPv6 header if there are extension headers between the IPv6
 *   header and the upper-layer header.
 * - The Upper-Layer Packet Length in the pseudo-header is the length of the upper-layer header and data (e.g.m
 *   TCP header plus TCP Data). Some upper-layer protocols carry their own length information (e.g., the
 *   Length field in the UDP header); for such protocols, that is the length used in the pseudo-header. Other
 *   protocols (such as TCP) do not carry their own length information, in which case the length used in the
 *   pseudo-header is the Payload Length from the IPv6 header, minus the length of any extension headers present
 *   between the IPv6 header and the upper-layer header.
 * - Unlike IPv4, the default behavior when UDP packets are originated by an IPv6 node is that the UDP checksum
 *   is not optional. That is, whenever originating a UDP packet, an IPv6 node must compute a UDP checksum
 *   over the packet and the pseudo-header, and, if that computation yields a result of zero, it must be
 *   changed to hex FFFF for placement in the UDP header. IPv6 receivers must discard UDP packets containing a 
 *   zero checksum and should log the error.
 * - As an exception to the default behavior, protocols that use UDP as a tunnel encapsulation may enable 
 *   zero-checksum mode for a specific port (or set of ports) for sending and/or receiving. Any node implementing
 *   zero-checksum mode must follow the requirements specified in [Applicability Statement for the Use of IPv6 UDP Datagrams with Zero Checksums](https://datatracker.ietf.org/doc/html/rfc6936).
 * 
 * The IPv6 version of ICMP [Internet Control Message Protocol (ICMPv6) for the Internet Protocol Version 6 (IPv6) Specification](https://datatracker.ietf.org/doc/html/rfc4443)
 * includes the above pseudo-header in its checksum computation; this is a change from the IPv4 version of ICMP,
 * which does not include a pseudo-header in its checksum. The reason for the change is to protect ICMP from
 * misdelivery or corruption of those fields of the IPv6 header on which it depends, which, unlike IPv4, are
 * not covered by an internet-layer checksum. The Next Header field in the pseudo-header for ICMP contains the
 * value 58, which identifies the IPv6 version of ICMP.
 * 
 * @subsection  UpperLayerProtocolIssues_Maximum_Packet_Lifetime        8.2. Maximum Packet Lifetime
 * 
 * Unlike IPv4, IPv6 nodes are not required to enforce maximum packet lifetime. That is the reason the IPv4
 * "Time-to-Live" field was renamed "Hop Limit" in IPv6. In practice, very few, if any, IPv4 implementations
 * conform to the requirement that they limit packet lifetime, so this is not a change in practice. Any 
 * upper-layer protocol that relies on the internet layer (whether IPv4 or IPv6) to limit packet lifetime
 * ought to be upgraded to provide its own mechanisms for detecting and discarding obsolete packets.
 * 
 * @subsection  UpperLayerProtocolIssues_Maximum_Upper_Layer_Payload_Size   8.3. Maximum Upper-Layer Payload Size
 * 
 * When computing the maximum payload size available for upper-layer data, an upper-layer protocol must take into
 * account the larger size of the IPv6 header relative to the IPv4 header. For example in IPv4, TCP's Maximum
 * Segment Size (MSS) option is computed as the maximum packet size (a default value or a value learned through
 * Path MTU Discovery) minus 40 octets (20 octets for the minimum-length IPv4 header and 20 octets for the
 * minimum-length TCP header). When using TCP over IPv6, the MSS must be computed as the maximum packet size
 * minus 60 octets, because the minimum-length IPv6 header (i.e., an IPv6 header with no extension headers) is
 * 20 octets longer than a minimum-length IPv4 header.
 * 
 * @subsection  UpperLayerProtocolIssues_Responding_to_Packets_Carrying_Routing_Headers 8.4. Responding to Packets Carrying Routing Headers
 * 
 * When an upper-layer protocol sends one or more packets in response to a received packet that included a Routing
 * header, the response packet(s) must not include a Routing header that was automatically derived by "reversing"
 * the received Routing header unless the integrity and authenticity or the received Source Address and Routing
 * header have been verified (e.g., via the use of an Authentication header in the received packet). In other 
 * words, only the following kinds of packets are permitted in response to a received packet bearing a Routing
 * header:
 * 
 * - Response packets that do not carry Routing headers.
 * - Response packets that carry Routing headers that were not derived by reversing the Routing header of the 
 *   received packet (for example, a Routing header supplied by local configuration).
 * - Response packets that carry Routing headers that were derived by reversing the Routing header of the 
 *   received packet (for example, a Routing header supplied by local configuration).
 * 
 * @section     IANAConsiderations      9. IANA Considerations
 * 
 * [Internet Protocol, Version 6 (IPv6) Specification](https://datatracker.ietf.org/doc/html/rfc2460) is
 * referenced in a number of IANA registries. These include:
 * 
 * - [Internet Protocol Version 6 (IPv6) Parameters](https://www.iana.org/assignments/ipv6-parameters/ipv6-parameters.xhtml)
 * - [Assigned Internet Protocol Numbers](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml)
 * - [ONC RPC Network Identifiers (netids)](https://www.iana.org/assignments/rpc-netids/rpc-netids.xhtml)
 * - [Network Layer Protocol Identifiers (NLPIDs) of Interest](https://www.iana.org/assignments/nlpids/nlpids.xhtml)
 * - [Protocol Registries](https://www.iana.org/protocols)
 * 
 * The IANA has updated these references to point to this document.
 * 
 * @section     SecurityConsidersions   10. Security Considerations
 * 
 * IPv6, from the viewpoint of the basic format and transmission of packets, has security properties that are
 * similar to IPv4. These security issues include:
 * 
 * - Eavesdropping, where on-path elements can observe the whole packet (including both contents and metadata)
 *   of each IPv6 datagram.
 * - Replay, where the attacker records a sequence of packets off of the wire and plays them back to the party
 *   that originally received theme.
 * - Packet insertion, where the attacker forgets a packet with some chosen set of properties and injects it into
 *   the network.
 * - Packet deletion, where the attacker removes a packet from the wire.
 * - Packet modification, where the attacker removes a packet from the wire, modifies it, and reinjects it into
 *   the network.
 * - Man-in-the-middle (MITM) attacks, where the attacker subverts the communication stream in order to pose as
 *   the sender to receiver and the receiver to the sender.
 * - Denial-of-service (Dos) attacks, where the attacker sends large amounts of legitimate traffic to a destination
 *   to overwhelm it.
 * 
 * IPv6 packets can protected from eavesdropping, replay, packet insertion, packet modification, and MITM attacks
 * by use of the [Security Architecture for the Internet Protocol](https://datatracker.ietf.org/doc/html/rfc4301).
 * In addition, upper-layer protocols such as Transport Layer Security (TLS) or Secure Shell (SSH) can be used
 * to protect the application layer traffic running on top of IPv6.
 * 
 * There is not any mechanism to protect against DoS attacks. Defending against these type of attacks is outside
 * the scope of this specification.
 * 
 * IPv6 addresses are significantly larger than IPv4 addresses making it much harder to scan the address space
 * across the Internet and even on a single network link (e.g., Local Area Network). See [Network Reconnaissance in IPv6 Networks](https://datatracker.ietf.org/doc/html/rfc7707)
 * for more information.
 * 
 * IPv6 addresses of nodes are expected to be more visible on the Internet as compared with IPv4 since the use of
 * address translation technology is reduced. This creates some additional privacy issues such as making it
 * easier to distinguish endpoints. See [Security and Privacy Considerations for IPv6 Address Generation Mechanisms](https://datatracker.ietf.org/doc/html/rfc7721) for more information.
 * 
 * The design of IPv6 extension header architecture, while adding a lot of flexibility, also creates new 
 * security challenges. As noted below, but it's clear that for any new extension header have been resolved,
 * but it's clear that for any new extension header designed in the future, the security implications need to
 * be examined thoroughly, and this needs to include how the new extension header works with existing extension
 * headers. See [Transmission and Processing of IPv6 Extension Headers](https://datatracker.ietf.org/doc/html/rfc7045)
 * for more information.
 * 
 * This version of the IPv6 specification resolves a number of security issues that were found with the previous
 * version [Internet Protocol, Version 6 (IPv6) Specification](https://datatracker.ietf.org/doc/html/rfc2460) of
 * the IPv6 specification. These include:
 * 
 * - Revised the text to handle the case of fragments that are whole datagrams (i.e., both the Fragment Offset
 *   field and the M flag are zero). If received, they should be processed as a reassembled packet. Any other
 *   fragments that match should be processed independently. The Fragment creation process was modified to not
 *   create whole datagram fragments (Fragment Offset field and the M flag are zero). See [Processing of IPv6 "Atomic" Fragments](https://datatracker.ietf.org/doc/html/rfc6946)
 *   and [Generation of IPv6 Atomic Fragments Considered Harmful](https://datatracker.ietf.org/doc/html/rfc8021)
 *   for more information.
 * - Removed the paragraph in Section 5 that required including a Fragment header to outgoing packets if an ICMP
 *   Packet Too Big message reporting a Next-Hop MTU is less than 1280. See [Processing of IPv6 "Atomic" Fragments](https://datatracker.ietf.org/doc/html/rfc6946)
 *   for more information.
 * - Changed the text to require that IPv6 nodes must not create overlapping fragments. Also, when reassembling an
 *   IPv6 datagram, if one or more of its constituent fragments is determined to be an overlapping fragment,
 *   the entire datagram (and any constituent fragments) must be silently discarded. Includes clarification
 *   that no ICMP error message should be sent it overlapping fragments are received. See [Handling of Overlapping IPv6 Fragments](https://datatracker.ietf.org/doc/html/rfc5722)
 *   for more information.
 * - Revised the text to require that all headers through the first upper-layer header are in the first 
 *   fragment. See [Implications of Oversized IPv6 Header Chains](https://datatracker.ietf.org/doc/html/rfc7112)
 *   for more information.
 * - Incorporated the updates from [Deprecation of Type 0 Routing Headers in IPv6](https://datatracker.ietf.org/doc/html/rfc5095)
 *   and [IANA Allocation Guidelines for the IPv6 Routing Header](https://datatracker.ietf.org/doc/html/rfc5871)
 *   to remove the description of the Routing Header type 0 (RH0), that the allocations guideines for Routing
 *   headers are specified in [IANA Allocation Guidelines for the IPv6 Routing Header](https://datatracker.ietf.org/doc/html/rfc5871),
 *   and removed RH0 from the list of required extension headers.
 * 
 * Security issues relating to other parts of IPv6 including addressing, ICMPv6, Path MTU Discovery, etc., are
 * discussed in the appropriate specification.
 * 
 * @todo:       Arragne Remain Specification
 * 
 * @see         [Internet Protocol, Version 6 Specification](https://datatracker.ietf.org/doc/html/rfc8200)
 */