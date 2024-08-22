#include <string.h>
#include <errno.h>

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

    snorlaxdbg(true, false, "implement", "recursive module on");

    protocol_context_t * context = protocol_module_context_gen(module, node, child);

    if(context == nil) {
        snorlaxdbg(protocol_context_error_get(child) == 0, false, "critical", "");
        return fail;
    } else {
        if(protocol_module_on(child->module, protocol_event_out, context, child) == fail) {
            protocol_context_error_set(context, ECHILD);
            protocol_module_propagate_on(module, protocol_event_exception, nil, context);
            context = protocol_context_rem(context);
            return success;
        }
    }

    protocol_path_node_t * next = protocol_path_node_next(node);

    if(next != protocol_path_end(node->path)) {
        if(protocol_module_out(next->module, next, context) == fail) {
            snorlaxdbg(protocol_context_error_get(context) == 0, false, "critical", "");
            protocol_module_propagate_on(module, protocol_event_exception, nil, context);
            context = protocol_context_rem(context);
        }
        return success;
    }

    protocol_module_propagate_on(module, protocol_event_complete_out, nil, context);

    return success;
}

extern protocol_context_t * protocol_module_func_reply_gen(protocol_module_t * module, protocol_context_t * request) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(request == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "critical", "");

    return nil;
}

extern int32_t protocol_module_func_propagate_on(protocol_module_t * module, uint32_t type, protocol_context_t * parent, protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    int error = 0;

    if(protocol_module_on(module, type, parent, context) == fail) {
        snorlaxdbg(protocol_context_error_get(context) == 0, false, "critical", "");
        if(type != protocol_event_exception) {
            type = protocol_event_exception;
            error = protocol_context_error_get(context);
            protocol_module_on(module, type, parent, context);
        }
    }

    uint64_t n = protocol_context_array_size(context->children);

    for(uint64_t i = 0; i < n; i++) {
        if(type == protocol_event_exception && protocol_context_error_get(context) == 0) {
            protocol_context_error_set(context, error);
        }
        protocol_context_t * child = protocol_context_array_get(context->children, i);
        protocol_module_propagate_on(child->module, type, child->parent, child);
    }

    return success;
}
