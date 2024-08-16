#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

#include "../version4.h"

static internet_protocol_version4_context_t * internet_protocol_version4_context_func_rem(internet_protocol_version4_context_t * context);
static int32_t internet_protocol_version4_context_func_valid(internet_protocol_version4_context_t * context);

static internet_protocol_version4_context_func_t func = {
    internet_protocol_version4_context_func_rem,
    internet_protocol_version4_context_func_valid
};

extern internet_protocol_version4_context_t * internet_protocol_version4_context_gen(internet_protocol_version4_module_t * module, protocol_context_t * parent, internet_protocol_version4_packet_t * datagram, uint64_t datagramlen) {
    internet_protocol_version4_context_t * context = (internet_protocol_version4_context_t *) calloc(1, sizeof(internet_protocol_version4_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->datagram = datagram;
    context->datagramlen = datagramlen;

    return context;
}

static internet_protocol_version4_context_t * internet_protocol_version4_context_func_rem(internet_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(context->children) context->children = protocol_context_array_rem(context->children);
    
    context->pseudo = memory_rem(context->pseudo);

    context->sync = sync_rem(context->sync);

    free(context);

    return nil;
}

static int32_t internet_protocol_version4_context_func_valid(internet_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(internet_protocol_version4_context_error_get(context)) return false;

    if(internet_protocol_version4_context_checksum_get(context) != internet_protocol_version4_context_checksumcal_get(context)) {
        snorlaxdbg(false, true, "debug", "checksum => %u", internet_protocol_version4_context_checksum_get(context));
        snorlaxdbg(false, true, "debug", "checksumcal => %u", internet_protocol_version4_context_checksumcal_get(context));
        
        internet_protocol_version4_context_error_set(context, EIO);

        return false;
    }

    return true;
}