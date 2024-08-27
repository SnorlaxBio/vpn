// #include <stdlib.h>
// #include <string.h>
// #include <arpa/inet.h>
// #include <errno.h>

// #include "../../../../control.h"

// extern int32_t transmission_control_block_state_listen_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_synchronize_sequence_sent_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_synchronize_sequence_recv_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     char buffer[protocol_packet_max];
//     transmission_control_protocol_context_t * response = transmission_control_block_context_gen_connect_synack(context->block, buffer + protocol_packet_max, protocol_packet_max);

//     // TODO: MACRO 혹은 함수로 빼자.
//     if(response) {
//         transmission_control_protocol_module_debug(block->module, stdout, response);

//         protocol_path_node_t * parent = protocol_path_node_next(protocol_path_begin(context->block->path));

//         snorlaxdbg(parent == nil, false, "critical", "");

//         if(protocol_module_out(parent->module, parent, (protocol_context_t *) response) == fail) {
//             snorlaxdbg(false, true, "debug", "fail to protocol_module_out(...)");
//         }

//         return success;
//     }

//     transmission_control_protocol_context_error_set(context, EINVAL);

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_establish_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     if(transmission_control_block_state_get(block) != transmission_control_protocol_context_state_get(context)) {
//         snorlaxdbg(false, true, "debug", "state is changed, send message check and send");
//     }

//     return success;
// }

// extern int32_t transmission_control_block_state_finish_wait_frist_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_finish_wait_second_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_close_wait_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_closing_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_last_acknowledge_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_time_wait_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_closed_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

// extern int32_t transmission_control_block_state_exception_complete_in(transmission_control_block_t * block, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
// #ifndef   RELEASE
//     snorlaxdbg(block == nil, false, "critical", "");
//     snorlaxdbg(parent == nil, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     snorlaxdbg(true, false, "implement", "");

//     return fail;
// }

