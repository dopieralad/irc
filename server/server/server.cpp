#include <netinet/in.h>
#include <unistd.h>
#include "server.h"

Server::Server() {
    create_socket();
    create_address();
}

void Server::create_socket() {
    server_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    int is_on = 1;
    setsockopt(server_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*) &is_on, sizeof(is_on));
}

void Server::create_address() {
    server_address.sin_family = PF_INET;
    server_address.sin_port = htons(6667);
    server_address.sin_addr.s_addr = INADDR_ANY;
}

void Server::start() {
    bind(server_descriptor, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_descriptor, 10);
}

int Server::get_descriptor() const {
    return server_descriptor;
}

Server::~Server() {
    close(server_descriptor);
}
