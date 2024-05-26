cmake_minimum_required(VERSION 3.22)
project(SnorlaxTCP C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSNORLAX_DEBUG")

include_directories(src)

set(SNORLAX_SOURCE                                      src/snorlax.c)
set(SNORLAX_HEADER                                      src/snorlax.h)

set(SNORLAX_PCAP_SOURCE                                 src/snorlax/pcap.c)
set(SNORLAX_PCAP_HEADER                                 src/snorlax/pcap.h)

set(SNORLAX_PROTOCOL_SOURCE                             src/snorlax/protocol/number.c)
set(SNORLAX_PROTOCOL_HEADER                             src/snorlax/protocol/number.h)

set(SNORLAX_PROTOCOL_ETHERNET_SOURCE                    src/snorlax/protocol/ethernet.c)
set(SNORLAX_PROTOCOL_ETHERNET_HEADER                    src/snorlax/protocol/ethernet.h)

set(SNORLAX_PROTOCOL_INTERNET_SOURCE                    src/snorlax/protocol/internet.c
                                                        src/snorlax/protocol/internet/version4.c
                                                        src/snorlax/protocol/internet/version6.c)
set(SNORLAX_PROTOCOL_INTERNET_HEADER                    src/snorlax/protocol/internet.h
                                                        src/snorlax/protocol/internet/version4.h
                                                        src/snorlax/protocol/internet/version6.h)

set(SNORLAX_PROTOCOL_USER_DATAGRAM_SOURCE               src/snorlax/protocol/user-datagram.c)
set(SNORLAX_PROTOCOL_USER_DATAGRAM_HEADER               src/snorlax/protocol/user-datagram.h)

set(SNORLAX_PROTOCOL_INTERNET_CONTROL_MESSAGE_SOURCE    src/snorlax/protocol/internet/control-message.c)
set(SNORLAX_PROTOCOL_INTERNET_CONTROL_MESSAGE_HEADER    src/snorlax/protocol/internet/control-message.h)

set(SNORLAX_PROTOCOL_ETHERNET_ADDRESS_RESOLUTION_SOURCE src/snorlax/protocol/ethernet/address-resolution-protocol.c)
set(SNORLAX_PROTOCOL_ETHERNET_ADDRESS_RESOLUTION_HEADER src/snorlax/protocol/ethernet/address-resolution-protocol.h)

set(SNORLAX_PROTOCOL_APPLICATION_SOURCE                 src/snorlax/protocol/application.c)
set(SNORLAX_PROTOCOL_APPLICATION_HEADER                 src/snorlax/protocol/application.h)

add_library(snorlax-protocol-stack ${SNORLAX_SOURCE}
                                   ${SNORLAX_HEADER}
                                   ${SNORLAX_PCAP_SOURCE}
                                   ${SNORLAX_PCAP_HEADER}
                                   ${SNORLAX_PROTOCOL_SOURCE}
                                   ${SNORLAX_PROTOCOL_HEADER}
                                   ${SNORLAX_PROTOCOL_ETHERNET_SOURCE}
                                   ${SNORLAX_PROTOCOL_ETHERNET_HEADER}
                                   ${SNORLAX_PROTOCOL_ETHERNET_ADDRESS_RESOLUTION_SOURCE}
                                   ${SNORLAX_PROTOCOL_ETHERNET_ADDRESS_RESOLUTION_HEADER}
                                   ${SNORLAX_PROTOCOL_INTERNET_SOURCE}
                                   ${SNORLAX_PROTOCOL_INTERNET_HEADER}
                                   ${SNORLAX_PROTOCOL_INTERNET_CONTROL_MESSAGE_SOURCE}
                                   ${SNORLAX_PROTOCOL_INTERNET_CONTROL_MESSAGE_HEADER}
                                   ${SNORLAX_PROTOCOL_USER_DATAGRAM_SOURCE}
                                   ${SNORLAX_PROTOCOL_USER_DATAGRAM_HEADER}
                                   ${SNORLAX_PROTOCOL_APPLICATION_SOURCE}
                                   ${SNORLAX_PROTOCOL_APPLICATION_HEADER})

target_compile_options(snorlax-protocol-stack PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

add_executable(snorlax-pcap src/snorlax/pcap/main.c)
target_link_libraries(snorlax-pcap snorlax-protocol-stack -lpcap)
