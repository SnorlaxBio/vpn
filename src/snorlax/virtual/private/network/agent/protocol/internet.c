#include <errno.h>

#include "internet.h"

#include "../application.h"

static int32_t virtual_private_network_agent_internet_protocol_on_event_in(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t virtual_private_network_agent_internet_protocol_on_event_out(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t virtual_private_network_agent_internet_protocol_on_event_exception(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t virtual_private_network_agent_internet_protocol_on_event_complete(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t virtual_private_network_agent_internet_protocol_on_event_complete_in(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t virtual_private_network_agent_internet_protocol_on_event_complete_out(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t virtual_private_network_agent_internet_protocol_on_event_none(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context);

extern int32_t virtual_private_network_agent_internet_protocol_on(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");
    switch(type) {
        case protocol_event_in:             return virtual_private_network_agent_internet_protocol_on_event_in(module, parent, context);
        case protocol_event_out:            return virtual_private_network_agent_internet_protocol_on_event_out(module, parent, context);
        case protocol_event_exception:      return virtual_private_network_agent_internet_protocol_on_event_exception(module, parent, context);
        case protocol_event_complete:       return virtual_private_network_agent_internet_protocol_on_event_complete(module, parent, context);
        case protocol_event_complete_in:    return virtual_private_network_agent_internet_protocol_on_event_complete_in(module, parent, context);
        case protocol_event_complete_out:   return virtual_private_network_agent_internet_protocol_on_event_complete_out(module, parent, context);
        default:                            return virtual_private_network_agent_internet_protocol_on_event_none(module, parent, context);
    }

    return fail;
}

static int32_t virtual_private_network_agent_internet_protocol_on_event_in(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

static int32_t virtual_private_network_agent_internet_protocol_on_event_out(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

static int32_t virtual_private_network_agent_internet_protocol_on_event_exception(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "warning", "exception => %d", protocol_context_error_get(context));

    return success;
}

static int32_t virtual_private_network_agent_internet_protocol_on_event_complete(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

static int32_t virtual_private_network_agent_internet_protocol_on_event_complete_in(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

/**
 * 상위 레이어가 없을 경우 이 곳에서 데이터 전달이 이루어진다.
 */
static int32_t virtual_private_network_agent_internet_protocol_on_event_complete_out(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    if(parent != nil) {
        return success;
    }

    virtual_private_network_application_agent_t * application = virtual_private_network_application_agent_get();
    descriptor_event_subscription_t * tun = application->tun;

    internet_protocol_module_debug(module, stdout, context);

    if(descriptor_event_subscription_write(tun, context->packet, context->packetlen) == fail) {
        internet_protocol_context_error_set(context, errno);
        return fail;
    }

    snorlaxdbg(false, true, "debug", "packet write => %lu", context->packetlen);

    return success;
}

/**
 * 
 */
static int32_t virtual_private_network_agent_internet_protocol_on_event_none(internet_protocol_module_t * module, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "critical", "");

    return fail;
}