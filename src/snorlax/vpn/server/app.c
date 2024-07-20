#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <snorlax/socket/server.h>

#include "app.h"

#include "../server.h"
#include "../session.h"

static vpn_server_app_t * vpn_server_app_func_rem(vpn_server_app_t * application);
static int32_t vpn_server_app_func_on(vpn_server_app_t * application);
static int32_t vpn_server_app_func_off(vpn_server_app_t * application);
static int32_t vpn_server_app_func_run(vpn_server_app_t * application);

static vpn_server_app_func_t func = {
    vpn_server_app_func_rem,
    vpn_server_app_func_on,
    vpn_server_app_func_off,
    vpn_server_app_func_run
};

static vpn_server_app_t * app = nil;

int main(int argc, char ** argv) {
    app = vpn_server_app_gen();
    vpn_server_app_on(app);

    int32_t ret = vpn_server_app_run(app);

    app = vpn_server_app_rem(app);

    return ret;
}

extern vpn_server_app_t * vpn_server_app_gen(void) {
    vpn_server_app_t * application = (vpn_server_app_t *) calloc(1, sizeof(vpn_server_app_t));

    application->func = address_of(func);

    return application;
}

static vpn_server_app_t * vpn_server_app_func_rem(vpn_server_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    return nil;
}

static int32_t vpn_server_app_func_on(vpn_server_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    if(application->engine == nil){
        application->engine = event_engine_gen();

        if(event_engine_on(application->engine) == fail) {
#ifndef   RELEASE
            snorlaxdbg(true, false, "critical", "");
#endif // RELEASE
        }

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(6207);
        addr.sin_addr.s_addr = 0;
        uint64_t addrlen = sizeof(struct sockaddr_in);

        application->server = event_engine_socket_server_sub(application->engine, socket_server_gen(AF_INET, SOCK_STREAM, IPPROTO_TCP, &addr, addrlen), vpn_session_event_subscription_handler_get(), vpn_server_event_subscription_handler_get());
    }

    return success;
}

static int32_t vpn_server_app_func_off(vpn_server_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    return success;
}

static int32_t vpn_server_app_func_run(vpn_server_app_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
#endif // RELEASE

    return event_engine_run(application->engine);
}