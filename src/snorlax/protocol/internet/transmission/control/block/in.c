#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../../control.h"

extern int32_t transmission_control_block_in_closed(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
    snorlaxdbg(transmission_control_protocol_context_is_connect_syn(context) == false, false, "critical", "");
#endif // RELEASE

    transmission_control_block_state_prev_set(block, transmission_control_block_state_get(block));

    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_cwr)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_cwr), false, "critical", "");
    // }
    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_ece)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_ece), false, "critical", "");
    // }
    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_urg)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_urg), false, "critical", "");
    // }
    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_ack)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_ack), false, "critical", "");
    // }
    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_psh)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_psh), false, "critical", "");
    // }
    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_rst)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_rst), false, "critical", "");
    // }
    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_fin)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_fin), false, "critical", "");
    // }

    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_syn)) {
    //     transmission_control_block_remote_sequence_set(block, transmission_control_protocol_context_sequence_get(context));
    // }

    transmission_control_block_state_set(block, transmission_control_state_synchronize_sequence_recv);

    transmission_control_block_remote_sequence_set(block, transmission_control_protocol_context_sequence_get(context));

    transmission_control_block_version_set(block, internet_protocol_context_version_get(context->parent));
    transmission_control_block_sequence_set(block, transmission_control_protocol_module_seqeuence_gen(context->module, context->parent, context));
    transmission_control_block_remote_window_set(block, transmission_control_protocol_context_window_get(context));

    snorlaxdbg(transmission_control_protocol_context_datalen_get(context) > 0, false, "check", "");

    return success;
}

extern int32_t transmission_control_block_in_listen(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_synchronize_sequence_sent(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_synchronize_sequence_recv(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_establish(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_finish_wait_first(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_finish_wait_second(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_close_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_closing(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_last_acknowledge(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_time_wait(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_in_exception(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}
