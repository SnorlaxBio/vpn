#include <sys/socket.h>

#include <snorlax/network/netlink.h>
#include <snorlax/descriptor/event/subscription.h>
#include <snorlax/protocol/internet.h>

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
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE

    descriptor_buffer_t * buffer = descriptor_event_subscription_buffer_get(subscription);
    buffer_node_t * in = nil;
    internet_protocol_module_t * module = vpn_client_app_internet_protocol_module_get();

    while(buffer_node_length(in = buffer_front(buffer->in)) > 0) {
        uint8_t * datagram = (uint8_t *) buffer_node_front(in);
        uint64_t datagramlen = buffer_node_length(in);

        internet_protocol_context_t * context = nil;

        internet_protocol_module_deserialize(module, datagram, datagramlen, nil, &context);

        if(internet_protocol_context_error_get(context)) {
            /**
             * TODO: 이 부분에서 버퍼를 지워야 하는지 혹은 더 읽어야 하는지 판단해야 한다.
             */
            snorlaxdbg(false, true, "debug", "errno => %d", internet_protocol_context_error_get(context));
            context = internet_protocol_context_rem(context);
            return;
        }

        uint64_t length = internet_protocol_context_packetlen_get(context);

        context = internet_protocol_version4_context_rem(context);

        buffer_node_position_set(in, buffer_node_position_get(in) + length);

        buffer_shrink(buffer->in);
    }

#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
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
