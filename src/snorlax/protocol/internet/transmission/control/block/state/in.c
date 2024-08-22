#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#include "../../../control.h"

extern int32_t transmission_control_block_state_listen_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_synchronize_sequence_sent_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_synchronize_sequence_recv_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(transmission_control_protocol_context_flags_get(context) == transmission_control_flag_control_syn) {
        if(transmission_control_block_acknowledge_get(block) != transmission_control_protocol_context_sequence_get(context) + 1) {
            snorlaxdbg(true, false, "check", "");
            transmission_control_protocol_context_error_set(context, EIO);

            return fail;
        }

        return success;
    } else if(transmission_control_protocol_context_flags_get(context) == transmission_control_flag_control_ack) {
        if((transmission_control_block_sequence_get(block) + 1 != transmission_control_protocol_context_acknowledge_get(context)) || transmission_control_block_acknowledge_get(block) != transmission_control_protocol_context_sequence_get(context)) {
            snorlaxdbg(true, false, "check", "implement connection close");
            transmission_control_protocol_context_error_set(context, EIO);

            return fail;
        }

        transmission_control_block_state_set(block, transmission_control_state_establish);
        transmission_control_block_sequence_set(block, transmission_control_protocol_context_acknowledge_get(context));

        return success;
    } else {
        snorlaxdbg(true, false, "check", "");
    }

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_establish_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_cwr)) {
        snorlaxdbg(true, false, "implement", "");
    }
    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_ece)) {
        snorlaxdbg(true, false, "implement", "");
    }
    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_urg)) {
        snorlaxdbg(true, false, "implement", "");
    }
    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_ack)) {
        transmission_control_block_sequence_set(block, transmission_control_protocol_context_acknowledge_get(context));
    }
    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_psh)) {
        snorlaxdbg(false, true, "debug", "data => %p", transmission_control_protocol_context_data_get(context));
        snorlaxdbg(false, true, "debug", "datalen => %u", transmission_control_protocol_context_datalen_get(context));

        snorlaxdbg(block->agent == nil, false, "critical", "");

        if(transmission_control_block_recv(block, context) == fail) {
            return fail;
        }
    }
    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_rst)) {
        snorlaxdbg(true, false, "implement", "");
    }
    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_syn)) {
        snorlaxdbg(true, false, "implement", "");
    }
    if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_fin)) {
        snorlaxdbg(true, false, "implement", "");
    }

    return fail;
}

extern int32_t transmission_control_block_state_finish_wait_frist_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_finish_wait_second_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_close_wait_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_closing_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_last_acknowledge_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_time_wait_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_closed_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}

extern int32_t transmission_control_block_state_exception_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");

    return fail;
}