#include <stdlib.h>

#include "version4.h"



// static internet_protocol_version4_module_t * internet_protocol_version4_module_func_rem(internet_protocol_version4_module_t * module);
// static int32_t internet_protocol_version4_module_func_deserialize(internet_protocol_version4_module_t * module, protocol_message_t * message, uint32_t messagelen, internet_protocol_version4_context_t ** context);
// static int32_t internet_protocol_version4_module_func_serialize(internet_protocol_version4_module_t * module, internet_protocol_version4_context_t * context, protocol_message_t ** message, uint32_t * messagelen);

// static internet_protocol_version4_module_func_t func = {
//     internet_protocol_version4_module_func_rem,
//     internet_protocol_version4_module_func_deserialize,
//     internet_protocol_version4_module_func_serialize
// };

// extern internet_protocol_version4_module_t * internet_protocol_version4_module_gen(protocol_module_t * parent, protocol_module_t ** modules, uint64_t n, protocol_module_map_index_t index) {
//     internet_protocol_version4_module_t * module = (internet_protocol_version4_module_t *) calloc(1, sizeof(internet_protocol_version4_module_t));

//     module->func = address_of(func);
//     module->parent = parent;

//     if(modules != nil && n > 0 && index != nil) {
//         module->map = protocol_module_map_gen(modules, n, index);
//     }

//     return module;
// }

// static internet_protocol_version4_module_t * internet_protocol_version4_module_func_rem(internet_protocol_version4_module_t * module) {
// #ifndef   RELEASE
//     snorlaxdbg(module == nil, false, "critical", "");
// #endif // RELEASE

//     module->map = protocol_module_map_rem(module->map);

//     module->sync = sync_rem(module->sync);

//     free(module);

//     return nil;
// }

// static int32_t internet_protocol_version4_module_func_deserialize(internet_protocol_version4_module_t * module, protocol_message_t * message, uint32_t messagelen, internet_protocol_version4_context_t ** context) {
// #ifndef   RELEASE
//     snorlaxdbg(module == nil, false, "critical", "");
//     snorlaxdbg(message == nil, false, "critical", "");
//     snorlaxdbg(messagelen == 0, false, "critical", "");
//     snorlaxdbg(context == nil, false, "critical", "");
// #endif // RELEASE

//     if(messagelen < internet_protocol_version4_header_length_min) {
//         snorlaxdbg(false, true, "debug", "");
//         return fail;
//     }

//     if(*context == nil) *context = internet_protocol_version4_context_gen();
// }
