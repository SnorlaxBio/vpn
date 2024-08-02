cmake_minimum_required(VERSION 3.22)
project(SnorlaxVPN C)
include(ExternalProject)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DSNORLAX_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSNORLAX_DEBUG")

ExternalProject_Add(snorlax-std
    PREFIX          "${PROJECT_SOURCE_DIR}/lib/snorlax/std"
    TMP_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/std/tmp"
    STAMP_DIR       "${PROJECT_SOURCE_DIR}/lib/snorlax/std/stamp"
    DOWNLOAD_DIR    "${PROJECT_SOURCE_DIR}/lib/snorlax/std/src"
    SOURCE_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/std/src"
    BINARY_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/std/build"
    INSTALL_DIR     "${PROJECT_SOURCE_DIR}/lib/snorlax/std/install"
    LOG_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/std/log"
    GIT_REPOSITORY  git@github.com:SnorlaxBio/std.git
    GIT_TAG         main
    GIT_REMOTE_NAME origin
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug
                                       -S "${PROJECT_SOURCE_DIR}/lib/snorlax/std/src"
                                       -B "${PROJECT_SOURCE_DIR}/lib/snorlax/std/build"
                                       --install-prefix ${PROJECT_SOURCE_DIR}
    BUILD_COMMAND     ${CMAKE_COMMAND} --build "${PROJECT_SOURCE_DIR}/lib/snorlax/std/build"
                                       --target all)

# ExternalProject_Add(snorlax-protocol
#     PREFIX          "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol"
#     TMP_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/tmp"
#     STAMP_DIR       "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/stamp"
#     DOWNLOAD_DIR    "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/src"
#     SOURCE_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/src"
#     BINARY_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/build"
#     INSTALL_DIR     "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/install"
#     LOG_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/log"
#     GIT_REPOSITORY  git@github.com:SnorlaxBio/protocol.git
#     GIT_TAG         main
#     GIT_REMOTE_NAME origin
#     CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug
#                                        -S "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/src"
#                                        -B "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/build"
#                                        --install-prefix ${PROJECT_SOURCE_DIR}
#     BUILD_COMMAND     ${CMAKE_COMMAND} --build "${PROJECT_SOURCE_DIR}/lib/snorlax/protocol/build"
#                                        --target all)

ExternalProject_Add(snorlax-eva
    PREFIX          "${PROJECT_SOURCE_DIR}/lib/snorlax/eva"
    TMP_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/tmp"
    STAMP_DIR       "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/stamp"
    DOWNLOAD_DIR    "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/src"
    SOURCE_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/src"
    BINARY_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/build"
    INSTALL_DIR     "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/install"
    LOG_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/log"
    GIT_REPOSITORY  git@github.com:SnorlaxBio/eva.git
    GIT_TAG         main
    GIT_REMOTE_NAME origin
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug
                                        -S "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/src"
                                        -B "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/build"
                                        --install-prefix ${PROJECT_SOURCE_DIR}
    BUILD_COMMAND     ${CMAKE_COMMAND} --build "${PROJECT_SOURCE_DIR}/lib/snorlax/eva/build"
                                        --target all)

ExternalProject_Add(snorlax-net
    PREFIX          "${PROJECT_SOURCE_DIR}/lib/snorlax/net"
    TMP_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/net/tmp"
    STAMP_DIR       "${PROJECT_SOURCE_DIR}/lib/snorlax/net/stamp"
    DOWNLOAD_DIR    "${PROJECT_SOURCE_DIR}/lib/snorlax/net/src"
    SOURCE_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/net/src"
    BINARY_DIR      "${PROJECT_SOURCE_DIR}/lib/snorlax/net/build"
    INSTALL_DIR     "${PROJECT_SOURCE_DIR}/lib/snorlax/net/install"
    LOG_DIR         "${PROJECT_SOURCE_DIR}/lib/snorlax/net/log"
    GIT_REPOSITORY  git@github.com:SnorlaxBio/net.git
    GIT_TAG         main
    GIT_REMOTE_NAME origin
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug
                                        -S "${PROJECT_SOURCE_DIR}/lib/snorlax/net/src"
                                        -B "${PROJECT_SOURCE_DIR}/lib/snorlax/net/build"
                                        --install-prefix ${PROJECT_SOURCE_DIR}
    BUILD_COMMAND     ${CMAKE_COMMAND} --build "${PROJECT_SOURCE_DIR}/lib/snorlax/net/build"
                                        --target all)

