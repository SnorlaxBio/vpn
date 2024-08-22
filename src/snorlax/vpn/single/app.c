#include <sys/socket.h>
#include <arpa/inet.h>

#include <snorlax/network/tun.h>
#include <snorlax/network/netlink.h>
#include <snorlax/socket/event/subscription.h>
#include <snorlax/descriptor/event/subscription.h>
#include <snorlax/protocol.h>
#include <snorlax/network/if.h>
// #include <snorlax/network

#include "app.h"
#include "app/config.h"
#include "app/tun.h"
#include "app/netlink.h"
#include "protocol/transmission/control.h"
#include "protocol/internet.h"
#include "protocol/internet/version4.h"
#include "protocol/internet/version6.h"
#include "../agent.h"

static vpn_single_app_t * app = nil;

extern vpn_single_app_t * vpn_single_app_get(void) {
    return app;
}

int main(int argc, char ** argv) {
    app = vpn_single_app_gen();
    vpn_agent_set((vpn_agent_t *) app);
    vpn_client_app_on(app);

    int32_t ret = vpn_client_app_run(app);

    app = vpn_client_app_rem(app);
    vpn_agent_set(nil);

    return ret;
}

static vpn_single_app_t * vpn_single_app_func_rem(vpn_single_app_t * application);
static int32_t vpn_single_app_func_on(vpn_single_app_t * application);
static int32_t vpn_single_app_func_off(vpn_single_app_t * application);
static int32_t vpn_single_app_func_run(vpn_single_app_t * application);

static vpn_single_app_func_t func = {
    vpn_single_app_func_rem,
    vpn_single_app_func_on,
    vpn_single_app_func_off,
    vpn_single_app_func_run
};

static protocol_module_t * transport_protocol_map_get(protocol_module_map_t * map, uint64_t no) {
    switch(no) {
        case transmission_control_protocol_no:                      return map->modules[0];
        case user_datagram_protocol_no:                             return map->modules[1];
        case internet_protocol_version6_extension_hopbyhop_no:      return map->modules[2];
        case internet_control_message_protocol_version4_no:         return map->modules[3];
        case internet_protocol_version6_extension_routing_no:       return map->modules[4];
        case internet_protocol_version6_extension_fragment_no:      return map->modules[5];
        case internet_protocol_version6_extension_destination_no:   return map->modules[6];
        case internet_control_message_protocol_version6_no:         return map->modules[7];
        default:                                                    return nil;
    }
}

extern vpn_single_app_t * vpn_single_app_gen(void) {
    vpn_single_app_t * application = (vpn_single_app_t *) calloc(1, sizeof(vpn_single_app_t));

    application->func = address_of(func);

    application->protocol.transmission_control = transmission_control_protocol_module_gen(nil, transmission_control_protocol_module_func_vpn_single_on);
    application->protocol.user_datagram = user_datagram_protocol_module_gen(nil, user_datagram_protocol_module_func_on);
    application->protocol.internet_protocol_version6_extension_hopbyhop = internet_protocol_version6_extension_hopbyhop_module_gen(internet_protocol_version6_extension_hopbyhop_module_func_on);
    application->protocol.internet_control_message_protocol_version4 = internet_control_message_protocol_version4_module_gen(internet_control_message_protocol_version4_module_func_on);
    application->protocol.internet_protocol_version6_extension_routing = internet_protocol_version6_extension_routing_module_gen(internet_protocol_version6_extension_routing_module_func_on);
    application->protocol.internet_protocol_version6_extension_fragment = internet_protocol_version6_extension_fragment_module_gen(internet_protocol_version6_extension_fragment_module_func_on);
    application->protocol.internet_protocol_version6_extension_destination = internet_protocol_version6_extension_destination_module_gen(internet_protocol_version6_extension_destination_module_func_on);
    application->protocol.internet_control_message_protocol_version6 = internet_control_message_protocol_version6_module_gen(internet_control_message_protocol_version6_module_func_on);

    protocol_module_t * modules[] = {
        (protocol_module_t *) application->protocol.transmission_control,
        (protocol_module_t *) application->protocol.user_datagram,
        (protocol_module_t *) application->protocol.internet_protocol_version6_extension_hopbyhop,
        (protocol_module_t *) application->protocol.internet_control_message_protocol_version4,
        (protocol_module_t *) application->protocol.internet_protocol_version6_extension_routing,
        (protocol_module_t *) application->protocol.internet_protocol_version6_extension_fragment,
        (protocol_module_t *) application->protocol.internet_protocol_version6_extension_destination,
        (protocol_module_t *) application->protocol.internet_control_message_protocol_version6,
    };
    printf("%p\n", application->protocol.transmission_control);
    printf("%p\n", application->protocol.user_datagram);
    printf("%p\n", application->protocol.internet_protocol_version6_extension_hopbyhop);
    printf("%p\n", application->protocol.internet_control_message_protocol_version4);
    printf("%p\n", application->protocol.internet_protocol_version6_extension_routing);
    printf("%p\n", application->protocol.internet_protocol_version6_extension_fragment);
    printf("%p\n", application->protocol.internet_protocol_version6_extension_destination);
    printf("%p\n", application->protocol.internet_control_message_protocol_version6);

    printf("%lu\n", sizeof(modules) / sizeof(protocol_module_t *));

    application->protocolmap.transport = protocol_module_map_gen(modules, sizeof(modules) / sizeof(protocol_module_t *), transport_protocol_map_get);

    internet_protocol_version4_module_t * version4 = internet_protocol_version4_module_gen(application->protocolmap.transport, internet_protocol_version4_module_func_vpn_single_on, address_of(application->internet.addr.version4));
    internet_protocol_version6_module_t * version6 = internet_protocol_version6_module_gen(application->protocolmap.transport, internet_protocol_version6_module_func_vpn_single_on, application->internet.addr.version6);

    application->protocol.internet = internet_protocol_module_gen(application->protocolmap.transport, internet_protocol_module_func_vpn_single_on, version4, version6);

    return application;
}

