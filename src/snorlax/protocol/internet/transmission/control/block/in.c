#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#include "../../control.h"

#define transmission_control_block_in_closed_flags_must                 (transmission_control_flag_control_syn)
#define transmission_control_block_in_closed_flags_allow                (transmission_control_flag_control_syn)
#define transmission_control_block_in_closed_flags_disallow             (transmission_control_flag_control_ack | transmission_control_flag_control_rst | transmission_control_flag_control_fin)
#define transmission_control_block_in_closed_flags_check                (transmission_control_flag_control_cwr | transmission_control_flag_control_ece | transmission_control_flag_control_urg | transmission_control_flag_control_psh)

extern int32_t transmission_control_block_in_closed(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
    snorlaxdbg(context == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(transmission_control_protocol_context_flags_get(context) & transmission_control_block_in_closed_flags_disallow, false, "disallow", "");
    snorlaxdbg(transmission_control_protocol_context_flags_get(context) & transmission_control_block_in_closed_flags_check, false, "check", "");
    snorlaxdbg((transmission_control_protocol_context_flags_get(context) & transmission_control_block_in_closed_flags_must) == 0, false, "must", "");

    snorlaxdbg(transmission_control_protocol_context_datalen_get(context) > 0, false, "check", "");
    snorlaxdbg(transmission_control_protocol_context_acknowledge_get(context) != 0, false, "exception", "");

    if((transmission_control_protocol_context_flags_get(context) & transmission_control_block_in_closed_flags_must) == transmission_control_block_in_closed_flags_must) {
        transmission_control_block_state_prev_set(block, transmission_control_block_state_get(block));

        snorlaxdbg(block->buffer.in  != nil, false, "critical", "");
        snorlaxdbg(block->buffer.out != nil, false, "critical", "");

        block->buffer.in  = transmission_control_buffer_gen(transmission_control_buffer_in_gen, block->module);
        block->buffer.out = transmission_control_buffer_gen(transmission_control_buffer_out_gen, block->module);

        /**
         * @see     [RFC9293 / 3.1. Header Format](https://github.com/SnorlaxBio/dev/blob/main/RFC/RFC9293/FunctionalSpecification.md#31-header-format)
         * @see     [RFC7323 / 2. TCP Window Scale Option](https://github.com/SnorlaxBio/dev/blob/main/RFC/RFC7323/TCPWindowScaleOption.md)
         */
        for(transmission_control_protocol_option_t * option = transmission_control_protocol_context_option_begin(context); !transmission_control_protocol_context_option_end(context, option); option = transmission_control_protocol_context_option_next(option)) {
            switch(*option) {
                case transmission_control_protocol_option_type_maximum_segment_size:    transmission_control_block_remote_maximum_segment_set(block, uint16_of((option + 2)));      break;
                case transmission_control_protocol_option_type_no_operation:                                                                                                        break;
                case transmission_control_protocol_option_type_window_scale:            transmission_control_block_remote_window_scale_set(block, uint8_of((option + 2)));          break;
                default:                                                                snorlaxdbg(false, true, "check", "");                                                       break;
            }
        }

        snorlaxdbg(false, transmission_control_block_remote_maximum_segment_get(block) == 0, "critical", "");

        /**
         * Upon receiving a SYN segment with a Window Scale option containing `shift.cnt = S`, a TCP must set `Snd.Wind.Shift` to `S` and must sete `Rcv.Wind.Shift` to `R`;
         * otherwise, it must set both `Snd.Wind.Shift` and `Rcv.Wind.Shift` to zero.
         * 
         * @see     [2.3. Using the Window Scale Option](https://github.com/SnorlaxBio/dev/blob/main/RFC/RFC7323/TCPWindowScaleOption.md#23-using-the-window-scale-option)
         */
        transmission_control_block_window_set(block, transmission_control_protocol_module_window_get(block->module));
        if(transmission_control_block_remote_window_scale_get(block) > 0) {
            transmission_control_block_window_scale_set(block, transmission_control_protocol_module_scale_get(block->module));
        }
        transmission_control_block_sequence_set(block, transmission_control_protocol_module_func_sequence_gen(block->module, context->parent, context));
        transmission_control_block_acknowledge_set(block, transmission_control_protocol_context_sequence_get(context) + 1);

        transmission_control_block_remote_sequence_set(block, transmission_control_protocol_context_sequence_get(context));
        transmission_control_block_remote_acknowledge_set(block, transmission_control_protocol_context_acknowledge_get(context));
        transmission_control_block_remote_window_set(block, transmission_control_protocol_context_window_get(context));
        
        transmission_control_block_state_set(block, transmission_control_state_synchronize_sequence_recv);

        return success;
    }

    snorlaxdbg(true, false, "critical", "error handling");

    return fail;
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


// #define transmission_control_flag_control_cwr                       (0x01u << 7u)
// #define transmission_control_flag_control_ece                       (0x01u << 6u)
// #define transmission_control_flag_control_urg                       (0x01u << 5u)
// #define transmission_control_flag_control_ack                       (0x01u << 4u)
// #define transmission_control_flag_control_psh                       (0x01u << 3u)
// #define transmission_control_flag_control_rst                       (0x01u << 2u)
// #define transmission_control_flag_control_syn                       (0x01u << 1u)
// #define transmission_control_flag_control_fin                       (0x01u << 0u)

#define transmission_control_block_in_synchronize_sequence_recv_flags_must          (0)
#define transmission_control_block_in_synchronize_sequence_recv_flags_duplicate     (transmission_control_flag_control_syn)
#define transmission_control_block_in_synchronize_sequence_recv_flags_finish        (transmission_control_flag_control_rst | transmission_control_flag_control_fin)
#define transmission_control_block_in_synchronize_sequence_recv_flags_allow         (transmission_control_flag_control_ack | transmission_control_block_in_synchronize_sequence_recv_flags_finish | transmission_control_block_in_synchronize_sequence_recv_flags_duplicate)
#define transmission_control_block_in_synchronize_sequence_recv_flags_disallow      (0)
#define transmission_control_block_in_synchronize_sequence_recv_flags_check         (transmission_control_flag_control_cwr | transmission_control_flag_control_ece | transmission_control_flag_control_urg | transmission_control_flag_control_psh)

extern int32_t transmission_control_block_in_synchronize_sequence_recv(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    // AVAILABLE STATE CHECK ... FIN WAIT, CLOSED, CLOSING, ... ETC ...

    uint8_t flags = transmission_control_protocol_context_flags_get(context);

    if(flags & transmission_control_block_in_synchronize_sequence_recv_flags_allow) {
        transmission_control_block_state_prev_set(block, transmission_control_block_state_get(block));

        snorlaxdbg((flags & transmission_control_block_in_synchronize_sequence_recv_flags_check), false, "check", "");

        if(flags & transmission_control_block_in_synchronize_sequence_recv_flags_finish) {
            snorlaxdbg(true, false, "implement", "do finish");
            return success;
        }

        if(flags & transmission_control_block_in_synchronize_sequence_recv_flags_duplicate) {
            snorlaxdbg(true, false, "implement", "retransmission, packet drop or close to invalid");
            return success;
        }

        if(flags & transmission_control_flag_control_ack) {
            uint32_t len = transmission_control_protocol_context_acknowledge_get(context) - transmission_control_block_sequence_get(block);

            snorlaxdbg(false, true, "implement", "synack 에서 데이터를 보냈다면, len >= 1 보다 크다.");

            if(len == 1) {
                transmission_control_block_remote_acknowledge_set(block, transmission_control_protocol_context_acknowledge_get(context));
                transmission_control_block_sequence_set(block, transmission_control_protocol_context_acknowledge_get(context));
            } else {
                snorlaxdbg(true, false, "implement or error handling", "");
            }

            snorlaxdbg(transmission_control_protocol_context_sequence_get(context) != transmission_control_block_acknowledge_get(block), false, "implement or error handling", "");

            transmission_control_block_state_set(block, transmission_control_state_establish);

            return success;
        }
    }

    snorlaxdbg(true, false, "critical", "");

    return fail;
}

// #define transmission_control_flag_control_cwr                       (0x01u << 7u)
// #define transmission_control_flag_control_ece                       (0x01u << 6u)
// #define transmission_control_flag_control_urg                       (0x01u << 5u)
// #define transmission_control_flag_control_ack                       (0x01u << 4u)
// #define transmission_control_flag_control_psh                       (0x01u << 3u)
// #define transmission_control_flag_control_rst                       (0x01u << 2u)
// #define transmission_control_flag_control_syn                       (0x01u << 1u)
// #define transmission_control_flag_control_fin                       (0x01u << 0u)

#define transmission_control_block_in_establish_flags_must              (0)
#define transmission_control_block_in_establish_flags_duplicate         (0)
#define transmission_control_block_in_establish_flags_finish            (transmission_control_flag_control_rst | transmission_control_flag_control_fin)
#define transmission_control_block_in_establish_flags_allow             (0xFF)
#define transmission_control_block_in_establish_flags_disallow          (transmission_control_flag_control_syn)
#define transmission_control_block_in_establish_flags_check             (transmission_control_flag_control_cwr | transmission_control_flag_control_ece | transmission_control_flag_control_urg | transmission_control_flag_control_psh)

extern int32_t transmission_control_block_in_establish(transmission_control_block_t * block, transmission_control_protocol_context_t * context) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    // ALL ALLOW ...

    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_ack)) {
    //     /**
    //      * TODO: transmission_control_block_remote_acknowledge_update
    //      * 
    //      * 오버플로우에 조심해서 개발하자.
    //      */
    //     if(transmission_control_block_remote_acknowledge_update(block, transmission_control_protocol_context_acknowledge_get(context))) {
    //         transmission_control_block_buffer_out_erase(block->buffer.out, transmission_control_block_remote_acknowledge_get(block));
    //         /**
    //          * SYN 은 어떻게 풀어야 할까? 여기서 업데이트 하는 것이 맞을까?
    //          */
    //         transmission_control_block_sequence_set(block, transmission_control_block_remote_acknowledge_get(block));

    //     }
    // }

    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_syn)) {
    //     snorlaxdbg(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_syn), false, "implement", "");
    //     if(transmission_control_block_remote_sequence_update(block, transmission_control_block_remote_sequence_get(block))) {

    //     }
        
    // }

    // if(transmission_control_protocol_context_flags_has(context, transmission_control_flag_control_psh)) {
    //     // UPDATE MY BUFFER ... 
    // }

    // snorlaxdbg(true, false, "implement", "");

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
