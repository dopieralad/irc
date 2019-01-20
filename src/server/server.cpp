#include <iostream>
#include <unistd.h>
#include "server.h"
#include "../error/error.h"

Server::Server() {
    int server_descriptor = connection_accepter.get_descriptor();
    multiplexer.set_server_descriptor(server_descriptor);

    multiplexer.set_read_from_client([this](int client_descriptor) -> bool {
        char* buffer[10];
        // NOTE: probably waits on this read after connection, is the file empty?
        int bytes_read = Error::guard(
                (int) read(client_descriptor, buffer, 10),
                "Couldn't read from the client descriptor!"
        );

        this->incoming_message_callback(client_descriptor, buffer);

        return true;
    });
}

void Server::start() {
    connection_accepter.start();
    multiplexer.start();
}

void Server::on_message(message_callback incoming_message_callback) {
    this->incoming_message_callback = incoming_message_callback;
}

