#include <stdlib.h>
#include <iostream>
#include "server/server.h"
#include "multiplexer/multiplexer.h"
#include "utils/Utils.h"
#include "connection_accepter/connection_accepter.h"
#include "message_handler/MessageHandler.h"
#include "storage/Storage.h"

/**
 * TODO Add handling of SIGTERM and SIGKILL interrupts: free resources
 */
int main() {
    Server server;
    Storage storage;
    MessageHandler message_handler(&storage);

    server.on_message([&server, &message_handler](int client_id, std::string message) -> void {
//        std::cout << client_id << " -> " << message << std::endl;

        message_handler.receive_message(client_id, message);
    });

    message_handler.set_send_message_to_clients_ids([&server](std::vector<int> client_ids, std::string message) {
//        std::cout << Utils::join_vector(client_ids) << " <- " << message << std::endl;

        server.send_message_to_clients(client_ids, message);
    });

    message_handler.set_close_connection_with_client([&server](int client_id) -> void {
        server.close_connection_with(client_id);
    });

    server.start();

    return EXIT_SUCCESS;
}