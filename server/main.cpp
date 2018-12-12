#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/select.h>
#include "multiplexer/multiplexer.h"
#include "server/server.h"

bool read_from_client(int client_descriptor) {
    printf("Reading descriptor: '%d'.\n", client_descriptor);
    return true;
}

bool process_client(int client_descriptor) {
    printf("Processing client: '%d'.\n", client_descriptor);
    return true;
}

bool write_to_client(int client_descriptor) {
    printf("Writing descriptor: '%d'.\n", client_descriptor);
    write(client_descriptor, "\n\nTest", 6);
    return true;
}

/**
 * TODO Add error handling for all I/O operations
 * TODO Add handling of SIGTERM and SIGKILL interrupts: free resources
 */
int main() {
    auto* server = new Server();
    auto* multiplexer = new Multiplexer(server->get_descriptor(), read_from_client, process_client, write_to_client);

    server->start();
    multiplexer->start();

    delete multiplexer;
    delete server;

    return EXIT_SUCCESS;
}