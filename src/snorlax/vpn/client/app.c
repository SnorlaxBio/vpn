#include <linux/netlink.h>

#include <snorlax/network/tun.h>
#include <snorlax/network/netlink.h>
#include <snorlax/socket/event/subscription.h>
#include <snorlax/descriptor/event/subscription.h>

#include "app.h"
#include "app/config.h"
#include "event/subscription.h"
#include "app/tun.h"
#include "app/netlink.h"

static vpn_client_app_t * app = nil;

int main(int argc, char ** argv) {
    app = vpn_client_app_gen();
    vpn_client_app_on(app);

    int32_t ret = vpn_client_app_run(app);

    app = vpn_client_app_rem(app);

    return ret;
}

static vpn_client_app_t * vpn_client_app_func_rem(vpn_client_app_t * application);
static int32_t vpn_client_app_func_on(vpn_client_app_t * application);
static int32_t vpn_client_app_func_off(vpn_client_app_t * application);
static int32_t vpn_client_app_func_run(vpn_client_app_t * application);

static vpn_client_app_func_t func = {
    vpn_client_app_func_rem,
    vpn_client_app_func_on,
    vpn_client_app_func_off,
    vpn_client_app_func_run
};

extern vpn_client_app_t * vpn_client_app_gen(void) {
    vpn_client_app_t * application = (vpn_client_app_t *) calloc(1, sizeof(vpn_client_app_t));

    application->func = address_of(func);

    return application;
}

static vpn_client_app_t * vpn_client_app_func_rem(vpn_client_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    // descriptor_event_subscription_t * tun;
    // socket_event_subscription_t * netlink;

    application->netlink = socket_event_subscription_rem(application->netlink);
    application->tun = descriptor_event_subscription_rem(application->tun);
    application->pool = socket_client_event_subscription_pool_rem(application->pool);


    application->engine = event_engine_rem(application->engine);

    free(application);

    return nil;
}

static int32_t vpn_client_app_func_on(vpn_client_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    if(application->engine == nil){
        application->engine = event_engine_gen();

        if(event_engine_on(application->engine) != success) {
#ifndef   RELEASE
            snorlaxdbg(true, false, "critical", "");
#endif // RELEASE
        }

        const vpn_client_app_config_t * config = vpn_client_app_client_get();

        application->netlink = event_engine_socket_sub(application->engine, (socket_t *) network_netlink_gen(NETLINK_GENERIC), vpn_client_app_netlink_event_subscription_handler_get());
        application->tun = event_engine_descriptor_sub(application->engine, (descriptor_t *) network_tun_gen(), vpn_client_app_tun_event_subscription_handler_get());
        application->pool = socket_client_event_subscription_pool_gen(vpn_client_subscription_handler_get());
        for(int32_t i = 0; i < config->client_pool_size; i++) {
            // socket_client_event_subscription_t * subscription = event_engine_socket_client_sub()
            // socket_client_event_subscription_pool_node_gen(subscription);
            // socket_client_event_subscription_pool_push(application->pool, )
        }

        printf("implement socket\n");
    }

    return success;
}

static int32_t vpn_client_app_func_off(vpn_client_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    if(application->engine) event_engine_off(application->engine, vpn_client_app_engine_cancel);

    return success;
}

static int32_t vpn_client_app_func_run(vpn_client_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    return event_engine_run(application->engine);
}

extern void vpn_client_app_engine_cancel(___notnull const event_engine_t * engine) {
#ifndef   RELEASE
    snorlaxdbg(engine == nil, false, "critical", "");
#endif // RELEASE
}

extern network_netlink_t * vpn_client_app_netlink_descriptor_get(void) {
    return (network_netlink_t *) app->netlink->descriptor;
}

extern socket_event_subscription_t * vpn_client_app_netlink_subscription_get(void) {
    return app->netlink;
}