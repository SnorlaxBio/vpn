/**
 * @file        snorlax/virtual/private/network/application.h
 * @brief
 * @details
 * 
 * @author      snorlax <opuntia@snorlax.bio>
 * @since       Aug 24, 2024
 */

#ifndef   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_APPLICATION__H__
#define   __SNORLAX__VIRTUAL_PRIVATE_NETWORK_APPLICATION__H__

#include <snorlax.h>
#include <snorlax/network/tun.h>

struct virtual_private_network_application;
struct virtual_private_network_application_func;

struct virtual_private_network_application_config;

typedef struct virtual_private_network_application          virtual_private_network_application_t;
typedef struct virtual_private_network_application_func     virtual_private_network_application_func_t;

typedef struct virtual_private_network_application_config   virtual_private_network_application_config_t;

struct virtual_private_network_application {
    ___reference virtual_private_network_application_func_t * func;
    sync_t * sync;
    ___reference virtual_private_network_application_config_t * config;
};

struct virtual_private_network_application_func {
    virtual_private_network_application_t * (*rem)(virtual_private_network_application_t *);
    int32_t (*on)(virtual_private_network_application_t *);
    int32_t (*off)(virtual_private_network_application_t *);
    int32_t (*run)(virtual_private_network_application_t *);
};

extern virtual_private_network_application_t * virtual_private_network_application_get(void);
extern network_tun_t * virtual_private_network_application_tun_get(virtual_private_network_application_t * application);

#endif // __SNORLAX__VIRTUAL_PRIVATE_NETWORK_APPLICATION__H__
