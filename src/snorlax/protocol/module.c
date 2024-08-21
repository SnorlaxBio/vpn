#include <string.h>

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

extern int32_t protocol_module_func_out(protocol_module_t * module, protocol_path_node_t * node, protocol_context_t * child) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(node == nil, false, "critical", "");
    snorlaxdbg(child == nil, false, "critical", "");
#endif // RELEASE

    protocol_context_t * context = protocol_module_context_gen(module, node, child);

    if(context == nil) {
        snorlaxdbg(false, true, "debug", "context == nil");
        child = protocol_context_rem(child);
        return fail;
    }

    if(protocol_module_on(module, protocol_event_out, nil, context) == fail) {
        snorlaxdbg(false, true, "exception", "error => %d", protocol_context_error_get(context));
        protocol_module_on(module, protocol_event_exception_out, nil, context);
        context = protocol_context_rem(context);
        return fail;
    }

    protocol_path_node_t * next = protocol_path_node_next(node);

    if(next != node->path->end) {
        if(protocol_module_on(module, protocol_event_complete_out, nil, context) == fail) {
            snorlaxdbg(false, true, "exception", "error => %d", protocol_context_error_get(context));
            protocol_module_on(module, protocol_event_exception_out, nil, context);
            context = protocol_context_rem(context);
            return fail;
        }
        
        return protocol_module_out(next->module, next, context);
    }

    if(protocol_module_on(module, protocol_event_complete_out, nil, context) == fail) {
        snorlaxdbg(false, true, "exception", "error => %d", protocol_context_error_get(context));
        protocol_module_on(module, protocol_event_exception_out, nil, context);
        context = protocol_context_rem(context);
        return fail;
    }

    context = protocol_context_rem(context);

    return success;
}

extern protocol_context_t * protocol_module_func_reply_gen(protocol_module_t * module, protocol_context_t * request) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(request == nil, false, "critical", "");
#endif // RELEASE

    return nil;
}