static vpn_single_app_t * vpn_single_app_func_rem(vpn_single_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    // descriptor_event_subscription_t * tun;
    // socket_event_subscription_t * netlink;

    application->netlink = socket_event_subscription_rem(application->netlink);
    application->tun = descriptor_event_subscription_rem(application->tun);

    application->engine = event_engine_rem(application->engine);

    application->protocol.internet = internet_protocol_module_rem(application->protocol.internet);
    
    // .version4 = internet_protocol_version4_module_rem(application->protocol.internet.version4);
    // application->protocol.internet.version6 = internet_protocol_version6_module_rem(application->protocol.internet.version6);

    free(application);

    return nil;
}

static int32_t vpn_single_app_func_on(vpn_single_app_t * application) {
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

        const vpn_single_app_config_t * config = vpn_single_app_config_get();

        application->netlink = event_engine_socket_sub(application->engine, (socket_t *) network_netlink_gen(NETLINK_GENERIC), vpn_single_app_netlink_event_subscription_handler_get(), nil);
        application->tun = event_engine_descriptor_sub(application->engine, (descriptor_t *) network_tun_gen(), vpn_single_app_tun_event_subscription_handler_get(), nil);
        // application->pool = socket_client_event_subscription_pool_gen(vpn_client_subscription_handler_get());
        // for(int32_t i = 0; i < config->client_pool_size; i++) {
        //     // socket_client_event_subscription_t * subscription = event_engine_socket_client_sub()
        //     // socket_client_event_subscription_pool_node_gen(subscription);
        //     // socket_client_event_subscription_pool_push(application->pool, )
        // }

        printf("implement socket\n");
    }

    return success;
}

static int32_t vpn_single_app_func_off(vpn_single_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    if(application->engine) event_engine_off(application->engine, vpn_single_app_engine_cancel);

    return success;
}

static int32_t vpn_single_app_func_run(vpn_single_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    return event_engine_run(application->engine);
}

extern void vpn_single_app_engine_cancel(___notnull const event_engine_t * engine) {
#ifndef   RELEASE
    snorlaxdbg(engine == nil, false, "critical", "");
#endif // RELEASE
}

extern void vpn_single_app_interface_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response) {
    snorlaxdbg(false, true, "debug", "");
    if(state == network_netlink_request_state_done) {
        if(network_if_addr_get("tun0", address_of(app->internet.addr.version4), app->internet.addr.version6) == fail) {
            snorlaxdbg(false, true, "warning", "");
        }
    }
}

extern void vpn_single_app_network_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response) {
    snorlaxdbg(false, true, "debug", "");
}