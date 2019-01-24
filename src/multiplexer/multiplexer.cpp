#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <string>
#include "multiplexer.h"
#include "../error/error.h"

Multiplexer::Multiplexer() {
    FD_ZERO(&read_mask);
    FD_ZERO(&write_mask);
}

void Multiplexer::set_server_descriptor(int descriptor) {
    this->server_descriptor = descriptor;
    this->greatest_descriptor = descriptor;
}

void Multiplexer::set_read_from_client(read_function read_from_client) {
    this->read_from_client = read_from_client;
};

void Multiplexer::start() {
    while (started) {
        wait_for_ready_descriptors();

        check_incoming_connection();

        for (int descriptor = server_descriptor + 1; descriptor <= greatest_descriptor; descriptor++) {
            check_readability(descriptor);

            check_writeability(descriptor);
        }
    }
}

void Multiplexer::wait_for_ready_descriptors() {
    FD_SET(server_descriptor, &read_mask); // Always listen for new connections to the server
    for (int client_descriptor : open_connections) { // Listen for data from already connected clients
        FD_SET(client_descriptor, &read_mask);
    }

    Error::guard(
            select(greatest_descriptor + 1, &read_mask, &write_mask, nullptr, nullptr),
            "Could not select descriptors!"
    );
}

int Multiplexer::establish_connection() {
    sockaddr_in client_address{};
    socklen_t address_size = sizeof(client_address);

    int client_descriptor = Error::guard(
            accept(server_descriptor, (struct sockaddr *) &client_address, &address_size),
            "Could not accept incoming connection!"
    );
    open_connections.push_back(client_descriptor);

    printf("New connection from address: '%s:%d'.\n", inet_ntoa(client_address.sin_addr), client_address.sin_port);

    return client_descriptor;
}

void Multiplexer::check_incoming_connection() {
    if (FD_ISSET(server_descriptor, &read_mask)) { // New connection has arrived
        int client_descriptor = establish_connection();

        FD_SET(client_descriptor, &read_mask);

        if (client_descriptor > greatest_descriptor) {
            greatest_descriptor = client_descriptor;
        }
    }
}

void Multiplexer::check_readability(int client_descriptor) {
    if (FD_ISSET(client_descriptor, &read_mask)) {
        read_from_client(client_descriptor);
    }
}

void Multiplexer::check_writeability(int client_descriptor) {
    if (FD_ISSET(client_descriptor, &write_mask)) {
        bool finished_writing = write_to_client(client_descriptor);

        if (finished_writing) {
            FD_CLR(client_descriptor, &write_mask);

            if (client_descriptor == greatest_descriptor) {
                while (!FD_ISSET(greatest_descriptor, &read_mask) &&
                       !FD_ISSET(greatest_descriptor, &write_mask) &&
                       greatest_descriptor > server_descriptor) {
                    greatest_descriptor--;
                }
            }
        }
    }
}
