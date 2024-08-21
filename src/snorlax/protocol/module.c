#include "../protocol.h"

extern int32_t protocol_module_func_on(protocol_module_t * module, uint32_t type, protocol_context_t * parent, protocol_context_t * context) {
    return success;
}

extern int32_t protocol_module_func_serialize(protocol_module_t * module, protocol_context_t * parent, protocol_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == nil, false, "critical", "");
#endif // RELEASE
    if(context->packet == nil || context->packetlen == 0) {
        return fail;
    }

    if(*packet == nil) {
        *packet = (protocol_packet_t *) malloc(context->packetlen);
    } else if(*packetlen) {
        if(*packetlen < context->packetlen) {
            return fail;
        }
    }

    memcpy(*packet, context->packet, (*packetlen = context->packetlen));

    return success;
}

extern int32_t protocol_module_func_out(protocol_module_t * module, protocol_context_t * context, protocol_module_path_t * modulepath, uint64_t index) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    return fail;
}