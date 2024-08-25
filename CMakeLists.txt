cmake_minimum_required(VERSION 3.22)
project(SnorlaxVPN C)
include(ExternalProject)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DSNORLAX_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSNORLAX_DEBUG")

# TODO: ### 20240825 | 여러 포함 라이브러리들의 관계를 잘 정리하고 전체적으로 한 번만 빌드하도록 한다.
# TODO: ### 20240825 | External Project 에 대해서 정리하자.
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
# TODO: ### 20240825 | MESSAGE PROJECT 를 생성 후에 다시 포함시킨다.
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

set(SNORLAX_VPN_PROTOCOL_SOURCE src/snorlax/vpn/protocol.c
                                src/snorlax/vpn/protocol/module.c
                                src/snorlax/vpn/protocol/context.c)

set(SNORLAX_VPN_PROTOCOL_HEADER src/snorlax/vpn/protocol.h)

# set(SNORLAX_VPN_CLIENT_SOURCE   src/snorlax/vpn/agent.c
#                                 src/snorlax/vpn/client.c
#                                 src/snorlax/vpn/client/app.c
#                                 src/snorlax/vpn/client/app/config.c
#                                 src/snorlax/vpn/client/app/tun.c
#                                 src/snorlax/vpn/client/app/netlink.c
#                                 src/snorlax/vpn/client/event/subscription.c
#                                 src/snorlax/vpn/client/event/subscription/handler.c)
# set(SNORLAX_VPN_ClIENT_HEADER   src/snorlax/vpn/agent.h
#                                 src/snorlax/vpn/client.h
#                                 src/snorlax/vpn/client/app.h
#                                 src/snorlax/vpn/client/app/config.h
#                                 src/snorlax/vpn/client/app/tun.h
#                                 src/snorlax/vpn/client/app/netlink.h
#                                 src/snorlax/vpn/client/event/subscription.h
#                                 src/snorlax/vpn/client/event/subscription/handler.h)

# set(SNORLAX_VPN_SINGLE_SOURCE   src/snorlax/vpn/agent.c
#                                 src/snorlax/vpn/client.c
#                                 src/snorlax/vpn/single/app.c
#                                 src/snorlax/vpn/single/app/config.c
#                                 src/snorlax/vpn/single/app/tun.c
#                                 src/snorlax/vpn/single/app/netlink.c
#                                 src/snorlax/vpn/single/protocol/internet.c
#                                 src/snorlax/vpn/single/protocol/internet/version4.c
#                                 src/snorlax/vpn/single/protocol/internet/version6.c
#                                 src/snorlax/vpn/single/protocol/transmission/control.c
#                                 src/snorlax/vpn/single/protocol/transmission/control/handler.c
#                                 src/snorlax/vpn/single/protocol/transmission/control/block/agent.c
#                                 src/snorlax/vpn/single/protocol/transmission/control/block/agent/meta.c)

# set(SNORLAX_VPN_SINGLE_HEADER   src/snorlax/vpn/agent.h
#                                 src/snorlax/vpn/client.h
#                                 src/snorlax/vpn/single/app.h
#                                 src/snorlax/vpn/single/app/config.h
#                                 src/snorlax/vpn/single/app/tun.h
#                                 src/snorlax/vpn/single/app/netlink.h
#                                 src/snorlax/vpn/single/protocol/internet.h
#                                 src/snorlax/vpn/single/protocol/internet/version4.h
#                                 src/snorlax/vpn/single/protocol/internet/version6.h
#                                 src/snorlax/vpn/single/protocol/transmission/control.h)

# set(SNORLAX_VPN_SERVER_SOURCE   src/snorlax/vpn/server/app.c
#                                 src/snorlax/vpn/server.c
#                                 src/snorlax/vpn/session.c)
# set(SNORLAX_VPN_SERVER_HEADER   src/snorlax/vpn/server/app.h
#                                 src/snorlax/vpn/server.h
#                                 src/snorlax/vpn/session.h)

