#include "config.h"

static vpn_client_app_config_t config = {
    .client_pool_size = 1,
};

extern const vpn_client_app_config_t * vpn_client_app_config_get(void) {
    return &config;
}