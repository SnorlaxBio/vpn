#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../message.h"

static internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6_module_func_rem(internet_control_message_protocol_version6_module_t * module);
static int32_t internet_control_message_protocol_version6_module_func_deserialize(internet_control_message_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t ** context);
static int32_t internet_control_message_protocol_version6_module_func_serialize(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen);
static void internet_control_message_protocol_version6_module_func_debug(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context);
static int32_t internet_control_message_protocol_version6_module_func_in(internet_control_message_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t ** context);

static void internet_control_message_protocol_version6_module_func_debug_destination_unreachable_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_destination_unreachable_t * context);
static void internet_control_message_protocol_version6_module_func_debug_packet_too_big_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_packet_too_big_t * context);
static void internet_control_message_protocol_version6_module_func_debug_time_exceeded_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_time_exceeded_t * context);
static void internet_control_message_protocol_version6_module_func_debug_parameter_problem_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_parameter_problem_t * context);
static void internet_control_message_protocol_version6_module_func_debug_echo_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_echo_t * context);
static void internet_control_message_protocol_version6_module_func_debug_router_solicitation_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_router_solicitation_t * context);
static void internet_control_message_protocol_version6_module_func_debug_router_advertisement_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_router_advertisement_t * context);
static void internet_control_message_protocol_version6_module_func_debug_neighbor_solicitation_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_neighbor_solicitation_t * context);

static internet_control_message_protocol_version6_module_func_t func = {
    internet_control_message_protocol_version6_module_func_rem,
    internet_control_message_protocol_version6_module_func_deserialize,
    internet_control_message_protocol_version6_module_func_serialize,
    internet_control_message_protocol_version6_module_func_debug,
    internet_control_message_protocol_version6_module_func_in
};

