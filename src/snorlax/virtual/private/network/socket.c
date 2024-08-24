

#include "socket.h"

#include "application.h"

extern int32_t virtual_private_network_socket_func_protect(socket_t * socket) {
#ifndef   RELEASE
    snorlaxdbg(socket == nil, false, "critical", "");
#endif // RELEASE

    virtual_private_network_application_t * application = virtual_private_network_application_get();

    snorlaxdbg(application == nil, false, "critical", "");

    return network_tun_protect(virtual_private_network_application_tun_get(application), (descriptor_t *) socket);
}