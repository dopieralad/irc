#include "MessageHandler.h"
#include "../types.h"
#include "../message/Message.h"
#include "../channel/Channel.h"

MessageHandler::MessageHandler(Storage storage) : storage(storage) {

};

void MessageHandler::receive_message(int client_id, std::string raw_message) {
    Message message(raw_message);

    bool is_client_logged_in = storage.is_client_with_id_logged_in(client_id);
    bool is_login_command = message.get_type() == login_command;

    if (!is_client_logged_in && !is_login_command) {
        send_message_to_client_id(client_id, "You need to log-in first. Try /login <nickname>");
        return;
    }

    switch (message.get_type()) {
        case text_message: {
            // get channel that client_id is on
            // send a message to that channel
            return;
        }
        case login_command: {
            if (message.get_content().empty()) {
                send_message_to_client_id(client_id, "You need to enter a nickname. Usage: /login <nickname>");
                return;
            }

            struct Client created_client = storage.create_client(client_id, message.get_content());

            // TODO: move to storage to keep all the logic there?
            Channel default_channel = storage.get_default_channel();
            Channel clients_channel = storage.add_client_to_channel(created_client, default_channel);

            send_message_to_channel(clients_channel, get_welcome_message(clients_channel, created_client));

            return;
        }
        case join_command: {
            // check if channels with the name exists
            // create if it doesn't
            // join client to the channel
            // send info that client joined to that channel
            return;
        }
//        case leave_command:
//            // remove client from channel
//            // send info that client left to that channel
//
//            // close connection with the client?
//
//            return;
        case unknown_command: {
            send_message_to_client_id(client_id, UKNOWN_COMMAND_WARNING);
            return;
        }
    }
}


// TODO: extract?
std::string MessageHandler::format_message(Client client, std::string message) {
    return "<" + std::to_string(client.id) + ">: " + message;
}

std::string MessageHandler::get_welcome_message(Channel channel, struct Client client) {
    return client.name + " joined " + channel.get_name();
}

void MessageHandler::send_message_to_client_id(int client_id, const std::string message) {
    std::vector<int> client_ids = { client_id };
    send_message_to_clients_ids(client_ids, message);
}

void MessageHandler::send_message_to_channel(Channel channel, std::string message) {
    std::vector clients_ids = channel.get_clients_ids();
    send_message_to_clients_ids(clients_ids, message);
}

void MessageHandler::set_send_message_to_clients(send_message_to_clients_function send_message_to_clients) {
    this->send_message_to_clients_ids = send_message_to_clients;
}

