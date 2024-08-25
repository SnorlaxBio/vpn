#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#include <snorlax/event/engine.h>

#include "../../control.h"

static transmission_control_block_client_t * transmission_control_block_client_func_rem(transmission_control_block_client_t * agent);
static int32_t transmission_control_block_client_func_open(transmission_control_block_client_t * agent, socket_client_factory_t gen, event_engine_t * engine);

static transmission_control_block_client_func_t func = {
    transmission_control_block_client_func_rem,
    transmission_control_block_client_func_open,

};

/**
 * Construct transmission control block client object.
 * 
 * @param in block  transmission_control_block_t *, not null : control block
 * @param in on     transmission_control_block_client_handler_t : control block event handler
 * 
 * @return transmission_control_block_client_t * : transmission control block client object
 */
extern transmission_control_block_client_t * transmission_control_block_client_gen(___notnull transmission_control_block_t * block, transmission_control_block_client_handler_t on) {
#ifndef   RELEASE
    snorlaxdbg(block == nil, false, "critical", "");
#endif // RELEASE

    transmission_control_block_client_t * agent = (transmission_control_block_client_t *) calloc(1, sizeof(transmission_control_block_client_t));

    agent->func = address_of(func);
    agent->block = block;
    agent->on = on;

    return agent;
}

static transmission_control_block_client_t * transmission_control_block_client_func_rem(transmission_control_block_client_t * agent) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
#endif // RELEASE

    agent->subscription = socket_client_event_subscription_rem(agent->subscription);

    agent->sync = sync_rem(agent->sync);

    free(agent);

    return nil;
}

static int32_t transmission_control_block_client_func_open(transmission_control_block_client_t * agent, socket_client_factory_t gen, event_engine_t * engine) {
#ifndef   RELEASE
    snorlaxdbg(agent == nil, false, "critical", "");
    snorlaxdbg(agent->block == nil, false, "critical", "");
    snorlaxdbg(agent->block->module == nil, false, "critical", "");
    snorlaxdbg(gen == nil, false, "critical", "");
    snorlaxdbg(engine == nil, false, "critical", "");
#endif // RELEASE

    if(agent->subscription = nil) {
        socket_client_t * descriptor = nil;

        protocol_path_node_t * node = protocol_path_begin(agent->block->path);
        protocol_path_node_t * next = protocol_path_node_next(node);

        if(agent->block->version == 4) {
            struct sockaddr_in addr;

            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = uint32_of(protocol_path_node_source_get(next));
            addr.sin_port = uint16_of(protocol_path_node_source_get(node));

            descriptor = gen(AF_INET, SOCK_STREAM, IPPROTO_TCP, address_of(addr), sizeof(struct sockaddr_in));
        } else if(agent->block->version == 6) {
            struct sockaddr_in6 addr;

            addr.sin6_flowinfo = 0;
            addr.sin6_scope_id = 0;
            addr.sin6_family = AF_INET6;
            memcpy(addr.sin6_addr.s6_addr, protocol_path_node_source_get(next), 16);
            addr.sin6_port = uint16_of(protocol_path_node_source_get(node));

            descriptor = gen(AF_INET6, SOCK_STREAM, IPPROTO_TCP, address_of(addr), sizeof(struct sockaddr_in6));
        }

        snorlaxdbg(descriptor == nil, false, "critical", "");

        agent->subscription = event_engine_socket_client_sub(engine, descriptor, transmission_control_block_client_handler_get(), agent->block->module->client.pool, agent);

        return success;
    }

    snorlaxdbg(false, true, "warning", "");

    return success;
}

// struct transmission_control_block_client {
//     transmission_control_block_client_func_t * func;
//     sync_t * sync;
//     ___reference transmission_control_block_t * block;
//     socket_client_t * socket;
//     socket_client_event_subscription_t * subscription;
// };

// struct transmission_control_block_client_func {
//     transmission_control_block_client_t * (*rem)(transmission_control_block_client_t *);

//     int32_t (*open)(transmission_control_block_client_t *);
//     int64_t (*send)(transmission_control_block_client_t *);
//     int64_t (*recv)(transmission_control_block_client_t *);
//     int32_t (*close)(transmission_control_block_client_t *);
//     int32_t (*shutdown)(transmission_control_block_client_t *, uint32_t);

//     int32_t (*in)(transmission_control_block_client_t *, transmission_control_protocol_context_t *);
//     int32_t (*out)(transmission_control_block_client_t *);
// };

// extern transmission_control_block_client_t * transmission_control_block_client_gen(___notnull transmission_control_block_t * block, socket_client_event_subscription_handler_t * handler);
