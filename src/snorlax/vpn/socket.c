#include "socket.h"

/**
 * TODO: UDP/RAW 등을 구현
 */

extern int32_t vpn_socket_protect(socket_t * descriptor) {
#ifndef   RELEASE
    snorlaxdbg(descriptor == nil, false, "critical", "");
#endif // RELEASE

    vpn_app_t * app = vpn_app_get();

    snorlaxdbg(app == nil, false, "critical", "");

    return network_tun_protect(vpn_tun_get(app), (descriptor_t *) descriptor);
}
