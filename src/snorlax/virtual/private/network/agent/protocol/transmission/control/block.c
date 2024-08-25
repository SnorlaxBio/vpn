#include <errno.h>

#include "block.h"

#include "../../../application.h"

#include "../../../../socket/client.h"

#include "../../../transmission/control/block/client.h"

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    if(transmission_control_block_state_is_changed(block)) {
        if(transmission_control_block_state_get(block) == transmission_control_state_synchronize_sequence_recv) {
            snorlaxdbg(block->agent != nil, false, "critical", "");

            virtual_private_network_application_agent_t * application = virtual_private_network_application_agent_get();

            transmission_control_block_client_t * agent = transmission_control_block_client_gen(block, virtual_private_network_agent_transmission_control_block_client_on);

            transmission_control_block_agent_set(block, (transmission_control_block_agent_t *) agent);

            if(transmission_control_block_client_open(agent, virutal_private_network_socket_client_factory, application->engine) == fail) {
                transmission_control_protocol_context_error_set(context, EIO);
                return fail;
            }

            return success;
        }
    }

    return success;
}

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_exception(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_complete(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_complete_in(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    // if(transmission_control_block_state_is_changed(block)) {
    //     if(transmission_control_block_state_get(block) == transmission_control_state_synchronize_sequence_recv) {
    //         // transmission_control_block

    //         // send packet exist ...

    //         snorlaxdbg(true, false, "implement", "create connect synack in internal");
    //     }
    // } else if(transmission_control_block_state_get(block) == transmission_control_state_establish) {
    //     snorlaxdbg(false, true, "implement", "");
    // } else {
    //     snorlaxdbg(false, true, "implement", "");
    // }

    return success;
}

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_complete_out(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return success;
}

extern int32_t virtual_private_network_agent_transmission_control_protocol_block_on_event_none(transmission_control_protocol_module_t * module, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context, transmission_control_block_t * block) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(true, false, "critical", "");

    return fail;
}