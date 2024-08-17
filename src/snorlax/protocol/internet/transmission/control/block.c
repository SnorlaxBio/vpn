#include <stdlib.h>
#include <string.h>

#include "../control.h"

static transmission_control_block_t * transmission_control_block_func_rem(transmission_control_block_t * block);
static int32_t transmission_control_block_func_open(transmission_control_block_t * block);
static int32_t transmission_control_block_func_send(transmission_control_block_t * block);
static int32_t transmission_control_block_func_recv(transmission_control_block_t * block);
static int32_t transmission_control_block_func_close(transmission_control_block_t * block);

static transmission_control_block_func_t func = {
    transmission_control_block_func_rem,
    transmission_control_block_func_open,
    transmission_control_block_func_send,
    transmission_control_block_func_recv,
    transmission_control_block_func_close
};

extern transmission_control_block_t * transmission_control_block_gen(transmission_control_protocol_address_pair_t * pair) {
    transmission_control_block_t * block = (transmission_control_block_t *) calloc(1, sizeof(transmission_control_block_t));

    block->func = address_of(func);
    
    snorlaxdbg(true, false, "implement", "");

    return block;
}

static transmission_control_block_t * transmission_control_block_func_rem(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    block->sync = sync_rem(block->sync);

    free(block);

    return nil;
}

static int32_t transmission_control_block_func_open(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    // block

    // PASSIVE OPEN: SERVER
    // ACTIVE OPEN: CLIENT
    // PASSIVE OPEN & ACTIVE OPEN

    snorlaxdbg(true, false, "implement", "");
    return fail;
}

static int32_t transmission_control_block_func_send(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");
    return fail;
}

static int32_t transmission_control_block_func_recv(transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "implement", "");
    return fail;
}

static int32_t transmission_control_block_func_close(transmission_control_block_t * block) {

}

// struct transmission_control_block {
//     transmission_control_block_func_t * func;
//     sync_t * sync;
//     transmission_control_address_t source;
//     transmission_control_address_t destination;
//     uint32_t state;
// };

// struct transmission_control_block_func {

// };

// #define transmission_control_state_none                             0
// #define transmission_control_state_listen                           1
// #define transmission_control_state_synchronize_sent                 2
// #define transmission_control_state_synchronize_received             3
// #define transmission_control_state_established                      4
// #define transmission_control_state_finish_wait_1                    5
// #define transmission_control_state_finish_wait_2                    6
// #define transmission_control_state_close_wait                       7
// #define transmission_control_state_closing                          8
// #define transmission_control_state_last_acknowledgment              9
// #define transmission_control_state_time_wait                        10
// #define transmission_control_state_closed                           0

// extern transmission_control_block_t * transmission_control_block_gen(void);

// #define transmission_control_block_rem(block)                       ((block)->func->rem(block))
// #define transmission_control_block_open(block)                      ((block)->func->open(block))
// #define transmission_control_block_send(block)                      ((block)->func->send(block))
// #define transmission_control_block_recv(block)                      ((block)->func->recv(block))
// #define transmission_control_block_close(block)                     ((block)->func->close(block))