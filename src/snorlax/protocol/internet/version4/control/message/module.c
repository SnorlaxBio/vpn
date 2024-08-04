#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../message.h"

static void internet_control_message_protocol_version4_module_func_destination_unreachable_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static void internet_control_message_protocol_version4_module_func_time_exceeded_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static void internet_control_message_protocol_version4_module_func_parameter_problem_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static void internet_control_message_protocol_version4_module_func_source_quench_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static void internet_control_message_protocol_version4_module_func_redirect_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static void internet_control_message_protocol_version4_module_func_echo_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static void internet_control_message_protocol_version4_module_func_timestamp_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);
static void internet_control_message_protocol_version4_module_func_information_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);

static internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4_module_func_rem(internet_control_message_protocol_version4_module_t * module);
static int32_t internet_control_message_protocol_version4_module_func_deserialize(internet_control_message_protocol_version4_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t ** context);
static int32_t internet_control_message_protocol_version4_module_func_serialize(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen);
static void internet_control_message_protocol_version4_module_func_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context);

static internet_control_message_protocol_version4_module_func_t func = {
    internet_control_message_protocol_version4_module_func_rem,
    internet_control_message_protocol_version4_module_func_deserialize,
    internet_control_message_protocol_version4_module_func_serialize,
    internet_control_message_protocol_version4_module_func_debug
};

extern internet_control_message_protocol_version4_module_t * internet_control_message_protocol_version4_module_gen(internet_protocol_version4_module_t * parent) {
    internet_control_message_protocol_version4_module_t * module = (internet_control_message_protocol_version4_module_t *) calloc(1, sizeof(internet_control_message_protocol_version4_module_t));

    module->func = address_of(func);
    module->parent = parent;

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

static int32_t internet_control_message_protocol_version4_module_func_deserialize(internet_control_message_protocol_version4_module_t * module, protocol_packet_t * packet, uint32_t packetlen, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "criticial", "");
    snorlaxdbg(packet == nil, false, "criticial", "");
    snorlaxdbg(packetlen == 0, false, "criticial", "");
    snorlaxdbg(parent == nil, false, "criticial", "");
    snorlaxdbg(context == nil, false, "criticial", "");
#endif // RELEASE

    if(*context == nil) *context = internet_control_message_protocol_version4_context_gen(parent, (internet_control_message_protocol_version4_packet_t *) packet, packetlen);

    if(packetlen < internet_control_message_protocol_version4_message_length_min) {
        internet_control_message_protocol_version4_context_error_set(*context, EAGAIN);
        return fail;
    }

    if(internet_control_message_protocol_version4_message_length_validate(internet_control_message_protocol_version4_context_type_get(*context), packetlen)) {
        internet_control_message_protocol_version4_context_error_set(*context, EAGAIN);
        return fail;
    }

    internet_control_message_protocol_version4_module_debug(module, stdout, *context);

    return success;
}

static int32_t internet_control_message_protocol_version4_module_func_serialize(internet_control_message_protocol_version4_module_t * module, internet_protocol_version4_context_t * parent, internet_control_message_protocol_version4_context_t * context, protocol_packet_t ** packet, uint32_t * packetlen) {
    snorlaxdbg(true, false, "implement", "");

    return fail;
}

static void internet_control_message_protocol_version4_module_func_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    switch(internet_control_message_protocol_version4_context_type_get(context)) {
        case internet_control_message_protocol_version4_message_type_echo_reply:                internet_control_message_protocol_version4_module_func_echo_message_debug(module, stream, context);                         break;           
        case internet_control_message_protocol_version4_message_type_destination_unreachable:   internet_control_message_protocol_version4_module_func_destination_unreachable_message_debug(module, stream, context);      break;
        case internet_control_message_protocol_version4_message_type_source_quench:             internet_control_message_protocol_version4_module_func_source_quench_message_debug(module, stream, context);                break;
        case internet_control_message_protocol_version4_message_type_redirect:                  internet_control_message_protocol_version4_module_func_redirect_message_debug(module, stream, context);                     break;
        case internet_control_message_protocol_version4_message_type_echo:                      internet_control_message_protocol_version4_module_func_echo_message_debug(module, stream, context);                         break;
        case internet_control_message_protocol_version4_message_type_time_exceeded:             internet_control_message_protocol_version4_module_func_time_exceeded_message_debug(module, stream, context);                break;
        case internet_control_message_protocol_version4_message_type_parameter_problem:         internet_control_message_protocol_version4_module_func_parameter_problem_message_debug(module, stream, context);            break;
        case internet_control_message_protocol_version4_message_type_timestamp:                 internet_control_message_protocol_version4_module_func_timestamp_message_debug(module, stream, context);                    break;
        case internet_control_message_protocol_version4_message_type_timestamp_reply:           internet_control_message_protocol_version4_module_func_timestamp_message_debug(module, stream, context);                    break;
        case internet_control_message_protocol_version4_message_type_information_request:       internet_control_message_protocol_version4_module_func_information_message_debug(module, stream, context);                  break;
        case internet_control_message_protocol_version4_message_type_information_reply:         internet_control_message_protocol_version4_module_func_information_message_debug(module, stream, context);                  break;
        default:                                                                                snorlaxdbg(true, false, "critical", "");                                                                                    break;
    }
}

