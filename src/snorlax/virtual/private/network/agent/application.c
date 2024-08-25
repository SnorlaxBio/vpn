#include <string.h>

#include <snorlax/network/if.h>

#include "application.h"

#include "protocol/transmission/control.h"
#include "protocol/user/datagram.h"

#include "protocol/internet.h"

#include "protocol/internet/version4.h"
#include "protocol/internet/version6.h"

#include "protocol/internet/version4/control/message.h"
#include "protocol/internet/version6/control/message.h"

#include "protocol/internet/version6/extension/destination.h"
#include "protocol/internet/version6/extension/fragment.h"
#include "protocol/internet/version6/extension/hopbyhop.h"
#include "protocol/internet/version6/extension/routing.h"

#include "tun/event/subscription/handler.h"
#include "netlink/event/subscription/handler.h"

static virtual_private_network_application_agent_t * application = nil;

static virtual_private_network_application_agent_t * virtual_private_network_application_agent_func_rem(virtual_private_network_application_agent_t * o);
static int32_t virtual_private_network_application_agent_func_on(virtual_private_network_application_agent_t * o);
static int32_t virtual_private_network_application_agent_func_off(virtual_private_network_application_agent_t * o);
static int32_t virtual_private_network_application_agent_func_run(virtual_private_network_application_agent_t * o);

static protocol_module_t * virtual_private_network_application_agent_transport_protocol_map_get(protocol_module_map_t * map, uint64_t no);
static void virtual_private_network_application_agent_event_engine_cancel(___notnull const event_engine_t * engine);

static virtual_private_network_application_agent_func_t func = {
    virtual_private_network_application_agent_func_rem,
    virtual_private_network_application_agent_func_on,
    virtual_private_network_application_agent_func_off,
    virtual_private_network_application_agent_func_run
};

static virtual_private_network_application_config_t config = {
    .port = 6207,
    .ifname = "tun0"
};

static virtual_private_network_application_agent_t * virtual_private_network_application_agent_gen(virtual_private_network_application_config_t * config);

int main(int argc, char ** argv) {
    application = virtual_private_network_application_agent_gen(address_of(config));

    if(virtual_private_network_application_agent_on(application) == success) {
        int ret = virtual_private_network_application_agent_run(application);

        application = virtual_private_network_application_agent_rem(application);

        return ret;
    }

    application = virtual_private_network_application_agent_rem(application);
    return fail;
}

