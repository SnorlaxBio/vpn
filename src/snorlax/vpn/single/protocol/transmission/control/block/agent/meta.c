#include "../../../control.h"

static transmission_control_block_agent_single_meta_t * transmission_control_block_agent_single_meta_func_rem(transmission_control_block_agent_single_meta_t * meta);

static transmission_control_block_agent_single_meta_func_t func = {
    transmission_control_block_agent_single_meta_func_rem
};

extern transmission_control_block_agent_single_meta_t * transmission_control_block_agent_single_meta_gen(transmission_control_block_t * block) {
    transmission_control_block_agent_single_meta_t * meta = (transmission_control_block_agent_single_meta_t *) calloc(1, sizeof(transmission_control_block_agent_single_meta_t));

    meta->func = address_of(func);
    meta->block = block;

    return meta;
}

static transmission_control_block_agent_single_meta_t * transmission_control_block_agent_single_meta_func_rem(transmission_control_block_agent_single_meta_t * meta) {
#ifndef   RELEASE
    snorlaxdbg(meta == nil, false, "critical", "");
#endif // RELEASE

    meta->sync = sync_rem(meta->sync);

    free(meta);

    return nil;
}
