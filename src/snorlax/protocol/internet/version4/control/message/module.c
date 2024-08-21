#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../message.h"

static internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4_module_func_rem(internet_control_message_protocol_version4_module_t * module);
static int32_t internet_control_message_protocol_version4_module_func_deserialize(internet_control_message_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t ** context);
static int32_t internet_control_message_protocol_version4_module_func_serialize(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void internet_control_message_protocol_version4_module_func_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static int32_t internet_control_message_protocol_version4_module_func_in(internet_control_message_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t ** context);
static int32_t internet_control_message_protocol_version4_module_func_out(internet_control_message_protocol_version4_module_t * module, internet_control_message_protocol_version4_context_t * context, protocol_path_node_t * node);

static internet_control_message_protocol_version4_module_func_t func = {
    internet_control_message_protocol_version4_module_func_rem,
    internet_control_message_protocol_version4_module_func_deserialize,
    internet_control_message_protocol_version4_module_func_serialize,
    internet_control_message_protocol_version4_module_func_debug,
    internet_control_message_protocol_version4_module_func_in,
    internet_control_message_protocol_version4_module_func_out
};

extern internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4_module_gen(internet_control_message_protocol_version4_context_handler_t on) {
    internet_control_message_protocol_version4_module_t * module = (internet_control_message_protocol_version4_module_t *) calloc(1, sizeof(internet_control_message_protocol_version4_module_t));

    module->func = address_of(func);
    module->on = on;

    return module;
}

static internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4_module_func_rem(internet_control_message_protocol_version4_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t internet_control_message_protocol_version4_module_func_deserialize(internet_control_message_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(packet == nil, false, "criticial", "");
    snorlaxdbg(parent == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    if(*context == nil) *context = internet_control_message_protocol_version4_context_gen(module, parent, (internet_control_message_protocol_version4_packet_t *) packet, packetlen);

    if(packetlen < internet_control_message_protocol_version4_length_min) {
        internet_control_message_protocol_version4_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_control_message_protocol_version4_module_debug(module, stdout, *context);

    return internet_control_message_protocol_version4_context_valid(*context) ? success : fail;
}

static int32_t internet_control_message_protocol_version4_module_func_serialize(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static void internet_control_message_protocol_version4_module_func_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| destination unreachable message ");
    fprintf(stream, "| %d ", context->message->type);
    fprintf(stream, "| %d ", context->message->code);
    fprintf(stream, "| %d ", context->message->checksum);
    fprintf(stream, "|\n");
}

static int32_t internet_control_message_protocol_version4_module_func_in(internet_control_message_protocol_version4_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(packet == nil, false, "criticial", "");
    snorlaxdbg(packetlen == 0, false, "criticial", "");
    snorlaxdbg(parent == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    if(*context == nil) *context = internet_control_message_protocol_version4_context_gen(module, parent, (internet_control_message_protocol_version4_packet_t *) packet, packetlen);

    if(internet_control_message_protocol_version4_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        internet_control_message_protocol_version4_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    if(internet_control_message_protocol_version4_module_on(module, protocol_event_in, parent, *context) == fail) {
        internet_control_message_protocol_version4_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    internet_control_message_protocol_version4_module_on(module, protocol_event_complete_in, parent, *context);

    return success;
}

extern int32_t internet_control_message_protocol_version4_module_func_on(internet_control_message_protocol_version4_module_t * module, uint32_t type, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t * context) {
    snorlaxdbg(false, true, "implement", "");

    return success;
}

static int32_t internet_control_message_protocol_version4_module_func_out(internet_control_message_protocol_version4_module_t * module, internet_control_message_protocol_version4_context_t * context, protocol_path_node_t * node) {
    snorlaxdbg(true, false, "critical", "");
}