static protocol_module_t * virtual_private_network_application_agent_transport_protocol_map_get(protocol_module_map_t * map, uint64_t no) {
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

static virtual_private_network_application_agent_t * virtual_private_network_application_agent_gen(virtual_private_network_application_config_t * config) {
#ifndef   RELEASE
    snorlaxdbg(application != nil, false, "critical", "");
#endif // RELEASE

    virtual_private_network_application_agent_t * o = application;

    if(o == nil) {
        snorlaxdbg(config == nil, false, "critical", "");

        o = (virtual_private_network_application_agent_t *) calloc(1, sizeof(virtual_private_network_application_agent_t));

        o->func = address_of(func);

        o->config = config;

        strcpy(o->config->ifname, config->ifname);

        o->TransmissionControlProtocol                  = transmission_control_protocol_module_gen(nil, virtual_private_network_agent_transmission_control_protocol_on);
        o->UserDatagramProtocol                         = user_datagram_protocol_module_gen(nil, virtual_private_network_agent_user_datagram_protocol_on);
        o->InternetProtocolVersion6ExtensionDestination = internet_protocol_version6_extension_destination_module_gen(virtual_private_network_agent_internet_protocol_version6_extension_destination_on);
        o->InternetProtocolVersion6ExtensionFragment    = internet_protocol_version6_extension_fragment_module_gen(virtual_private_network_agent_internet_protocol_version6_extension_fragment_on);
        o->InternetProtocolVersion6ExtensionHopbyhop    = internet_protocol_version6_extension_hopbyhop_module_gen(virtual_private_network_agent_internet_protocol_version6_extension_hopbyhop_on);
        o->InternetProtocolVersion6ExtensionRouting     = internet_protocol_version6_extension_routing_module_gen(virtual_private_network_agent_internet_protocol_version6_extension_routing_on);
        o->InternetControlMessageProtocolVersion4       = internet_control_message_protocol_version4_module_gen(virtual_private_network_agent_internet_control_message_protocol_version4_on);
        o->InternetControlMessageProtocolVersion6       = internet_control_message_protocol_version6_module_gen(virtual_private_network_agent_internet_control_message_protocol_version6_on);

        protocol_module_t * modules[] = {
            (protocol_module_t *) o->TransmissionControlProtocol,
            (protocol_module_t *) o->UserDatagramProtocol,
            (protocol_module_t *) o->InternetProtocolVersion6ExtensionHopbyhop,
            (protocol_module_t *) o->InternetControlMessageProtocolVersion4,
            (protocol_module_t *) o->InternetProtocolVersion6ExtensionRouting,
            (protocol_module_t *) o->InternetProtocolVersion6ExtensionFragment,
            (protocol_module_t *) o->InternetProtocolVersion6ExtensionDestination,
            (protocol_module_t *) o->InternetControlMessageProtocolVersion6
        };

        o->TransportLayer = protocol_module_map_gen(modules, sizeof(modules) / sizeof(protocol_module_t *), virtual_private_network_application_agent_transport_protocol_map_get);

        internet_protocol_version4_module_t * version4 = internet_protocol_version4_module_gen(o->TransportLayer, virtual_private_network_agent_internet_protocol_version4_on, address_of(o->InternetProtocolAddressVersion4));
        internet_protocol_version6_module_t * version6 = internet_protocol_version6_module_gen(o->TransportLayer, virtual_private_network_agent_internet_protocol_version6_on, o->InternetProtocolAddressVersion6);

        o->InternetProtocol = internet_protocol_module_gen(o->TransportLayer, virtual_private_network_agent_internet_protocol_on, version4, version6);
    }

    return o;
}

extern virtual_private_network_application_agent_t * virtual_private_network_application_agent_get(void) {
    return application;
}

extern virtual_private_network_application_t * virtual_private_network_application_get(void) {
    return (virtual_private_network_application_t *) application;
}

extern network_tun_t * virtual_private_network_application_tun_get(virtual_private_network_application_t * o) {
    return virtual_private_network_application_agent_tun_get((virtual_private_network_application_agent_t *) o);
}

extern network_tun_t * virtual_private_network_application_agent_tun_get(virtual_private_network_application_agent_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
    snorlaxdbg(o->tun == nil, false, "critical", "");
#endif // RELEASE

    return (network_tun_t *) o->tun->descriptor;
}

static virtual_private_network_application_agent_t * virtual_private_network_application_agent_func_rem(virtual_private_network_application_agent_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    if(o->tun) o->tun = socket_event_subscription_rem(o->tun);
    if(o->netlink) o->netlink = socket_event_subscription_rem(o->netlink);

    if(o->engine) o->engine = event_engine_rem(o->engine);
    
    if(o->InternetProtocol) o->InternetProtocol = internet_protocol_module_rem(o->InternetProtocol);
    if(o->TransmissionControlProtocol) o->TransmissionControlProtocol = transmission_control_protocol_module_rem(o->TransmissionControlProtocol);
    if(o->UserDatagramProtocol) o->UserDatagramProtocol = user_datagram_protocol_module_rem(o->UserDatagramProtocol);
    if(o->InternetProtocolVersion6ExtensionHopbyhop) o->InternetProtocolVersion6ExtensionHopbyhop = internet_protocol_version6_extension_hopbyhop_module_rem(o->InternetProtocolVersion6ExtensionHopbyhop);
    if(o->InternetProtocolVersion6ExtensionRouting) o->InternetProtocolVersion6ExtensionRouting = internet_protocol_version6_extension_routing_module_rem(o->InternetProtocolVersion6ExtensionRouting);
    if(o->InternetProtocolVersion6ExtensionFragment) o->InternetProtocolVersion6ExtensionFragment = internet_protocol_version6_extension_fragment_module_rem(o->InternetProtocolVersion6ExtensionFragment);
    if(o->InternetProtocolVersion6ExtensionDestination) o->InternetProtocolVersion6ExtensionDestination = internet_protocol_version6_extension_destination_module_rem(o->InternetProtocolVersion6ExtensionDestination);
    if(o->InternetControlMessageProtocolVersion4) o->InternetControlMessageProtocolVersion4 = internet_control_message_protocol_version4_module_rem(o->InternetControlMessageProtocolVersion4);
    if(o->InternetControlMessageProtocolVersion6) o->InternetControlMessageProtocolVersion6 = internet_control_message_protocol_version6_module_rem(o->InternetControlMessageProtocolVersion6);
    if(o->TransportLayer) o->TransportLayer = protocol_module_map_rem(o->TransportLayer);

    o->sync = sync_rem(o->sync);

    free(o);

    return nil;
}

static int32_t virtual_private_network_application_agent_func_on(virtual_private_network_application_agent_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    if(o->engine == nil) {
        o->engine = event_engine_gen();

        if(event_engine_on(o->engine) == fail) {
            snorlaxdbg(true, false, "critical", "");
        }

        o->netlink = event_engine_socket_sub(o->engine, (socket_t *) network_netlink_gen(NETLINK_GENERIC), virtual_private_network_agent_netlink_event_subscription_handler_get());
        o->tun = event_engine_descriptor_sub(o->engine, (descriptor_t *) network_tun_gen(), virtual_private_network_agent_tun_event_subscription_handler_get());
    }

    return success;
}

static int32_t virtual_private_network_application_agent_func_off(virtual_private_network_application_agent_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    if(o == nil) {
        if(o->engine) event_engine_off(o->engine, virtual_private_network_application_agent_event_engine_cancel);
    }

    return fail;
}

___implement static void virtual_private_network_application_agent_event_engine_cancel(___notnull const event_engine_t * engine) {
#ifndef   RELEASE
    snorlaxdbg(engine == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "must implement", "");
}

static int32_t virtual_private_network_application_agent_func_run(virtual_private_network_application_agent_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
    snorlaxdbg(o->engine == nil, false, "critical", "");
#endif // RELEASE

    return event_engine_run(o->engine);
}

extern void virtual_private_network_application_agent_interface_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response) {
    snorlaxdbg(false, true, "debug", "");

    if(state == network_netlink_request_state_done) {
        if(network_if_addr_get(application->ifname, address_of(application->InternetProtocolAddressVersion4), application->InternetProtocolAddressVersion6) == fail) {
            snorlaxdbg(false, true, "warning", "");
        }
    }
}

extern void virtual_private_network_application_agent_network_on(struct nlmsghdr * request, uint32_t state, struct nlmsghdr * response) {
    snorlaxdbg(false, true, "debug", "");

    /**
     * 모든 기능이 작동할 때 필요한 코드가 있으면 여기에 정의한다.
     */
}
