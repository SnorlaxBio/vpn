#include "../../control.h"

extern int32_t transmission_control_block_event_in_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_protocol_context_state_set(context, transmission_control_block_state_get(block));

    switch(transmission_control_block_state_get(block)) {
        case transmission_control_state_listen:                         return transmission_control_block_state_listen_in(block, parent, context);
        case transmission_control_state_synchronize_sequence_sent:      return transmission_control_block_state_synchronize_sequence_sent_in(block, parent, context);
        case transmission_control_state_synchronize_sequence_recv:      return transmission_control_block_state_synchronize_sequence_recv_in(block, parent, context);
        case transmission_control_state_establish:                      return transmission_control_block_state_establish_in(block, parent, context);
        case transmission_control_state_finish_wait_first:              return transmission_control_block_state_finish_wait_frist_in(block, parent, context);
        case transmission_control_state_finish_wait_second:             return transmission_control_block_state_finish_wait_second_in(block, parent, context);
        case transmission_control_state_close_wait:                     return transmission_control_block_state_close_wait_in(block, parent, context);
        case transmission_control_state_closing:                        return transmission_control_block_state_closing_in(block, parent, context);
        case transmission_control_state_last_acknowledge:               return transmission_control_block_state_last_acknowledge_in(block, parent, context);
        case transmission_control_state_time_wait:                      return transmission_control_block_state_time_wait_in(block, parent, context);
        case transmission_control_state_closed:                         return transmission_control_block_state_closed_in(block, parent, context);
        default:                                                        return transmission_control_block_state_exception_in(block, parent, context);
    }
}

extern int32_t transmission_control_block_event_out_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return success;
}

extern int32_t transmission_control_block_event_exception_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return success;
}

extern int32_t transmission_control_block_event_complete_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return success;
}

extern int32_t transmission_control_block_event_complete_in_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    switch(transmission_control_block_state_get(block)) {
        case transmission_control_state_listen:                         return transmission_control_block_state_listen_complete_in(block, parent, context);
        case transmission_control_state_synchronize_sequence_sent:      return transmission_control_block_state_synchronize_sequence_sent_complete_in(block, parent, context);
        case transmission_control_state_synchronize_sequence_recv:      return transmission_control_block_state_synchronize_sequence_recv_complete_in(block, parent, context);
        case transmission_control_state_establish:                      return transmission_control_block_state_establish_complete_in(block, parent, context);
        case transmission_control_state_finish_wait_first:              return transmission_control_block_state_finish_wait_frist_complete_in(block, parent, context);
        case transmission_control_state_finish_wait_second:             return transmission_control_block_state_finish_wait_second_complete_in(block, parent, context);
        case transmission_control_state_close_wait:                     return transmission_control_block_state_close_wait_complete_in(block, parent, context);
        case transmission_control_state_closing:                        return transmission_control_block_state_closing_complete_in(block, parent, context);
        case transmission_control_state_last_acknowledge:               return transmission_control_block_state_last_acknowledge_complete_in(block, parent, context);
        case transmission_control_state_time_wait:                      return transmission_control_block_state_time_wait_complete_in(block, parent, context);
        case transmission_control_state_closed:                         return transmission_control_block_state_closed_complete_in(block, parent, context);
        default:                                                        return transmission_control_block_state_exception_complete_in(block, parent, context);
    }
}

extern int32_t transmission_control_block_event_complete_out_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return success;
}

extern int32_t transmission_control_block_event_none_on(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(parent == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "implement", "");

    return success;
}
