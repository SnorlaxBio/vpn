#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

#include "../version4.h"

static internet_protocol_version4_context_t * internet_protocol_version4_context_func_rem(internet_protocol_version4_context_t * context);
static int32_t internet_protocol_version4_context_func_valid(internet_protocol_version4_context_t * context);
static uint8_t * internet_protocol_version4_context_func_addrptr(internet_protocol_version4_context_t * context, uint32_t type);
static void internet_protocol_version4_context_func_build(internet_protocol_version4_context_t * context, const uint8_t * pseudo, uint64_t pseudolen);

static internet_protocol_version4_context_func_t func = {
    internet_protocol_version4_context_func_rem,
    internet_protocol_version4_context_func_valid,
    internet_protocol_version4_context_func_addrptr,
    internet_protocol_version4_context_func_build
};

extern internet_protocol_version4_context_t * internet_protocol_version4_context_gen(internet_protocol_version4_module_t * module, protocol_context_t * parent, internet_protocol_version4_packet_t * datagram, uint64_t datagramlen, uint64_t * bufferlen) {
    internet_protocol_version4_context_t * context = (internet_protocol_version4_context_t *) calloc(1, sizeof(internet_protocol_version4_context_t));

    context->func = address_of(func);
    context->module = module;
    context->children = protocol_context_array_gen();
    context->parent = parent;
    context->packet = datagram;
    context->packetlen = datagramlen;
    context->bufferlen = bufferlen;

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

    if(internet_protocol_version4_context_error_get(context)) {
        snorlaxdbg(false, true, "debug", "error => %d\n", internet_protocol_version4_context_error_get(context));
        return false;
    }

    snorlaxdbg(false, true, "debug", "checksum => %u", internet_protocol_version4_context_checksum_get(context));
    snorlaxdbg(false, true, "debug", "checksumcal => %u", internet_protocol_version4_context_checksumcal_get(context));

    if(internet_protocol_version4_context_checksum_get(context) != internet_protocol_version4_context_checksumcal_get(context)) {    
        internet_protocol_version4_context_error_set(context, EIO);
        return false;
    }

    return true;
}

static uint8_t * internet_protocol_version4_context_func_addrptr(internet_protocol_version4_context_t * context, uint32_t type) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(type == protocol_address_type_source) {
        return (uint8_t *) address_of(context->packet->source);
    } else if(type == protocol_address_type_destination) {
        return (uint8_t *) address_of(context->packet->destination);
    }

    return nil;
}

static void internet_protocol_version4_context_func_build(internet_protocol_version4_context_t * context, const uint8_t * pseudo, uint64_t pseudolen) {
#ifndef   RELEASE
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(pseudo != nil, false, "critical", "");
    snorlaxdbg(pseudolen != 0, false, "critical", "");
#endif // RELEASE

    internet_protocol_version4_context_checksumcal_set(context, internet_protocol_version4_context_checksum_cal(context));
    internet_protocol_version4_context_checksum_set(context, internet_protocol_version4_context_checksumcal_get(context));
}