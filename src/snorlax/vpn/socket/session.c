#include "session.h"

/**
 * TODO: UDP/RAW 등을 구현
 */

extern socket_session_t * socket_session_gen(int32_t value, int32_t domain, int32_t type, int32_t protocol, void * addr, uint64_t addrlen) {
#ifndef   RELEASE
    snorlaxdbg(value <= invalid, false, "critical", "");
#endif // RELEASE

    socket_session_t * descriptor = (socket_session_t *) socket_gen(domain, type, protocol, addr, addrlen);

    descriptor->value = value;

    vpn_socket_protect((socket_t *) descriptor);

    descriptor_nonblock_on((descriptor_t *) descriptor);

    descriptor->status = (descriptor_state_open | descriptor_state_write);

    return descriptor;
}