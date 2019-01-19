#include <iostream>
#include "server.h"

Server::Server() {
    int server_descriptor = connection_accepter.get_descriptor();
    multiplexer.set_server_descriptor(server_descriptor);
}

void Server::start() {
    connection_accepter.start();
    multiplexer.start();
}

