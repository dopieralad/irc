#include <stdlib.h>
#include "server/server.h"
#include "multiplexer/multiplexer.h"
#include "connection_accepter/connection_accepter.h"

/**
 * TODO Add handling of SIGTERM and SIGKILL interrupts: free resources
 */
int main() {
    Server server;

    server.start();

    return EXIT_SUCCESS;
}