include_directories(src include)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/build)

set(SNORLAX_VPN_CLIENT_SOURCE   src/snorlax/vpn/client/app.c
                                src/snorlax/vpn/client/app/config.c
                                src/snorlax/vpn/client/app/tun.c
                                src/snorlax/vpn/client/app/netlink.c
                                src/snorlax/vpn/client/event/subscription.c)
set(SNORLAX_VPN_ClIENT_HEADER   src/snorlax/vpn/client/app.h
                                src/snorlax/vpn/client/app/config.h
                                src/snorlax/vpn/client/app/tun.h
                                src/snorlax/vpn/client/app/netlink.h
                                src/snorlax/vpn/client/event/subscription.h)

set(SNORLAX_VPN_PROTOCOL_SOURCE src/snorlax/protocol/module/map.c
                                src/snorlax/protocol/internet/version6.c
                                src/snorlax/protocol/internet/version4/context.c
                                src/snorlax/protocol/internet/version4/module.c
                                src/snorlax/protocol/internet/version6/context.c
                                src/snorlax/protocol/internet/version6/module.c
                                src/snorlax/protocol/internet/version6/extension/destination/context.c
                                src/snorlax/protocol/internet/version6/extension/destination/module.c
                                src/snorlax/protocol/internet/version6/extension/hopbyhop/context.c
                                src/snorlax/protocol/internet/version6/extension/hopbyhop/module.c
                                src/snorlax/protocol/internet/version6/extension/routing/context.c
                                src/snorlax/protocol/internet/version6/extension/routing/module.c
                                src/snorlax/protocol/internet/version6/extension/fragment/context.c
                                src/snorlax/protocol/internet/version6/extension/fragment/module.c)

set(SNORLAX_VPN_PROTOCOL_HEADER src/snorlax/protocol/packet.h
                                src/snorlax/protocol/module.h
                                src/snorlax/protocol/context.h
                                src/snorlax/protocol/module/map.h
                                src/snorlax/protocol/internet.h
                                src/snorlax/protocol/internet/version4.h
                                src/snorlax/protocol/internet/version6.h)

add_executable(snorlax-vpn-client   ${SNORLAX_VPN_CLIENT_SOURCE}
                                    ${SNORLAX_VPN_ClIENT_HEADER}
                                    ${SNORLAX_VPN_PROTOCOL_SOURCE}
                                    ${SNORLAX_VPN_PROTOCOL_HEADER})
target_compile_options(snorlax-vpn-client PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_link_libraries(snorlax-vpn-client libsnorlax-net.a libsnorlax-eva.a libsnorlax-std.a)

set(SNORLAX_VPN_SERVER_SOURCE   src/snorlax/vpn/server/app.c
                                src/snorlax/vpn/server.c
                                src/snorlax/vpn/session.c)
set(SNORLAX_VPN_SERVER_HEADER   src/snorlax/vpn/server/app.h
                                src/snorlax/vpn/server.h
                                src/snorlax/vpn/session.h)

add_executable(snorlax-vpn-server   ${SNORLAX_VPN_SERVER_SOURCE}
                                    ${SNORLAX_VPN_SERVER_HEADER})
target_compile_options(snorlax-vpn-server PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_link_libraries(snorlax-vpn-server libsnorlax-net.a libsnorlax-eva.a libsnorlax-std.a)