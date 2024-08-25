#include "control.h"
#include "control/block.h"

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_exception(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_none(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

extern int32_t virtual_private_network_agent_transmission_control_protocol_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    switch(type) {
        case protocol_event_in:             return virtual_private_network_agent_transmission_control_protocol_on_event_in(module, parent, context);
        case protocol_event_out:            return virtual_private_network_agent_transmission_control_protocol_on_event_out(module, parent, context);
        case protocol_event_exception:      return virtual_private_network_agent_transmission_control_protocol_on_event_exception(module, parent, context);
        case protocol_event_complete:       return virtual_private_network_agent_transmission_control_protocol_on_event_complete(module, parent, context);
        case protocol_event_complete_in:    return virtual_private_network_agent_transmission_control_protocol_on_event_complete_in(module, parent, context);
        case protocol_event_complete_out:   return virtual_private_network_agent_transmission_control_protocol_on_event_complete_out(module, parent, context);
        default:                            return virtual_private_network_agent_transmission_control_protocol_on_event_none(module, parent, context);
    }
}

/**
 * TCP 패킷이 분석되어지는 부분이다.
 */
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    snorlaxdbg(context->block == nil, false, "critical", "");

    return context->block ? virtual_private_network_agent_transmission_control_protocol_block_on_event_in(module, parent, context, context->block) : success;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return context->block ? virtual_private_network_agent_transmission_control_protocol_block_on_event_out(module, parent, context, context->block) : success;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_exception(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return context->block ? virtual_private_network_agent_transmission_control_protocol_block_on_event_exception(module, parent, context, context->block) : success;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return context->block ? virtual_private_network_agent_transmission_control_protocol_block_on_event_complete(module, parent, context, context->block) : success;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return context->block ? virtual_private_network_agent_transmission_control_protocol_block_on_event_complete_in(module, parent, context, context->block) : success;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return context->block ? virtual_private_network_agent_transmission_control_protocol_block_on_event_complete_out(module, parent, context, context->block) : success;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_none(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "critical", "");

    return context->block ? virtual_private_network_agent_transmission_control_protocol_block_on_event_none(module, parent, context, context->block) : success;
}
