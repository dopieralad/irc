#include "MessageHandler.h"
#include "../types.h"
#include "../message/Message.h"

MessageHandler::MessageHandler() = default;

void MessageHandler::receive_message(int client_id, std::string raw_message) {
    Message message(raw_message);

    switch (message.get_type()) {
        case text_message:
            // get channel that client_id is on
            // get all clients on that channel
            // send a message to them
            return;
        case login_command:
            // associate client's id with username
            // join client to default channel
            // send info that client joined to that channel
            return;
        case join_command:
            // join client to specified channel
            // send info that client joined to that channel
            return;
//        case leave_command:
//            // remove client from channel
//            // send info that client left to that channel
//
//            // close connection with the client?
//
//            return;
        case unknown_command:
            // send warning to client
            return;
    }
}

void MessageHandler::set_send_message_to_clients(send_message_to_clients_function send_message_to_clients) {
    this->send_message_to_clients = send_message_to_clients;
}

