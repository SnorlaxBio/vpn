#include "../../../control.h"

static void onSubscription(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onOpen(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onRead(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onWrite(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onClose(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onException(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);

socket_client_event_subscription_handler_t handler[descriptor_event_type_max] = {
    onSubscription,
    onOpen,
    onRead,
    onWrite,
    onClose,
    onException
};

extern socket_client_event_subscription_handler_t * transmission_control_block_client_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
    snorlaxdbg(subscription->descriptor->meta == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_client_t * agent = (transmission_control_block_client_t *) subscription->descriptor->meta;

    snorlaxdbg(false, true, "debug", "");


    transmission_control_block_client_on(agent, transmission_control_block_agent_event_type_subscription, node);
}

static void onOpen(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
    snorlaxdbg(subscription->descriptor->meta == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_client_t * agent = (transmission_control_block_client_t *) subscription->descriptor->meta;

    snorlaxdbg(false, true, "debug", "");

    transmission_control_block_client_on(agent, transmission_control_block_agent_event_type_open, node);
}

static void onRead(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
    snorlaxdbg(subscription->descriptor->meta == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_client_t * agent = (transmission_control_block_client_t *) subscription->descriptor->meta;

    snorlaxdbg(false, true, "debug", "");

    transmission_control_block_client_on(agent, transmission_control_block_agent_event_type_read, node);
}

static void onWrite(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
    snorlaxdbg(subscription->descriptor->meta == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_client_t * agent = (transmission_control_block_client_t *) subscription->descriptor->meta;

    snorlaxdbg(false, true, "debug", "");

    transmission_control_block_client_on(agent, transmission_control_block_agent_event_type_write, node);
}

static void onClose(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
    snorlaxdbg(subscription->descriptor->meta == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_client_t * agent = (transmission_control_block_client_t *) subscription->descriptor->meta;

    snorlaxdbg(false, true, "debug", "");

    transmission_control_block_client_on(agent, transmission_control_block_agent_event_type_close, node);

    transmission_control_block_close(agent->block);
}

static void onException(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(subscription == nil, false, "critical", "");
    snorlaxdbg(subscription->descriptor->meta == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_client_t * agent = (transmission_control_block_client_t *) subscription->descriptor->meta;

    snorlaxdbg(false, true, "debug", "");

    socket_client_t * s = subscription->descriptor;
    descriptor_exception_t * exception = descriptor_exception_get((descriptor_t *) s);

    if(exception != nil) { 
        snorlaxdbg(false, true, "debug", "");
    }

    transmission_control_block_client_on(agent, transmission_control_block_agent_event_type_exception, node);
}