static void internet_control_message_protocol_version4_module_func_destination_unreachable_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| destination unreachable message ");
    fprintf(stream, "| %d ", context->message.destination_unreachable->type);
    fprintf(stream, "| %d ", context->message.destination_unreachable->code);
    fprintf(stream, "| %d ", context->message.destination_unreachable->checksum);
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}

static void internet_control_message_protocol_version4_module_func_time_exceeded_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| time exceeded message ");
    fprintf(stream, "| %d ", context->message.time_exceeded->type);
    fprintf(stream, "| %d ", context->message.time_exceeded->code);
    fprintf(stream, "| %d ", context->message.time_exceeded->checksum);
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}

static void internet_control_message_protocol_version4_module_func_parameter_problem_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| time exceeded message ");
    fprintf(stream, "| %d ", context->message.parameter_problem->type);
    fprintf(stream, "| %d ", context->message.parameter_problem->code);
    fprintf(stream, "| %d ", context->message.parameter_problem->checksum);
    fprintf(stream, "| %d ", context->message.parameter_problem->pointer);
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}

static void internet_control_message_protocol_version4_module_func_source_quench_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| time exceeded message ");
    fprintf(stream, "| %d ", context->message.source_quench->type);
    fprintf(stream, "| %d ", context->message.source_quench->code);
    fprintf(stream, "| %d ", context->message.source_quench->checksum);
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}

static void internet_control_message_protocol_version4_module_func_redirect_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| time exceeded message ");
    fprintf(stream, "| %d ", context->message.redirect->type);
    fprintf(stream, "| %d ", context->message.redirect->code);
    fprintf(stream, "| %d ", context->message.redirect->checksum);
    fprintf(stream, "| %s ", inet_ntoa((struct in_addr) { .s_addr = context->message.redirect->gateway }));
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}

static void internet_control_message_protocol_version4_module_func_echo_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| time exceeded message ");
    fprintf(stream, "| %d ", context->message.echo->type);
    fprintf(stream, "| %d ", context->message.echo->code);
    fprintf(stream, "| %d ", context->message.echo->checksum);
    fprintf(stream, "| %d ", context->message.echo->identifier);
    fprintf(stream, "| %d ", context->message.echo->sequence);
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}

static void internet_control_message_protocol_version4_module_func_timestamp_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| time exceeded message ");
    fprintf(stream, "| %d ", context->message.timestamp->type);
    fprintf(stream, "| %d ", context->message.timestamp->code);
    fprintf(stream, "| %d ", context->message.timestamp->checksum);
    fprintf(stream, "| %d ", context->message.timestamp->identifier);
    fprintf(stream, "| %d ", context->message.timestamp->sequence);
    fprintf(stream, "| %d ", context->message.timestamp->timestamp.originate);
    fprintf(stream, "| %d ", context->message.timestamp->timestamp.receive);
    fprintf(stream, "| %d ", context->message.timestamp->timestamp.transmit);
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}

static void internet_control_message_protocol_version4_module_func_information_message_debug(internet_control_message_protocol_version4_module_t * module, FILE * stream, internet_control_message_protocol_version4_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(stream == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    fprintf(stream, "| internet control message protocol version 4");
    fprintf(stream, "| time exceeded message ");
    fprintf(stream, "| %d ", context->message.information->type);
    fprintf(stream, "| %d ", context->message.information->code);
    fprintf(stream, "| %d ", context->message.information->checksum);
    fprintf(stream, "| %d ", context->message.information->identifier);
    fprintf(stream, "| %d ", context->message.information->sequence);
    fprintf(stream, "|\n");

    // TODO: HEXADUMP + IP PACKET DEBUG
}