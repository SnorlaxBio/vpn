cmake_minimum_required(VERSION 3.22)
project(SnorlaxTCP C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSNORLAX_DEBUG")

include_directories(src)

set(SNORLAX_SOURCE                      src/snorlax.c)
set(SNORLAX_HEADER                      src/snorlax.h)

set(SNORLAX_PCAP_SOURCE                 src/snorlax/pcap.c)
set(SNORLAX_PCAP_HEADER                 src/snorlax/pcap.h)

set(SNORLAX_PROTOCOL_ETHERNET_SOURCE    src/snorlax/protocol/ethernet.c)
set(SNORLAX_PROTOCOL_ETHERNET_HEADER    src/snorlax/protocol/ethernet.h)

add_library(snorlax-protocol-stack ${SNORLAX_SOURCE}
                                   ${SNORLAX_HEADER}
                                   ${SNORLAX_PCAP_SOURCE}
                                   ${SNORLAX_PCAP_HEADER}
                                   ${SNORLAX_PROTOCOL_ETHERNET_SOURCE}
                                   ${SNORLAX_PROTOCOL_ETHERNET_HEADER})

target_compile_options(snorlax-protocol-stack PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

add_executable(snorlax-pcap src/snorlax/pcap/main.c)
target_link_libraries(snorlax-pcap snorlax-protocol-stack -lpcap)
