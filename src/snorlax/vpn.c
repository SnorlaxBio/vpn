/**
 * @file        snorlax/vpn.c
 * @brief
 * @details
 * 
 * @author      snorlax <ceo@snorlax.bio>
 * @since       June 2, 2024
 */

#include <snorlax/eva.h>

#include "vpn.h"

#include "vpn/tun.h"

static virtual_private_network_tun_t * tun = nil;
static descriptor_event_subscription_t * subscription = nil;

static void subscriptionOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void openOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void readOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void writeOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void closeOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);
static void exceptionOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node);

static descriptor_event_subscription_handler_t descriptorEventOn[descriptor_event_type_max] = {
    subscriptionOn,
    openOn,
    readOn,
    writeOn,
    closeOn,
    exceptionOn
};

extern int32_t virtual_private_network_run(void) {
    if(tun == nil) {
        snorlax_eva_on();

        tun = virtual_private_network_tun_gen();

        if(virtual_private_network_tun_open(tun) == success) {
            subscription = snorlax_eva_descriptor_sub((descriptor_t *) tun, descriptorEventOn);

            return snorlax_eva_run();
        }

        tun = virtual_private_network_tun_rem(tun);
    }

#ifndef   RELEASE
    snorlaxdbg(false, true, "warning", "");
#endif // RELEASE

    return fail;

}

static void subscriptionOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void openOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void readOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void writeOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void closeOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}

static void exceptionOn(___notnull descriptor_event_subscription_t * subscription, uint32_t type, event_subscription_event_t * node) {

}
