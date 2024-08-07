/**
 * @file        snorlax/vpn/client/app.h
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       July 19, 2024
 */

#ifndef   __SNORLAX__VPN_CLIENT_APP__H__
#define   __SNORLAX__VPN_CLIENT_APP__H__

#include <snorlax.h>
#include <snorlax/event/engine.h>
#include <snorlax/socket/client/event/subscription/pool.h>

#include <snorlax/protocol/internet.h>
#include <snorlax/protocol/internet/version4.h>
#include <snorlax/protocol/internet/version6.h>

struct vpn_client_app;
struct vpn_client_app_func;

typedef struct vpn_client_app vpn_client_app_t;
typedef struct vpn_client_app_func vpn_client_app_func_t;

typedef void (vpn_client_app_cancel_t)(vpn_client_app_t *);

struct vpn_client_app {
    vpn_client_app_func_t * func;
    sync_t * sync;
    event_engine_t * engine;

    struct {
        struct {
            internet_protocol_version4_module_t * version4;
            internet_protocol_version6_module_t * version6;
        } internet;
    } protocol;

    descriptor_event_subscription_t * tun;
    socket_event_subscription_t * netlink;
    socket_client_event_subscription_pool_t * pool;
};

struct vpn_client_app_func {
    vpn_client_app_t * (*rem)(vpn_client_app_t *);
    int32_t (*on)(vpn_client_app_t *);
    int32_t (*off)(vpn_client_app_t *);
    int32_t (*run)(vpn_client_app_t *);
};

extern vpn_client_app_t * vpn_client_app_gen(void);

#define vpn_client_app_rem(app)     ((app)->func->rem(app))
#define vpn_client_app_on(app)      ((app)->func->on(app))
#define vpn_client_app_off(app)     ((app)->func->off(app))
#define vpn_client_app_run(app)     ((app)->func->run(app))

extern void vpn_client_app_engine_cancel(___notnull const event_engine_t * engine);

extern network_netlink_t * vpn_client_app_netlink_descriptor_get(void);
extern socket_event_subscription_t * vpn_client_app_netlink_subscription_get(void);
extern internet_protocol_version4_module_t * vpn_client_app_internet_protocol_version4_module_get(void);
extern internet_protocol_version6_module_t * vpn_client_app_internet_protocol_version6_module_get(void);

#endif // __SNORLAX__VPN_CLIENT_APP__H__
