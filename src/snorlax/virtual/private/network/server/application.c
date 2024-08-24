#include "application.h"

static virtual_private_network_application_server_t * application = nil;

static virtual_private_network_application_config_t config = {
    .port = 6207,
};

static virtual_private_network_application_server_t * virtual_private_network_application_server_func_rem(virtual_private_network_application_server_t * o);
static int32_t virtual_private_network_application_server_func_on(virtual_private_network_application_server_t * o);
static int32_t virtual_private_network_application_server_func_off(virtual_private_network_application_server_t * o);
static int32_t virtual_private_network_application_server_func_run(virtual_private_network_application_server_t * o);

static virtual_private_network_application_server_func_t func = {
    virtual_private_network_application_server_func_rem,
    virtual_private_network_application_server_func_on,
    virtual_private_network_application_server_func_off,
    virtual_private_network_application_server_func_run
};

static virtual_private_network_application_server_t * virtual_private_network_application_server_gen(virtual_private_network_application_config_t * config);
static void virtual_private_network_application_server_cancel(___notnull event_engine_t * engine);

int main(int argc, char ** argv) {
    application = virtual_private_network_application_server_gen(address_of(config));

    if(virtual_private_network_application_server_on(application) == success) {
        int32_t ret = virtual_private_network_application_server_run(application);
        application = virtual_private_network_application_server_rem(application);

        return ret;
    }

    application = virtual_private_network_application_server_rem(application);

    return fail;
}

extern virtual_private_network_application_t * virtual_private_network_application_get(void) {
    return (virtual_private_network_application_t *) application;
}

extern network_tun_t * virtual_private_network_application_tun_get(virtual_private_network_application_t * application) {
    snorlaxdbg(false, true, "debug", "");

    return nil;
}

static virtual_private_network_application_server_t * virtual_private_network_application_server_gen(virtual_private_network_application_config_t * config) {
    virtual_private_network_application_server_t * o = (virtual_private_network_application_server_t *) calloc(1, sizeof(virtual_private_network_application_server_t));

    o->func = address_of(func);

    return o;
}

static virtual_private_network_application_server_t * virtual_private_network_application_server_func_rem(virtual_private_network_application_server_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    snorlaxdbg(false, true, "debug", "");

    return nil;
}

static int32_t virtual_private_network_application_server_func_on(virtual_private_network_application_server_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    if(o->engine == nil) {
        o->engine = event_engine_gen();

        snorlaxdbg(false, true, "implement", "");

        return success;
    }

    snorlaxdbg(false, true, "caution", "");

    return fail;
}

static int32_t virtual_private_network_application_server_func_off(virtual_private_network_application_server_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    if(o->engine) event_engine_off(o->engine, virtual_private_network_application_server_cancel);

    return success;
}

static int32_t virtual_private_network_application_server_func_run(virtual_private_network_application_server_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    return event_engine_run(o->engine);
}
