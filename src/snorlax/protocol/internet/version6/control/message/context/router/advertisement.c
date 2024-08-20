#include "../../../message.h"

static internet_control_message_protocol_version6_context_router_advertisement_t * internet_control_message_protocol_version6_context_router_advertisement_func_rem(internet_control_message_protocol_version6_context_router_advertisement_t * context);
static int32_t internet_control_message_protocol_version6_context_router_advertisement_func_valid(internet_control_message_protocol_version6_context_router_advertisement_t * context);
typedef uint8_t * (*internet_control_message_protocol_version6_context_router_advertisement_func_addrptr_t)(internet_control_message_protocol_version6_context_router_advertisement_t *, uint32_t);

static internet_control_message_protocol_version6_context_router_advertisement_func_t func = {
    internet_control_message_protocol_version6_context_router_advertisement_func_rem,
    internet_control_message_protocol_version6_context_router_advertisement_func_valid,
    (internet_control_message_protocol_version6_context_router_advertisement_func_addrptr_t) protocol_context_func_addrptr
};

extern internet_control_message_protocol_version6_context_router_advertisement_t * internet_control_message_protocol_version6_context_router_advertisement_gen(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_router_advertisement_t * packet, uint64_t packetlen) {
    internet_control_message_protocol_version6_context_router_advertisement_t * context = (internet_control_message_protocol_version6_context_router_advertisement_t *) calloc(1, sizeof(internet_control_message_protocol_version6_context_router_advertisement_t));

    context->func = address_of(func);
    context->module = module;
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static internet_control_message_protocol_version6_context_router_advertisement_t * internet_control_message_protocol_version6_context_router_advertisement_func_rem(internet_control_message_protocol_version6_context_router_advertisement_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_control_message_protocol_version6_context_router_advertisement_func_valid(internet_control_message_protocol_version6_context_router_advertisement_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(internet_protocol_version6_context_hop_limit_get(context->parent) != 255) {
        /**
         * The Internet Protocol <sup>IP</sup> Hop Limit field has a value of 255,
         * i.e., the packet could not possibly have been forwarded by a router.
         */
        return false;
    }

    if(!internet_control_message_protocol_version6_context_router_advertisement_checksum_valid(context)) {
        /**
         * Internet Control Message Protocl <sup>ICMP</sup> Checksum is valid.
         */
        return false;
    }

    if(internet_control_message_protocol_version6_context_router_advertisement_code_get(context) != 0) {
        /**
         * Internet Control Message Protocol <sup>ICMP</sup> Code is 0.
         */
        return false;
    }

    if(internet_control_message_protocol_version6_context_router_advertisement_length(context) <= 16) {
        /**
         * Internet Control Message Protocol <sup>ICMP</sup> length is 8 or more octets.
         */
        return false;
    }

    snorlaxdbg(false, true, "implement", "All included options have a length that is greater than zero.");
    snorlaxdbg(false, true, "implement", "Internet Protocol <sup>IP</sup> Source Address is a link local address. Routers must use their link local address as the source for Router Advertisement and Redirect messages so that hosts can uniquely identify routers.");

    return true;
}
