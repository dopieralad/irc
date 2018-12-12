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

#define MAX_QUEUE_BACKLOG 10 // 10 waiting connections

int get_server_descriptor() {
    sockaddr_in server_address{};
    server_address.sin_family = PF_INET;
    server_address.sin_port = htons(6667);
    server_address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0

    int server_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    int is_on = 1;
    setsockopt(server_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*) &is_on, sizeof(is_on));

    bind(server_descriptor, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_descriptor, MAX_QUEUE_BACKLOG);

    return server_descriptor;
}

bool read_from_client(int client_descriptor) {
    printf("Reading descriptor: '%d'.\n", client_descriptor);
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
    int server_descriptor = get_server_descriptor();

    auto* multiplexer = new Multiplexer(server_descriptor, read_from_client, write_to_client);
    multiplexer->start();
    delete multiplexer;

    close(server_descriptor);

    return EXIT_SUCCESS;
}