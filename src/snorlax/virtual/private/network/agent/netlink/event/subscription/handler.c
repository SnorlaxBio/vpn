#include <snorlax/network/netlink.h>

#include "handler.h"

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

extern socket_event_subscription_handler_t * virtual_private_network_agent_netlink_event_subscription_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void onOpen(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

___implement static void onRead(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    /**
     * TODO: ### 20240825 | UPGRADE BUSINESS LOGIC / 실패하면 어떻게 처리해 하는지 정하고 그것을 구현한다.
     * TODO: ### 20240825 | 아래의 로직을 함수로 만들어서 PROTOCOL MODULE 을 만들고 PROTOCOL LIB 로 옮긴다.
     */

    socket_buffer_t * buffer = socket_event_subscription_buffer_get(subscription);

    network_netlink_message_t * in = nil;
    network_netlink_request_t * out = nil;

    struct nlmsghdr * request = nil;
    struct nlmsghdr * response = nil;

    while(request = network_netlink_request_nlmsghdr_get(out = (network_netlink_request_t *) buffer_head(buffer->out))) {
        while(response = network_netlink_message_nlmsghdr_get(in = (network_netlink_message_t *) buffer_front(buffer->in))) {
            if(response->nlmsg_seq < request->nlmsg_seq) {
                /**
                 * 오래 전에 요청한 메시지다. 이 부분이 호출된 다는 것은 등록되지 않은 오래된 요청이 이제야 처리되었음을 의미한다.
                 * 버그에 의해서 호출될 경우도 있다. 이럴 경우를 위해서 이와 같은 로그가 나오면 메시지 처리 함수에 버그가 있는지 확인해야 한다.
                 */
                snorlaxdbg(false, true, "notice", "");

                network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);

                buffer_shrink(buffer->in);

                continue;
            }
            if(response->nlmsg_seq == request->nlmsg_seq) {
                if(response->nlmsg_type == NLMSG_DONE) {
                    network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);
                    network_netlink_request_done_set(out, network_netlink_request_done_get(out) + request->nlmsg_len);

                    network_netlink_request_on(out, request, network_netlink_request_state_done, response);

                    buffer_shrink(buffer->in);
                    buffer_shrink(buffer->out);

                    break;
                }
                if(response->nlmsg_type == NLMSG_ERROR) {
                    network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);
                    network_netlink_request_done_set(out, network_netlink_request_done_get(out) + request->nlmsg_len);

                    network_netlink_request_on(out, request, network_netlink_request_state_done, response);

                    buffer_shrink(buffer->in);
                    buffer_shrink(buffer->out);
                    
                    break;
                }

                network_netlink_message_position_set(in, network_netlink_message_position_get(in) + response->nlmsg_len);
                network_netlink_request_on(out, request, network_netlink_request_state_response, response);
                buffer_shrink(buffer->in);

                continue;
            }

            /**
             * `response->nlmsg_seq > request->nlmsg_seq` 와 같은 상태로 버그로 봐야 하지만,
             * 아직 요청되지 않은 메시지가 처리되어 나온 결과이다. 동작하도록 로그만 출력하고 루프에서 나온다.
             * 이와 같이 나오면 현재의 로직은 그 다음 메시지를 처리하지 못하게 된다. 그렇기 때문에 
             * REQUEST 를 삭제한다.
             * 
             * RESPONSE 가 없는 REQUEST 가 존재할 수 있다.
             */

            snorlaxdbg(true, false, "notice", "");

            network_netlink_request_done_set(out, network_netlink_request_done_get(out) + request->nlmsg_len);

            buffer_shrink(buffer->out);

            request = nil;

            break;
        }

        if(request == nil || response == nil){
            /**
             * 응답 메시지를 아직 수신하지 않았다.
             */
            break;
        }
    }
}

static void onWrite(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void onClose(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}

static void onException(___notnull socket_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
}