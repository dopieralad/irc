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

#define MAX_QUEUE_BACKLOG 10 // 10 waiting connections
#define TRUE 1

int get_server_descriptor() {
    struct sockaddr_in server_address;
    server_address.sin_family = PF_INET;
    server_address.sin_port = htons(6667);
    server_address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0

    int server_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    int is_on = 1;
    setsockopt(server_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &is_on, sizeof(is_on));

    bind(server_descriptor, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_descriptor, MAX_QUEUE_BACKLOG);

    return server_descriptor;
}

int establish_connection(int server_descriptor) {
    struct sockaddr_in client_address;
    socklen_t address_size = sizeof(client_address);
    int client_descriptor = accept(server_descriptor, (struct sockaddr *) &client_address, &address_size);

    printf("New connection from address: '%s'.\n", inet_ntoa((struct in_addr) client_address.sin_addr));

    return client_descriptor;
}

void respond_to_client(int client_descriptor) {
    write(client_descriptor, "\n\nTest", 6);

    close(client_descriptor);
}

/**
 * TODO Extract "select" into a more abstract being: class or structure
 * TODO Implement generic I/O multiplexer: select->multiplex(read, write, handle_error)
 * TODO Add error handling for all I/O operations
 * TODO Add handling of SIGTERM and SIGKILL interrupts: free resources
 */
int main() {
    int server_descriptor = get_server_descriptor();

    fd_set read_mask;
    fd_set write_mask;
    FD_ZERO(&read_mask);
    FD_ZERO(&write_mask);
    int greatest_descriptor = server_descriptor;

    while (TRUE) {
        FD_SET(server_descriptor, &read_mask); // Always listen for new connections to server

        // Wait for any descriptors ready for read or write
        int active_descriptors = select(greatest_descriptor + 1, &read_mask, &write_mask, NULL, NULL);

        if (FD_ISSET(server_descriptor, &read_mask)) { // New connection has arrived
            int client_descriptor = establish_connection(server_descriptor);

            FD_SET(client_descriptor, &write_mask);

            if (client_descriptor > greatest_descriptor) {
                greatest_descriptor = client_descriptor;
            }
        }

        for (int descriptor = server_descriptor + 1; descriptor <= greatest_descriptor; descriptor++) {
            if (FD_ISSET(descriptor, &write_mask)) {
                respond_to_client(descriptor);

                FD_CLR(descriptor, &write_mask);

                if (descriptor == greatest_descriptor) {
                    while (greatest_descriptor > server_descriptor && !FD_ISSET(greatest_descriptor, &write_mask)) {
                        greatest_descriptor -= 1;
                    }
                }
            }
        }
    }

    close(server_descriptor);

    return EXIT_SUCCESS;
}