### 20240825 | [PROTOCOL] MODULE ON/OFF 함수를 만들자.


-----------------------------------------------------------------------------------------

### 20240706 | NamedPipe, TCP, UDP, Unix Domain
### 20240815 | Router 관련한 패킷을 어떻게 처리해야 하는가? | OK

이 녀석은 아직 라우터가 아니다. 그렇기 때문에, 현재는 구현 필요성이 아니다.

### 20240815 | SERVER & INLINE SERVER 만들 것 ... INLINE SERVER 란 ? | OK

  - Server, Client
  - Single: Packet 전송이 클라이언트에서 이루어진다.

### 20240816 | TCP TEST 방법을 찾자.

- snorlax network tcp/ip socket ... test
- simple connect 

### 20240823 | TCP SEQNUMBER ... 

- SEND / RECV

https://www.kernel.org/doc/Documentation/networking/segmentation-offloads.txt

TCP segmentation allows a device to segment a single frame into multiple frames with a data payload size specified in skb_shinfo()->gso_size.
When TCP segmentation requested the bit for either SKB_GSO_TCPV4 or SKB_GSO_TCPV6 should be set in skb_shinfo()->gso_type and skb_shinfo()->gso_size should be set to a non-zero value.

TCP segmentation is dependent on support for the use of partial checksum offload.  For this reason TSO is normally disabled if the Tx checksum offload for a given device is disabled.

In order to support TCP segmentation offload it is necessary to populate the network and transport header offsets of the skbuff so that the device
drivers will be able determine the offsets of the IP or IPv6 header and the TCP header.  In addition as CHECKSUM_PARTIAL is required csum_start should also point to the TCP header of the packet.

For IPv4 segmentation we support one of two types in terms of the IP ID. The default behavior is to increment the IP ID with every segment.  If the GSO type SKB_GSO_TCP_FIXEDID is specified then we will not increment the IP ID and all segments will use the same IP ID.  If a device has NETIF_F_TSO_MANGLEID set then the IP ID can be ignored when performing TSO and we will either increment the IP ID for all frames, or leave it at a static value based on driver preference.

### 20240824 | TUN 의 INPUT 버퍼를 LIST 형으로 변경하자.

### 20240824 | 버퍼에 콜백을 만들어서 반영하자. - 이것은 고민을 하자.
