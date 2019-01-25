#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <string>
#include "multiplexer.h"
#include "../error/error.h"
#include <algorithm>

Multiplexer::Multiplexer() {
    FD_ZERO(&read_mask);
    FD_ZERO(&write_mask);
}

void Multiplexer::set_server_descriptor(int descriptor) {
    this->server_descriptor = descriptor;
}

void Multiplexer::set_read_from_client(read_function read_from_client) {
    this->read_from_client = read_from_client;
};

void Multiplexer::set_write_to_client(write_function write_to_client) {
    this->write_to_client = write_to_client;
};

void Multiplexer::start() {
    while (started) {
        wait_for_ready_descriptors();

        check_incoming_connection();

        for (int client_descriptor : open_connections) {
            check_readability(client_descriptor);

            check_writeability(client_descriptor);
        }
    }
}

void Multiplexer::wait_for_ready_descriptors() {
    FD_SET(server_descriptor, &read_mask); // Always listen for new connections to the server
    for (int client_descriptor : open_connections) { // Listen for data from already connected clients
        FD_SET(client_descriptor, &read_mask);
    }

    Error::guard(
            select(greatest_descriptor() + 1, &read_mask, &write_mask, nullptr, nullptr),
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
    }
}

void Multiplexer::check_readability(int client_descriptor) {
    if (FD_ISSET(client_descriptor, &read_mask)) {
        read_from_client(client_descriptor);
    }
}

void Multiplexer::check_writeability(int client_descriptor) {
    if (FD_ISSET(client_descriptor, &write_mask)) {
        write_to_client(client_descriptor);
    }
}

void Multiplexer::stop_writing_to(int client_descriptor) {
    FD_CLR(client_descriptor, &write_mask);
}

void Multiplexer::start_writing_to(int client_descriptor) {
    FD_SET(client_descriptor, &write_mask);
}

int Multiplexer::greatest_descriptor() {
    auto max = max_element(std::begin(open_connections), std::end(open_connections));

    if (max == open_connections.end()) {
        return server_descriptor;
    }

    return *max;
}

void Multiplexer::close_connection_with(int client_descriptor) {
    open_connections.erase(std::remove(open_connections.begin(), open_connections.end(), client_descriptor));
    close(client_descriptor);
}
