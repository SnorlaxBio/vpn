/**
 * @file        snorlax/vpn/server/app.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_SERVER_APP__H__
#define   __SNORLAX__VPN_SERVER_APP__H__

#include <snorlax.h>
#include <snorlax/socket/server.h>
#include <snorlax/socket/server/event/subscription.h>
#include <snorlax/event/engine.h>

struct vpn_server_app;
struct vpn_server_app_func;

typedef struct vpn_server_app vpn_server_app_t;
typedef struct vpn_server_app_func vpn_server_app_func_t;

struct vpn_server_app {
    vpn_server_app_func_t * func;
    sync_t * sync;

    event_engine_t * engine;
    
    socket_server_event_subscription_t * server;
};

struct vpn_server_app_func {
    vpn_server_app_t * (*rem)(vpn_server_app_t *);
    int32_t (*on)(vpn_server_app_t *);
    int32_t (*off)(vpn_server_app_t *);
    int32_t (*run)(vpn_server_app_t *);
};

extern vpn_server_app_t * vpn_server_app_gen(void);

#define vpn_server_app_rem(app)         ((app)->func->rem(app))
#define vpn_server_app_on(app)          ((app)->func->on(app))
#define vpn_server_app_off(app)         ((app)->func->off(app))
#define vpn_server_app_run(app)         ((app)->func->run(app))

#endif // __SNORLAX__VPN_SERVER_APP__H__
