#include "control.h"

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_exception(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);
static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_none(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context);

extern int32_t virtual_private_network_agent_transmission_control_protocol_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    switch(type) {
        case protocol_event_in:             return virtual_private_network_agent_transmission_control_protocol_on_event_in(module, type, parent, context);
        case protocol_event_out:            return virtual_private_network_agent_transmission_control_protocol_on_event_out(module, type, parent, context);
        case protocol_event_exception:      return virtual_private_network_agent_transmission_control_protocol_on_event_exception(module, type, parent, context);
        case protocol_event_complete:       return virtual_private_network_agent_transmission_control_protocol_on_event_complete(module, type, parent, context);
        case protocol_event_complete_in:    return virtual_private_network_agent_transmission_control_protocol_on_event_complete_in(module, type, parent, context);
        case protocol_event_complete_out:   return virtual_private_network_agent_transmission_control_protocol_on_event_complete_out(module, type, parent, context);
        default:                            return virtual_private_network_agent_transmission_control_protocol_on_event_none(module, type, parent, context);
    }
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_exception(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_in(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_complete_out(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static int32_t virtual_private_network_agent_transmission_control_protocol_on_event_none(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}
