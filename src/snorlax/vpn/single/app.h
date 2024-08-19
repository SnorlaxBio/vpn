#ifndef   __SNORLAX__VPN_SINGLE__H__
#define   __SNORLAX__VPN_SINGLE__H__

#include <linux/netlink.h>

#include <snorlax.h>
#include <snorlax/event/engine.h>
#include <snorlax/socket/client/event/subscription/pool.h>

#include <snorlax/protocol/internet.h>
#include <snorlax/protocol/internet/version4.h>
#include <snorlax/protocol/internet/version6.h>
#include <snorlax/protocol/internet/version4/control/message.h>
#include <snorlax/protocol/internet/version6/control/message.h>
#include <snorlax/protocol/internet/user/datagram.h>
#include <snorlax/protocol/internet/transmission/control.h>

struct vpn_single_app;
struct vpn_single_app_func;

typedef struct vpn_single_app vpn_single_app_t;
typedef struct vpn_single_app_func vpn_single_app_func_t;

struct vpn_single_app {
    vpn_single_app_func_t * func;
    sync_t * sync;
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

    char ifname[16];
    struct {
        struct {
            uint32_t version4;
            uint8_t version6[16];
        } addr;
    } internet;
};

struct vpn_single_app_func {
    vpn_single_app_t * (*rem)(vpn_single_app_t *);
    int32_t (*on)(vpn_single_app_t *);
    int32_t (*off)(vpn_single_app_t *);
    int32_t (*run)(vpn_single_app_t *);
};

extern vpn_single_app_t * vpn_single_app_gen(void);

#define vpn_client_app_rem(app)         ((app)->func->rem(app))
#define vpn_client_app_on(app)          ((app)->func->on(app))
#define vpn_client_app_off(app)         ((app)->func->off(app))
#define vpn_client_app_run(app)         ((app)->func->run(app))

extern void vpn_single_app_engine_cancel(___notnull const event_engine_t * engine);

extern vpn_single_app_t * vpn_single_app_get(void);

extern void vpn_single_app_interface_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response);
extern void vpn_single_app_network_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response);

#endif // __SNORLAX__VPN_SINGLE__H__
