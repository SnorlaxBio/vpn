#include <sys/socket.h>

#include <snorlax/network/netlink.h>

#include "tun.h"
#include "../app.h"

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

extern descriptor_event_subscription_handler_t * vpn_client_app_tun_event_subscription_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void onOpen(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "tun open");
#endif // RELEASE
    uint8_t all[4] = { 0, 0, 0, 0 };
    uint8_t addr[4] = { 10, 0, 0, 1 };

    // TODO: IMPLEMENT CALLBACK
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), network_netlink_message_ipaddr_add_gen(AF_INET, addr, 24, "tun0"));
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), network_netlink_message_iplink_setup_gen("tun0"));
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), network_netlink_message_iprule_add_gen(network_netlink_table_main_mark, network_netlink_table_main_priority, network_netlink_table_main_id));
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), network_netlink_message_iprule_add_gen(network_netlink_table_tun_mark, network_netlink_table_tun_priority, network_netlink_table_tun_id));
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), network_netlink_message_iproute_prepend_gen(all, 0, addr, network_netlink_table_tun_id));
    // DEFAULT ROUTE GET
}

static void onRead(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    printf("onRead\n");
}

static void onWrite(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void onClose(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    
}

static void onException(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

