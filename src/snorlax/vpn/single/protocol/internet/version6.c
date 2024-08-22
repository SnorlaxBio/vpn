#include "version6.h"

extern int32_t internet_protocol_version6_module_func_vpn_single_on(internet_protocol_version6_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "type => %d", type);

    return internet_protocol_module_on(module->parent, type, parent, (internet_protocol_context_t *) context);
}