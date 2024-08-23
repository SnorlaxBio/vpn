#include "../control.h"

static void onSubscription(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onOpen(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onRead(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onWrite(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onClose(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onException(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);

static socket_client_event_subscription_handler_t handler[descriptor_event_type_max] = {
    onSubscription,
    onOpen,
    onRead,
    onWrite,
    onClose,
    onException
};

extern socket_client_event_subscription_handler_t * transmission_control_protocol_client_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug", "");
}

static void onOpen(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug", "");



    // GET METATA
}

static void onRead(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug", "");

    transmission_control_block_agent_single_meta_t * meta = (transmission_control_block_agent_single_meta_t *) subscription->meta;

    snorlaxdbg(meta == nil, false, "critical", "");

    descriptor_buffer_t * buffer = socket_client_event_subscription_buffer_get(subscription);
    buffer_node_t * in = nil;
    // buffer_t * in = buffer->in;

    while(buffer_node_length(in = buffer_front(buffer->in)) > 0) {
        int32_t n = transmission_control_block_send(meta->block, (uint8_t *) buffer_node_front(in), buffer_node_length(in));

        if(n == 0) {
            snorlaxdbg(false, true, "check", "");
            break;
        }

        snorlaxdbg(n == fail, false, "critical", "이와 같은 상황을 분석해서 정확히 에러처리를 하자.");

        snorlaxdbg(false, true, "refactor", "아래의 구문을 하나로 합치면 코드가 짧아질 것이다.");
        buffer_node_position_set(in, buffer_node_position_get(in) + n);
        buffer_shrink(buffer->in);
    }

    
}

static void onWrite(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug", "");
}

static void onClose(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug", "");
}

static void onException(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug", "");
}