extern internet_control_message_protocol_version6_module_t * internet_control_message_protocol_version6_module_gen(internet_control_message_protocol_version6_context_handler_t on) {
    internet_control_message_protocol_version6_module_t * module = (internet_control_message_protocol_version6_module_t *) calloc(1, sizeof(internet_control_message_protocol_version6_module_t));

    module->func = address_of(func);
    module->on = on;

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

static int32_t internet_control_message_protocol_version6_module_func_deserialize(internet_control_message_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_control_message_protocol_version6_context_gen(parent, (internet_control_message_protocol_version6_packet_t * ) packet, packetlen);

    if(packetlen < internet_control_message_protocol_version6_message_length_min) {
        internet_control_message_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    if(internet_control_message_protocol_version6_length_validate(internet_control_message_protocol_version6_context_type_get(*context), packetlen) == false) {
        internet_control_message_protocol_version6_context_error_set(*context, EAGAIN);
        return fail;
    }

    // TODO: CALCULATE LENGTH

    internet_control_message_protocol_version6_module_debug(module, stdout, *context);

    switch(internet_control_message_protocol_version6_context_type_get(*context)) {
        case internet_control_message_protocol_version6_message_type_router_solicitation:   snorlaxdbg(false, true, "debug", "discard");    break;
        default:                                                                            snorlaxdbg(false, true, "implement", "");       break;
    }

    return success;
}

static int32_t internet_control_message_protocol_version6_module_func_serialize(internet_control_message_protocol_version6_module_t * module, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t * context, protocol_packet_t ** packet, uint64_t * packetlen) {
    snorlaxdbg(false, true, "implement", "");

    return fail;
}

static void internet_control_message_protocol_version6_module_func_debug(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_t * context) {
    switch(internet_control_message_protocol_version6_context_type_get(context)) {
        case internet_control_message_protocol_version6_message_type_destination_unreachable:   internet_control_message_protocol_version6_module_func_debug_destination_unreachable_message(module, stream, (internet_control_message_protocol_version6_context_destination_unreachable_t *) context);     break;
        case internet_control_message_protocol_version6_message_type_packet_too_big:            internet_control_message_protocol_version6_module_func_debug_packet_too_big_message(module, stream, (internet_control_message_protocol_version6_context_packet_too_big_t *) context);                       break;
        case internet_control_message_protocol_version6_message_type_time_exceeded:             internet_control_message_protocol_version6_module_func_debug_time_exceeded_message(module, stream, (internet_control_message_protocol_version6_context_time_exceeded_t *) context);                         break;
        case internet_control_message_protocol_version6_message_type_parameter_problem:         internet_control_message_protocol_version6_module_func_debug_parameter_problem_message(module, stream, (internet_control_message_protocol_version6_context_parameter_problem_t *) context);                 break;
        case internet_control_message_protocol_version6_message_type_echo_request:              internet_control_message_protocol_version6_module_func_debug_echo_message(module, stream, (internet_control_message_protocol_version6_context_echo_t *) context);                                           break;
        case internet_control_message_protocol_version6_message_type_echo_reply:                internet_control_message_protocol_version6_module_func_debug_echo_message(module, stream, (internet_control_message_protocol_version6_context_echo_t *) context);                                           break;
        case internet_control_message_protocol_version6_message_type_router_solicitation:       internet_control_message_protocol_version6_module_func_debug_router_solicitation_message(module, stream, (internet_control_message_protocol_version6_context_router_solicitation_t *) context);             break;
        case internet_control_message_protocol_version6_message_type_router_advertisement:      internet_control_message_protocol_version6_module_func_debug_router_advertisement_message(module, stream, (internet_control_message_protocol_version6_context_router_advertisement_t *) context);           break;
        case internet_control_message_protocol_version6_message_type_neighbor_solicitation:     internet_control_message_protocol_version6_module_func_debug_neighbor_solicitation_message(module, stream, (internet_control_message_protocol_version6_context_neighbor_solicitation_t *) context);         break;
        default:                                                                                snorlaxdbg(true, false, "critical", "");                                                                                                                                                                    break;
    }
}

static void internet_control_message_protocol_version6_module_func_debug_destination_unreachable_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_destination_unreachable_t * context) {
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

static void internet_control_message_protocol_version6_module_func_debug_packet_too_big_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_packet_too_big_t * context) {
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

static void internet_control_message_protocol_version6_module_func_debug_time_exceeded_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_time_exceeded_t * context) {
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

static void internet_control_message_protocol_version6_module_func_debug_parameter_problem_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_parameter_problem_t * context) {
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

static void internet_control_message_protocol_version6_module_func_debug_echo_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_echo_t * context) {
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

static void internet_control_message_protocol_version6_module_func_debug_router_solicitation_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_router_solicitation_t * context) {
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

static void internet_control_message_protocol_version6_module_func_debug_router_advertisement_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_router_advertisement_t * context) {
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

static void internet_control_message_protocol_version6_module_func_debug_neighbor_solicitation_message(internet_control_message_protocol_version6_module_t * module, FILE * stream, internet_control_message_protocol_version6_context_neighbor_solicitation_t * context) {
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

static int32_t internet_control_message_protocol_version6_module_func_in(internet_control_message_protocol_version6_module_t * module, protocol_packet_t * packet, uint64_t packetlen, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t ** context) {
#ifndef   RELEASE
    snorlaxdbg(module == nil, false, "critical", "");
    snorlaxdbg(packet == nil, false, "critical", "");
    snorlaxdbg(packetlen == 0, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(*context == nil) *context = internet_control_message_protocol_version6_context_gen(parent, (internet_control_message_protocol_version6_packet_t * ) packet, packetlen);

    if(internet_control_message_protocol_version6_module_deserialize(module, packet, packetlen, parent, context) == fail) {
        internet_control_message_protocol_version6_module_on(module, protocol_event_exception, parent, *context);
        return fail;
    }

    return internet_control_message_protocol_version6_module_on(module, protocol_event_in, parent, *context);
}

extern int32_t internet_control_message_protocol_version6_module_func_on(internet_control_message_protocol_version6_module_t * module, uint32_t type, internet_protocol_version6_context_t * parent, internet_control_message_protocol_version6_context_t * context) {
    return success;
}
