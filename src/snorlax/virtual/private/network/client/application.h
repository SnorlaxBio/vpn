/**
 * @file        snorlax/virtual/private/network/client/application.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       Aug 24, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_CLIENT_APPLICATION__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_CLIENT_APPLICATION__H__

#include <snorlax/virtual/private/network/application.h>
#include <snorlax/socket/client/event/subscription.h>
#include <snorlax/event/engine.h>

#include <snorlax/network/netlink.h>

#include <snorlax/protocol/internet.h>
#include <snorlax/protocol/internet/version4.h>
#include <snorlax/protocol/internet/version6.h>
#include <snorlax/protocol/internet/version4/control/message.h>
#include <snorlax/protocol/internet/version6/control/message.h>
#include <snorlax/protocol/internet/user/datagram.h>
#include <snorlax/protocol/internet/transmission/control.h>

struct virtual_private_network_application_client;
struct virtual_private_network_application_client_func;

typedef struct virtual_private_network_application_client           virtual_private_network_application_client_t;
typedef struct virtual_private_network_application_client_func      virtual_private_network_application_client_func_t;


struct virtual_private_network_application_client {
    virtual_private_network_application_client_func_t * func;
    sync_t * sync;
    virtual_private_network_application_config_t * config;

    event_engine_t * engine;

    descriptor_event_subscription_t * tun;
    socket_event_subscription_t * netlink;

    struct {
        internet_protocol_module_t * internet;

        user_datagram_protocol_module_t * user_datagram;
        transmission_control_protocol_module_t * transmission_control;
        internet_protocol_version6_extension_hopbyhop_module_t * internet_protocol_version6_extension_hopbyhop;
        internet_protocol_version6_extension_routing_module_t * internet_protocol_version6_extension_routing;
        internet_protocol_version6_extension_fragment_module_t * internet_protocol_version6_extension_fragment;
        internet_protocol_version6_extension_destination_module_t * internet_protocol_version6_extension_destination;
        internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4;
        internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6;
    } protocol;

    struct {
        protocol_module_map_t * transport;
    } protocolmap;

    socket_client_event_subscription_pool_t * pool;
};

struct virtual_private_network_application_client_func {
    virtual_private_network_application_client_t * (*rem)(virtual_private_network_application_client_t *);
    int32_t (*on)(virtual_private_network_application_client_t *);
    int32_t (*off)(virtual_private_network_application_client_t *);
    int32_t (*run)(virtual_private_network_application_client_t *);
};

#define virtual_private_network_application_client_rem(application)     ((application)->func->rem(application))
#define virtual_private_network_application_client_on(application)      ((application)->func->on(application))
#define virtual_private_network_application_client_off(application)     ((application)->func->off(application))
#define virtual_private_network_application_client_run(application)     ((application)->func->run(application))

extern virtual_private_network_application_client_t * virtual_private_network_application_client_get(void);
extern network_tun_t * virtual_private_network_application_client_tun_get(virtual_private_network_application_client_t * application);

struct virtual_private_network_application_config {
    uint16_t port;
};

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_CLIENT_APPLICATION__H__
