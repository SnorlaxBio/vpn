#include <sys/socket.h>

#include <snorlax/network/netlink.h>

#include "tun.h"
#include "../app.h"

static void onNetlinkIPRoutePrepend(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response);

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
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), vpn_client_app_netlink_subscription_get(), network_netlink_message_ipaddr_add_gen(AF_INET, addr, 24, "tun0"), nil);
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), vpn_client_app_netlink_subscription_get(), network_netlink_message_iplink_setup_gen("tun0"), nil);
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), vpn_client_app_netlink_subscription_get(), network_netlink_message_iprule_add_gen(network_netlink_table_main_mark, network_netlink_table_main_priority, network_netlink_table_main_id), nil);
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), vpn_client_app_netlink_subscription_get(), network_netlink_message_iprule_add_gen(network_netlink_table_tun_mark, network_netlink_table_tun_priority, network_netlink_table_tun_id), nil);
    network_netlink_req(vpn_client_app_netlink_descriptor_get(), vpn_client_app_netlink_subscription_get(), network_netlink_message_iproute_prepend_gen(all, 0, addr, network_netlink_table_tun_id), onNetlinkIPRoutePrepend);
    // TODO: 마지막 메시지까지 처리되면, 로그인을 처리하도록 하자.
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

static void onNetlinkIPRoutePrepend(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response) {
#ifndef   RELEASE
    snorlaxdbg(request == nil, false, "critical", "");
    snorlaxdbg(response == nil, false, "critical", "");
#endif // RELEASE

    if(state == network_netlink_request_state_done) {
        // 모든 클라이언트를 만든다 ...
        // 모든 클라리언트를 접속하도록 한다 ...
        printf("done\n");
    }
}
