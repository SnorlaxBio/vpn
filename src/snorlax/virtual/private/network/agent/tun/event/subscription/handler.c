#include "handler.h"

#include "../../../application.h"

static void onSubscription(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onOpen(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onRead(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onWrite(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onClose(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onException(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);

static descriptor_event_subscription_handler_t handler[descriptor_event_type_max] = {
    onSubscription,
    onOpen,
    onRead,
    onWrite,
    onClose,
    onException
};

extern descriptor_event_subscription_handler_t * virtual_private_network_agent_tun_event_subscription_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void onOpen(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    uint8_t all[4] = { 0, 0, 0, 0 };
    uint8_t addr[4] = { 10, 0, 0, 1 };
    const char * ifname = "tun0";

    virtual_private_network_application_agent_t * application = virtual_private_network_application_agent_get();

    network_netlink_req((network_netlink_t * ) application->netlink->descriptor, application->netlink, network_netlink_message_ipaddr_add_gen(AF_INET, addr, 24, ifname), nil);
    network_netlink_req((network_netlink_t * ) application->netlink->descriptor, application->netlink, network_netlink_message_iplink_setup_gen(ifname), virtual_private_network_application_agent_interface_on);
    network_netlink_req((network_netlink_t * ) application->netlink->descriptor, application->netlink, network_netlink_message_iprule_add_gen(network_netlink_table_main_mark, network_netlink_table_main_priority, network_netlink_table_main_id), nil);
    network_netlink_req((network_netlink_t * ) application->netlink->descriptor, application->netlink, network_netlink_message_iprule_add_gen(network_netlink_table_tun_mark, network_netlink_table_tun_priority, network_netlink_table_tun_id), nil);
    network_netlink_req((network_netlink_t * ) application->netlink->descriptor, application->netlink, network_netlink_message_iproute_prepend_gen(all, 0, addr, network_netlink_table_tun_id), virtual_private_network_application_agent_network_on);

    // // TODO: ENCAPSULATED PACKET MUST BE ROUTED VIA REAL ROUTER
    // network_netlink_req(descriptor, app->netlink, network_netlink_message_iprule_add_gen(network_netlink_table_tun_mark, network_netlink_table_tun_priority, network_netlink_table_tun_id), nil);
    // network_netlink_req(descriptor, app->netlink, network_netlink_message_iproute_prepend_gen(all, 0, addr, network_netlink_table_tun_id), vpn_single_app_network_on);

    // virtual_private_network_application_agent_netlink_req_turnon(application, application->netlink);

//    virtual_private_network_application_agent_netlink_subscription_get(application);
}

static void onRead(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void onWrite(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void onClose(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void onException(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}