/**
 * @file        snorlax/virtual/private/network/agent/application.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 24, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_APPLICATION__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_APPLICATION__H__


#include <snorlax/virtual/private/network/application.h>
#include <snorlax/socket/client/event/subscription.h>
#include <snorlax/event/engine.h>

#include <snorlax/network/netlink.h>
#include <snorlax/network/tun.h>
#include <snorlax/descriptor/event/subscription.h>
#include <snorlax/socket/event/subscription.h>

#include <snorlax/protocol/internet.h>
#include <snorlax/protocol/internet/version4.h>
#include <snorlax/protocol/internet/version6.h>
#include <snorlax/protocol/internet/version4/control/message.h>
#include <snorlax/protocol/internet/version6/control/message.h>
#include <snorlax/protocol/internet/user/datagram.h>
#include <snorlax/protocol/internet/transmission/control.h>

struct virtual_private_network_application_agent;
struct virtual_private_network_application_agent_func;

typedef struct virtual_private_network_application_agent            virtual_private_network_application_agent_t;
typedef struct virtual_private_network_application_agent_func       virtual_private_network_application_agent_func_t;

struct virtual_private_network_application_agent {
    ___reference virtual_private_network_application_agent_func_t *     func;
    sync_t *                                                            sync;
    ___reference virtual_private_network_application_config_t *         config;

    event_engine_t *                                                    engine;

    descriptor_event_subscription_t *                                   tun;
    socket_event_subscription_t *                                       netlink;

    internet_protocol_module_t *                                        InternetProtocol;
    transmission_control_protocol_module_t *                            TransmissionControlProtocol;
    user_datagram_protocol_module_t *                                   UserDatagramProtocol;
    internet_protocol_version6_extension_hopbyhop_module_t *            InternetProtocolVersion6ExtensionHopbyhop;
    internet_protocol_version6_extension_routing_module_t *             InternetProtocolVersion6ExtensionRouting;
    internet_protocol_version6_extension_fragment_module_t *            InternetProtocolVersion6ExtensionFragment;
    internet_protocol_version6_extension_destination_module_t *         InternetProtocolVersion6ExtensionDestination;
    internet_control_message_protocol_version4_module_t *               InternetControlMessageProtocolVersion4;
    internet_control_message_protocol_version6_module_t *               InternetControlMessageProtocolVersion6;

    protocol_module_map_t *                                             TransportLayer;

    char                                                                ifname[16];

    uint32_t                                                            InternetProtocolAddressVersion4;
    uint8_t                                                             InternetProtocolAddressVersion6[16];

};

struct virtual_private_network_application_agent_func {
    virtual_private_network_application_agent_t * (*rem)(virtual_private_network_application_agent_t *);
    int32_t (*on)(virtual_private_network_application_agent_t *);
    int32_t (*off)(virtual_private_network_application_agent_t *);
    int32_t (*run)(virtual_private_network_application_agent_t *);
};

#define virtual_private_network_application_agent_rem(application)      ((application)->func->rem(application))
#define virtual_private_network_application_agent_on(application)       ((application)->func->on(application))
#define virtual_private_network_application_agent_off(application)      ((application)->func->off(application))
#define virtual_private_network_application_agent_run(application)      ((application)->func->run(application))

extern virtual_private_network_application_agent_t * virtual_private_network_application_agent_get(void);
extern network_tun_t * virtual_private_network_application_agent_tun_get(virtual_private_network_application_agent_t * application);

extern void virtual_private_network_application_agent_interface_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response);
extern void virtual_private_network_application_agent_network_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response);

struct virtual_private_network_application_config {
    uint16_t port;
    char ifname[32];
};

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_AGENT_APPLICATION__H__