set(SNORLAX_PROTOCOL_SOURCE     src/snorlax/protocol.c
                                src/snorlax/protocol/module.c
                                src/snorlax/protocol/context.c
                                src/snorlax/protocol/path.c
                                src/snorlax/protocol/module/map.c
                                src/snorlax/protocol/context/array.c
                                src/snorlax/protocol/internet.c
                                src/snorlax/protocol/internet/module.c
                                src/snorlax/protocol/internet/context.c
                                src/snorlax/protocol/internet/version4.c
                                src/snorlax/protocol/internet/version4/context.c
                                src/snorlax/protocol/internet/version4/module.c
                                src/snorlax/protocol/internet/version4/control/message.c
                                src/snorlax/protocol/internet/version4/control/message/module.c
                                src/snorlax/protocol/internet/version4/control/message/context.c
                                src/snorlax/protocol/internet/version4/control/message/context/destination/unreachable.c
                                src/snorlax/protocol/internet/version4/control/message/context/parameter/problem.c
                                src/snorlax/protocol/internet/version4/control/message/context/source/quench.c
                                src/snorlax/protocol/internet/version4/control/message/context/time/exceeded.c
                                src/snorlax/protocol/internet/version4/control/message/context/echo.c
                                src/snorlax/protocol/internet/version4/control/message/context/information.c
                                src/snorlax/protocol/internet/version4/control/message/context/redirect.c
                                src/snorlax/protocol/internet/version4/control/message/context/timestamp.c
                                src/snorlax/protocol/internet/version6.c
                                src/snorlax/protocol/internet/version6/context.c
                                src/snorlax/protocol/internet/version6/module.c
                                src/snorlax/protocol/internet/version6/module/host.c
                                src/snorlax/protocol/internet/version6/module/router.c
                                src/snorlax/protocol/internet/version6/control/message.c
                                src/snorlax/protocol/internet/version6/control/message/module.c
                                src/snorlax/protocol/internet/version6/control/message/context.c
                                src/snorlax/protocol/internet/version6/control/message/context/echo.c
                                src/snorlax/protocol/internet/version6/control/message/context/redirect.c
                                src/snorlax/protocol/internet/version6/control/message/context/destination/unreachable.c
                                src/snorlax/protocol/internet/version6/control/message/context/packet/toobig.c
                                src/snorlax/protocol/internet/version6/control/message/context/parameter/problem.c
                                src/snorlax/protocol/internet/version6/control/message/context/router/solicitation.c
                                src/snorlax/protocol/internet/version6/control/message/context/router/advertisement.c
                                src/snorlax/protocol/internet/version6/control/message/context/neighbor/solicitation.c
                                src/snorlax/protocol/internet/version6/control/message/context/neighbor/advertisement.c
                                src/snorlax/protocol/internet/version6/control/message/context/time/exceeded.c
                                src/snorlax/protocol/internet/version6/extension/module.c
                                src/snorlax/protocol/internet/version6/extension/destination/context.c
                                src/snorlax/protocol/internet/version6/extension/destination/module.c
                                src/snorlax/protocol/internet/version6/extension/hopbyhop/context.c
                                src/snorlax/protocol/internet/version6/extension/hopbyhop/module.c
                                src/snorlax/protocol/internet/version6/extension/routing/context.c
                                src/snorlax/protocol/internet/version6/extension/routing/module.c
                                src/snorlax/protocol/internet/version6/extension/fragment/context.c
                                src/snorlax/protocol/internet/version6/extension/fragment/module.c
                                src/snorlax/protocol/internet/user/datagram.c
                                src/snorlax/protocol/internet/user/datagram/module.c
                                src/snorlax/protocol/internet/user/datagram/context.c
                                src/snorlax/protocol/internet/transmission/control.c
                                src/snorlax/protocol/internet/transmission/control/packet.c
                                src/snorlax/protocol/internet/transmission/control/module.c
                                src/snorlax/protocol/internet/transmission/control/context.c
                                src/snorlax/protocol/internet/transmission/control/block.c
                                src/snorlax/protocol/internet/transmission/control/block/client.c
                                src/snorlax/protocol/internet/transmission/control/block/client/handler.c
                                src/snorlax/protocol/internet/transmission/control/block/on.c
                                src/snorlax/protocol/internet/transmission/control/block/buffer/in.c
                                src/snorlax/protocol/internet/transmission/control/block/buffer/out.c
                                src/snorlax/protocol/internet/transmission/control/block/buffer/in/node.c
                                src/snorlax/protocol/internet/transmission/control/block/buffer/out/node.c
                                src/snorlax/protocol/internet/transmission/control/block/in.c
                                src/snorlax/protocol/internet/transmission/control/block/complete/in.c
                                src/snorlax/protocol/internet/transmission/control/block/state/in.c
                                src/snorlax/protocol/internet/transmission/control/block/state/complete/in.c)

set(SNORLAX_PROTOCOL_HEADER     src/snorlax/protocol.h
                                src/snorlax/protocol/internet.h
                                src/snorlax/protocol/internet/version4.h
                                src/snorlax/protocol/internet/version4/control/message.h
                                src/snorlax/protocol/internet/version6.h
                                src/snorlax/protocol/internet/version6/control/message.h
                                src/snorlax/protocol/internet/user/datagram.h
                                src/snorlax/protocol/internet/transmission/control.h)

