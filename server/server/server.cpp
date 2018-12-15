#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include "../../common/error.h"

Server::Server() {
    create_socket();
    create_address();
}

void Server::create_socket() {
    server_descriptor = Error::check(
            socket(PF_INET, SOCK_STREAM, 0),
            "Could not create socket!"
    );

    int is_on = 1;
    Error::check(
            setsockopt(server_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*) &is_on, sizeof(is_on)),
            "Could not set socket options!"
    );
}

void Server::create_address() {
    server_address.sin_family = PF_INET;
    server_address.sin_port = htons(6667);
    server_address.sin_addr.s_addr = INADDR_ANY;
}

void Server::start() {
    Error::check(
            bind(server_descriptor, (struct sockaddr*) &server_address, sizeof(server_address)),
            "Could not bind socket!"
    );

    Error::check(
            listen(server_descriptor, 10),
            "Could not listen on socket!"
    );
}

int Server::get_descriptor() const {
    return server_descriptor;
}

Server::~Server() {
    Error::check(
            close(server_descriptor),
            "Could not close socket!"
    );
}
