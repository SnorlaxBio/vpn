#include "../../../message.h"

static internet_control_message_protocol_version6_context_router_solicitation_t * internet_control_message_protocol_version6_context_router_solicitation_func_rem(internet_control_message_protocol_version6_context_router_solicitation_t * context);
static int32_t internet_control_message_protocol_version6_context_router_solicitation_func_valid(internet_control_message_protocol_version6_context_router_solicitation_t * context);

static internet_control_message_protocol_version6_context_router_solicitation_func_t func = {
    internet_control_message_protocol_version6_context_router_solicitation_func_rem,
    internet_control_message_protocol_version6_context_router_solicitation_func_valid
};

extern internet_control_message_protocol_version6_context_router_solicitation_t * internet_control_message_protocol_version6_context_router_solicitation_gen(internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_router_solicitation_t * packet, uint64_t packetlen) {
    internet_control_message_protocol_version6_context_router_solicitation_t * context = (internet_control_message_protocol_version6_context_router_solicitation_t *) calloc(1, sizeof(internet_control_message_protocol_version6_context_router_solicitation_t));

    context->func = address_of(func);
    context->parent = parent;
    context->packet = packet;
    context->packetlen = packetlen;

    return context;
}

static internet_control_message_protocol_version6_context_router_solicitation_t * internet_control_message_protocol_version6_context_router_solicitation_func_rem(internet_control_message_protocol_version6_context_router_solicitation_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_control_message_protocol_version6_context_router_solicitation_func_valid(internet_control_message_protocol_version6_context_router_solicitation_t * context) {
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

    if(!internet_control_message_protocol_context_router_solicitation_checksum_valid(context)) {
        /**
         * Internet Control Message Protocl <sup>ICMP</sup> Checksum is valid.
         */
        return false;
    }

    if(internet_control_message_protocol_version6_context_router_solicitation_code_get(context) != 0) {
        /**
         * Internet Control Message Protocol <sup>ICMP</sup> Code is 0.
         */
        return false;
    }

    if(internet_control_message_protocol_version6_context_router_solicitation_length(context) < 8) {
        /**
         * Internet Control Message Protocol <sup>ICMP</sup> length is 8 or more octets.
         */
        return false;
    }

    snorlaxdbg(false, true, "implement", "All included options have a length that is greater than zero.");
    snorlaxdbg(false, true, "implement", "If the Internet Protocol <sup>IP</sup> source address is the unspecified address, there is no source link layer address option in the message.");

    return true;
}