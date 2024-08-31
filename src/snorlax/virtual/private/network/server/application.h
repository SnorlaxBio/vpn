/**
 * @file        snorlax/virtual/private/network/server/application.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 24, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SERVER_APPLICATION__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SERVER_APPLICATION__H__

#include <snorlax/virtual/private/network/application.h>
#include <snorlax/socket/server/event/subscription.h>
#include <snorlax/event/engine.h>

struct virtual_private_network_application_server;
struct virtual_private_network_application_server_func;

typedef struct virtual_private_network_application_server           virtual_private_network_application_server_t;
typedef struct virtual_private_network_application_server_func      virtual_private_network_application_server_func_t;

struct virtual_private_network_application_server {
    virtual_private_network_application_server_func_t * func;
    sync_t * sync;
    virtual_private_network_application_config_t * config;

    event_engine_t * engine;

    socket_server_event_subscription_t * subscription;
};

struct virtual_private_network_application_server_func {
    virtual_private_network_application_server_t * (*rem)(virtual_private_network_application_server_t *);
    int32_t (*on)(virtual_private_network_application_server_t *);
    int32_t (*off)(virtual_private_network_application_server_t *);
    int32_t (*run)(virtual_private_network_application_server_t *);
};

#define virtual_private_network_application_server_rem(application)     ((application)->func->rem(application))
#define virtual_private_network_application_server_on(application)      ((application)->func->on(application))
#define virtual_private_network_application_server_off(application)     ((application)->func->off(application))
#define virtual_private_network_application_server_run(application)     ((application)->func->run(application))

extern virtual_private_network_application_server_t * virtual_private_network_application_server_get(void);
extern network_tun_t * virtual_private_network_application_server_tun_get(virtual_private_network_application_server_t * application);

struct virtual_private_network_application_config {
    uint16_t port;
};

#define virtual_private_network_application_server_socket_get(application)      ((virtual_private_network_server_socket_t *)(((virtual_private_network_application_server_t *) (application))->subscription->descriptor))

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_SERVER_APPLICATION__H__
