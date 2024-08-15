#include "config.h"

static vpn_single_app_config_t config = {
    .dummy = 1,
};

extern const vpn_single_app_config_t * vpn_single_app_config_get(void) {
    return &config;
}
