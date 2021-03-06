#include <netinet/in.h>
#include <unistd.h>
#include "connection_accepter.h"
#include "../error/error.h"

ConnectionAccepter::ConnectionAccepter() {
    create_socket();
    create_address();
}

void ConnectionAccepter::create_socket() {
    server_descriptor = Error::guard(
            socket(PF_INET, SOCK_STREAM, 0),
            "Could not create socket!"
    );

    int is_on = 1;
    Error::guard(
            setsockopt(server_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &is_on, sizeof(is_on)),
            "Could not set socket options!"
    );
}

void ConnectionAccepter::create_address() {
    server_address.sin_family = PF_INET;
    server_address.sin_port = htons(6667);
    server_address.sin_addr.s_addr = INADDR_ANY;
}

void ConnectionAccepter::start() {
    Error::guard(
            bind(server_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)),
            "Could not bind socket!"
    );

    Error::guard(
            listen(server_descriptor, 10),
            "Could not listen on socket!"
    );
}

int ConnectionAccepter::get_descriptor() const {
    return server_descriptor;
}

ConnectionAccepter::~ConnectionAccepter() {
    Error::guard(
            close(server_descriptor),
            "Could not close socket!"
    );
}
