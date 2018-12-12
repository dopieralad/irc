#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include "multiplexer.h"

Multiplexer::Multiplexer(int server_descriptor, bool (* read_function)(int), bool (* write_function)(int)) :
        server_descriptor(server_descriptor),
        greatest_descriptor(server_descriptor),
        read_from_client(read_function),
        write_to_client(write_function) {
    FD_ZERO(&read_mask);
    FD_ZERO(&write_mask);
}

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

    select(greatest_descriptor + 1, &read_mask, &write_mask, nullptr, nullptr);
}

int Multiplexer::establish_connection() {
    sockaddr_in client_address{};
    socklen_t address_size = sizeof(client_address);
    int client_descriptor = accept(server_descriptor, (struct sockaddr*) &client_address, &address_size);

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
        bool finished_reading = read_from_client(client_descriptor);

        if (finished_reading) {
            FD_CLR(client_descriptor, &read_mask);
            FD_SET(client_descriptor, &write_mask);
        }
    }
}

void Multiplexer::check_writeability(int client_descriptor) {
    if (FD_ISSET(client_descriptor, &write_mask)) {
        bool finished_writing = write_to_client(client_descriptor);

        if (finished_writing) {
            FD_CLR(client_descriptor, &write_mask);

            close(client_descriptor);

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