set(SNORLAX_VPN_SOURCE          src/snorlax/virtual/private/network/socket.c
                                src/snorlax/virtual/private/network/socket/session.c
                                src/snorlax/virtual/private/network/socket/server.c
                                src/snorlax/virtual/private/network/socket/client.c)

set(SNORLAX_VPN_HEADER          src/snorlax/virtual/private/network/socket.h
                                src/snorlax/virtual/private/network/socket/session.h
                                src/snorlax/virtual/private/network/socket/server.h
                                src/snorlax/virtual/private/network/socket/client.h
                                src/snorlax/virtual/private/network/application.h)

set(SNORLAX_VPN_AGENT_SOURCE    src/snorlax/virtual/private/network/agent/application.c
                                src/snorlax/virtual/private/network/agent/netlink/event/subscription/handler.c
                                src/snorlax/virtual/private/network/agent/tun/event/subscription/handler.c
                                src/snorlax/virtual/private/network/agent/protocol/internet.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version4.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version4/control/message.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/control/message.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/destination.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/fragment.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/hopbyhop.c
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/routing.c
                                src/snorlax/virtual/private/network/agent/protocol/transmission/control.c
                                src/snorlax/virtual/private/network/agent/protocol/transmission/control/block.c
                                src/snorlax/virtual/private/network/agent/protocol/user/datagram.c
                                src/snorlax/virtual/private/network/agent/transmission/control/block/client.c)

set(SNORLAX_VPN_AGENT_HEADER    src/snorlax/virtual/private/network/agent/application.h
                                src/snorlax/virtual/private/network/agent/netlink/event/subscription/handler.h
                                src/snorlax/virtual/private/network/agent/tun/event/subscription/handler.h
                                src/snorlax/virtual/private/network/agent/protocol/internet.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version4.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version4/control/message.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/control/message.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/destination.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/fragment.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/hopbyhop.h
                                src/snorlax/virtual/private/network/agent/protocol/internet/version6/extension/routing.h
                                src/snorlax/virtual/private/network/agent/protocol/transmission/control.h
                                src/snorlax/virtual/private/network/agent/protocol/transmission/control/block.h
                                src/snorlax/virtual/private/network/agent/protocol/user/datagram.h
                                src/snorlax/virtual/private/network/agent/transmission/control/block/client.h)

add_library(snorlax-protocol                ${SNORLAX_PROTOCOL_SOURCE} ${SNORLAX_PROTOCOL_HEADER})
target_compile_options(snorlax-protocol     PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

add_library(snorlax-vpn                     ${SNORLAX_VPN_SOURCE} ${SNORLAX_VPN_HEADER})
target_compile_options(snorlax-vpn          PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

add_executable(snorlax-vpn-agent            ${SNORLAX_VPN_AGENT_SOURCE} ${SNORLAX_VPN_AGENT_HEADER})
target_compile_options(snorlax-vpn-agent    PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_link_libraries(snorlax-vpn-agent     snorlax-vpn snorlax-protocol libsnorlax-net.a libsnorlax-eva.a libsnorlax-std.a)

# add_library(snorlax-vpn-protocol    ${SNORLAX_VPN_PROTOCOL_SOURCE}
#                                     ${SNORLAX_VPN_PROTOCOL_HEADER})
# target_compile_options(snorlax-vpn-protocol PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")



# add_executable(snorlax-vpn-client   ${SNORLAX_VPN_CLIENT_SOURCE}
#                                     ${SNORLAX_VPN_ClIENT_HEADER})
# target_compile_options(snorlax-vpn-client PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
# target_link_libraries(snorlax-vpn-client snorlax-vpn-protocol snorlax-protocol libsnorlax-net.a libsnorlax-eva.a libsnorlax-std.a)

# add_executable(snorlax-vpn-single   ${SNORLAX_VPN_SINGLE_SOURCE}
#                                     ${SNORLAX_VPN_SINGLE_HEADER})
# target_compile_options(snorlax-vpn-single PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
# target_link_libraries(snorlax-vpn-single snorlax-vpn-protocol snorlax-protocol libsnorlax-net.a libsnorlax-eva.a libsnorlax-std.a)

# add_executable(snorlax-vpn-server   ${SNORLAX_VPN_SERVER_SOURCE}
#                                     ${SNORLAX_VPN_SERVER_HEADER})
# target_compile_options(snorlax-vpn-server PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
# target_link_libraries(snorlax-vpn-server snorlax-vpn-protocol snorlax-protocol libsnorlax-net.a libsnorlax-eva.a libsnorlax-std.a)