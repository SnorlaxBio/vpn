#include "server.h"

// typedef void (*socket_server_event_subscription_handler_t)(___notnull socket_server_event_subscription_t *, uint32_t, event_subscription_event_t *);

static void onSubscription(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onOpen(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onRead(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onWrite(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onClose(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void onException(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);

static socket_server_event_subscription_handler_t handler[descriptor_event_type_max] = {
    onSubscription,
    onOpen,
    onRead,
    onWrite,
    onClose,
    onException
};

extern socket_server_event_subscription_handler_t * vpn_server_event_subscription_handler_get(void) {
    return handler;
}

static void onSubscription(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
}

static void onOpen(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
}

static void onRead(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
}

static void onWrite(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
}

static void onClose(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
}

static void onException(___notnull socket_server_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {
#ifndef   RELEASE
    snorlaxdbg(false, true, "debug", "");
#endif // RELEASE
}
