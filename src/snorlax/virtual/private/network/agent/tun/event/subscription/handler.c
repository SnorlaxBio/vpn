#include "handler.h"

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