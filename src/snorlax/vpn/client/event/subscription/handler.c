#include "handler.h"

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

extern socket_client_event_subscription_handler_t * vpn_client_event_subscription_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug",  "");
}

static void onOpen(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug",  "");
}

static void onRead(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug",  "");
}

static void onWrite(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug",  "");
}

static void onClose(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug",  "");
}

static void onException(___notnull socket_client_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
    snorlaxdbg(false, true, "debug",  "");
}
