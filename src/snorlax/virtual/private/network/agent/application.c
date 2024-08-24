#include "application.h"

int main(int argc, char ** argv) {
    return 0;
}

extern virtual_private_network_application_agent_t * virtual_private_network_application_agent_get(void) {

}

extern network_tun_t * virtual_private_network_application_agent_tun_get(virtual_private_network_application_agent_t * application) {
#ifndef   RELEASE
    snorlaxdbg(application == nil, false, "critical", "");
    snorlaxdbg(application->tun == nil, false, "critical", "");
#endif // RELEASE

    return (network_tun_t *) application->tun->descriptor;
}