#include <stdlib.h>
#include <iostream>
#include "server/server.h"
#include "multiplexer/multiplexer.h"
#include "connection_accepter/connection_accepter.h"

/**
 * TODO Add handling of SIGTERM and SIGKILL interrupts: free resources
 */
int main() {
    Server server;

    server.on_message([](int client_id, char* message[]) -> void {
        printf("<%d>: %s\n", client_id, message);
    });

    server.start();

    return EXIT_SUCCESS;
}