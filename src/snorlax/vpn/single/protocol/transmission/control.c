#include "control.h"

extern int32_t transmission_control_protocol_module_func_vpn_single_on(transmission_control_protocol_module_t * module, uint32_t type, internet_protocol_context_t * parent, transmission_control_protocol_context_t * context) {
    snorlaxdbg(false, true, "debug", "");
    if(transmission_control_protocol_context_key_has(context)) {
        if(transmission_control_protocol_module_blockon(module, type, parent, context) == fail) {
            snorlaxdbg(false, true, "warning", "");
        }
    }
    

    // transmission_control_protocol_module_func_blockon()
    // transmission_control_block_t * block = hashtable_get(module->map, transmission_control_protocol_context_key_get(context));

    return success;
}