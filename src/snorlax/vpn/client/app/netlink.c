#include <snorlax/socket/event/subscription.h>
#include <snorlax/socket.h>
#include <snorlax/network/netlink.h>

#include "netlink.h"

static void onSubscription(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onOpen(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onRead(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onWrite(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onClose(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onException(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);

static socket_event_subscription_handler_t handler[descriptor_event_type_max] = {
    onSubscription,
    onOpen,
    onRead,
    onWrite,
    onClose,
    onException
};

extern socket_event_subscription_handler_t * vpn_client_app_netlink_event_subscription_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void onOpen(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
}

static void onRead(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE

    socket_buffer_t * buffer = socket_event_subscription_buffer_get(subscription);

    network_netlink_message_t * in = nil;
    network_netlink_request_t * out = nil;

    struct nlmsghdr * request = nil;
    struct nlmsghdr * response = nil;

    while(request = network_netlink_request_nlmsghdr_get(out = (network_netlink_request_t *) buffer_head(buffer->out))) {
        netlink_protocol_debug(stdout, request);
        while(response = network_netlink_message_nlmsghdr_get(in = (network_netlink_message_t *) buffer_front(buffer->in))) {
            if(response->nlmsg_seq < request->nlmsg_seq) {
                netlink_protocol_debug(stdout, response);

                network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);

                buffer_shrink(buffer->in);

                continue;
            } else if(response->nlmsg_seq == request->nlmsg_seq) {
                // TODO: 
                if(response->nlmsg_type == NLMSG_DONE) {
                    netlink_protocol_debug(stdout, response);

                    network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);
                    network_netlink_request_done_set(out, network_netlink_request_done_get(out) + request->nlmsg_len);

                    buffer_shrink(buffer->in);
                    buffer_shrink(buffer->out);

                    break;
                } else if(response->nlmsg_type == NLMSG_ERROR) {
                    netlink_protocol_debug(stdout, response);

                    network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);
                    network_netlink_request_done_set(out, network_netlink_request_done_get(out) + request->nlmsg_len);

                    buffer_shrink(buffer->in);
                    buffer_shrink(buffer->out);

                    break;
                } else {
                    netlink_protocol_debug(stdout, response);

                    network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);
                    
                    buffer_shrink(buffer->in);

                    continue;
                }
            } else {
                request = nil;

                break;
            }
        }

        if(request == nil || response == nil) break;
    }
}

static void onWrite(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE

    socket_buffer_t * buffer = socket_event_subscription_buffer_get(subscription);

    network_netlink_request_t * out = nil;

    printf("%p\n", out = (network_netlink_request_t *) buffer_head(buffer->out));
    printf("%lu\n", out->done);
    printf("%lu\n", out->position);
    printf("%lu\n", out->size);
    printf("%lu\n", out->capacity);
    printf("%p\n", network_netlink_request_nlmsghdr_get(out = (network_netlink_request_t *) buffer_head(buffer->out)));
}

static void onClose(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void onException(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}