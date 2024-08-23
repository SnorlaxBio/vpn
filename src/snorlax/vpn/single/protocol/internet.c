#include <errno.h>

#include <snorlax/descriptor/event/subscription.h>

#include "internet.h"

#include "../app.h"

static int32_t internet_protocol_module_func_vpn_single_on_in(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t internet_protocol_module_func_vpn_single_on_out(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t internet_protocol_module_func_vpn_single_on_exception(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t internet_protocol_module_func_vpn_single_on_complete(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t internet_protocol_module_func_vpn_single_on_complete_in(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t internet_protocol_module_func_vpn_single_on_complete_out(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);
static int32_t internet_protocol_module_func_vpn_single_on_complete_default(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context);

extern int32_t internet_protocol_module_func_vpn_single_on(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    switch(type) {
        case protocol_event_in:                     return internet_protocol_module_func_vpn_single_on_in(module, type, parent, context);
        case protocol_event_out:                    return internet_protocol_module_func_vpn_single_on_out(module, type, parent, context);
        case protocol_event_exception:              return internet_protocol_module_func_vpn_single_on_exception(module, type, parent, context);
        case protocol_event_complete:               return internet_protocol_module_func_vpn_single_on_complete(module, type, parent, context);
        case protocol_event_complete_in:            return internet_protocol_module_func_vpn_single_on_complete_in(module, type, parent, context);
        case protocol_event_complete_out:           return internet_protocol_module_func_vpn_single_on_complete_out(module, type, parent, context);
        default:                                    return internet_protocol_module_func_vpn_single_on_complete_default(module, type, parent, context);
    }

    return success;
}

static int32_t internet_protocol_module_func_vpn_single_on_in(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

static int32_t internet_protocol_module_func_vpn_single_on_out(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

static int32_t internet_protocol_module_func_vpn_single_on_exception(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");
    snorlaxdbg(false, true, "debug", "exception => %d", protocol_context_error_get(context));

    return success;
}

static int32_t internet_protocol_module_func_vpn_single_on_complete(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    return success;
}

static int32_t internet_protocol_module_func_vpn_single_on_complete_in(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE
    snorlaxdbg(false, true, "debug", "");

    return success;
}

static int32_t internet_protocol_module_func_vpn_single_on_complete_out(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    if(parent != nil) {
        /**
         * 상위 레이어로 전달하는 경로로 패킷을 전달한다.
         */
        return success;
    }

    vpn_single_app_t * single = vpn_single_app_get();

    snorlaxdbg(single == nil, false, "critical", "");

    descriptor_event_subscription_t * tun = single->tun;

    internet_protocol_module_debug(module, stdout, context);

    if(descriptor_event_subscription_write(tun, context->packet, context->packetlen) == fail) {
        internet_protocol_context_error_set(context, errno);
        return fail;
    }

    snorlaxdbg(false, true, "debug", "packet write => %lu", context->packetlen);

    return success;
}

static int32_t internet_protocol_module_func_vpn_single_on_complete_default(internet_protocol_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return fail;
}
