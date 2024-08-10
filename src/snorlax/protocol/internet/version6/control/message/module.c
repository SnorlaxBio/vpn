#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../message.h"

static internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6_module_func_rem(internet_control_message_protocol_version6_module_t * module);
static int32_t internet_control_message_protocol_version6_module_func_deserialize(internet_control_message_protocol_version6_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t ** context);
static int32_t internet_control_message_protocol_version6_module_func_serialize(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen);
static void internet_control_message_protocol_version6_module_func_debug(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context);

static void internet_control_message_protocol_version6_module_func_debug_destination_unreachable_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context);
static void internet_control_message_protocol_version6_module_func_debug_packet_too_big_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context);
static void internet_control_message_protocol_version6_module_func_debug_time_exceeded_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context);
static void internet_control_message_protocol_version6_module_func_debug_parameter_problem_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context);
static void internet_control_message_protocol_version6_module_func_debug_echo_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context);

static internet_control_message_protocol_version6_module_func_t func = {
    internet_control_message_protocol_version6_module_func_rem,
    internet_control_message_protocol_version6_module_func_deserialize,
    internet_control_message_protocol_version6_module_func_serialize,
    internet_control_message_protocol_version6_module_func_debug
};

extern internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6_module_gen(internet_protocol_version6_module_t * parent) {
    internet_control_message_protocol_version6_module_t * module = (internet_control_message_protocol_version6_module_t *) calloc(1, sizeof(internet_control_message_protocol_version6_module_t));

    module->func = address_of(func);
    module->parent = parent;

    return module;
}

static internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6_module_func_rem(internet_control_message_protocol_version6_module_t * module) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
#endif // RELEASE

    module->sync = sync_rem(module->sync);

    free(module);

    return nil;
}

static int32_t internet_control_message_protocol_version6_module_func_deserialize(internet_control_message_protocol_version6_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context) *context = internet_control_message_protocol_version6_context_gen(parent, (internet_control_message_protocol_version6_packet_t * ) packet, packetlen);

    if(packetlen < internet_control_message_protocol_version6_message_length_min) {
        internet_control_message_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    if(internet_control_message_protocol_version6_message_length_validate(internet_control_message_protocol_version6_context_type_get(*context), packetlen) == false) {
        internet_control_message_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_control_message_protocol_version6_module_debug(module, stdout, *context);

    return success;
}

static int32_t internet_control_message_protocol_version6_module_func_serialize(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen) {
    snorlaxdbg(false, true, "implement", "");

    return fail;
}

static void internet_control_message_protocol_version6_module_func_debug(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context) {
    switch(internet_control_message_protocol_version6_context_type_get(context)) {
        case internet_control_message_protocol_version6_message_type_destination_unreachable:   internet_control_message_protocol_version6_module_func_debug_destination_unreachable_message(module, stream, context);  break;
        case internet_control_message_protocol_version6_message_type_packet_too_big:            internet_control_message_protocol_version6_module_func_debug_packet_too_big_message(module, stream, context);           break;
        case internet_control_message_protocol_version6_message_type_time_exceeded:             internet_control_message_protocol_version6_module_func_debug_time_exceeded_message(module, stream, context);            break;
        case internet_control_message_protocol_version6_message_type_parameter_problem:         internet_control_message_protocol_version6_module_func_debug_parameter_problem_message(module, stream, context);        break;
        case internet_control_message_protocol_version6_message_type_echo_request:              internet_control_message_protocol_version6_module_func_debug_echo_message(module, stream, context);                     break;
        case internet_control_message_protocol_version6_message_type_echo_reply:                internet_control_message_protocol_version6_module_func_debug_echo_message(module, stream, context);                     break;
        default:                                                                                snorlaxdbg(true, false, "critical", "");                                                                                break;
    }
}

static void internet_control_message_protocol_version6_module_func_debug_destination_unreachable_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(stream == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 6 ");
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_type_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_code_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_checksum_get(context));
    fprintf(stream, "|\n");
}

static void internet_control_message_protocol_version6_module_func_debug_packet_too_big_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(stream == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 6 ");
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_type_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_code_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_checksum_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_maximum_transmission_unit_get(context));
    fprintf(stream, "|\n");
}

static void internet_control_message_protocol_version6_module_func_debug_time_exceeded_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(stream == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 6 ");
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_type_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_code_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_checksum_get(context));
    fprintf(stream, "|\n");
}

static void internet_control_message_protocol_version6_module_func_debug_parameter_problem_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(stream == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 6 ");
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_type_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_code_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_checksum_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_pointer_get(context));
    fprintf(stream, "|\n");
}

static void internet_control_message_protocol_version6_module_func_debug_echo_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(stream == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 6 ");
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_type_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_code_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_checksum_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_identifier_get(context));
    fprintf(stream, "| %d ", internet_control_message_protocol_version6_context_sequence_get(context));
    fprintf(stream, "|\n");
}
