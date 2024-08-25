#include "version6.h"

extern int32_t virtual_private_network_agent_internet_protocol_version6_on(internet_protocol_version6_module_t * module, uint32_t type, protocol_context_t * parent, internet_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return internet_protocol_module_on(module->parent, type, parent, (internet_protocol_context_t *) context);
}
