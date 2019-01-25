#include "MessageHandler.h"
#include "../types.h"
#include "../message/Message.h"
#include "../channel/Channel.h"

MessageHandler::MessageHandler(Storage* storage) : storage(storage) {

};

void MessageHandler::receive_message(int client_id, std::string raw_message) {
    Message message(raw_message);

    bool is_client_logged_in = storage->is_client_with_id_logged_in(client_id);
    bool is_login_command = message.get_type() == login_command;

    if (!is_client_logged_in && !is_login_command) {
        send_message_to_client_id(client_id, "You need to log-in first. Try /login <nickname>");
        return;
    }

    switch (message.get_type()) {
        case text_message: {
            struct Client* client = storage->get_client_with_id(client_id);
            Channel* channel_of_client = storage->get_channel_of_client(client);
            send_message_to_channel(channel_of_client, format_message(client->name, message.get_content()));

            return;
        }
        case login_command: {
            if (message.get_content().empty()) {
                send_message_to_client_id(client_id, "You need to enter a nickname. Usage: /login <nickname>");
                return;
            }

            struct Client* created_client = storage->create_client(client_id, message.get_content());

            // TODO: move to storage to keep all the logic there?
            Channel* default_channel = storage->get_default_channel();
            storage->add_client_to_channel(created_client, default_channel);

            send_message_to_channel(
                    default_channel,
                    get_welcome_message(default_channel->get_name(), created_client->name)
            );

            return;
        }
        case join_command: {
            if (message.get_content().empty()) {
                send_message_to_client_id(client_id, "You need to enter the channel name. Usage: /join <channel name>");
                return;
            }

            Client* client = storage->get_client_with_id(client_id);
            Channel* previous_channel = storage->get_channel_of_client(client);

            Channel* next_channel = storage->get_or_create_channel(message.get_content());
            storage->move_client_to_channel(client, next_channel);

            send_message_to_channel(
                    previous_channel,
                    get_goodbye_message(previous_channel->get_name(), client->name)
            );

            send_message_to_channel(
                    next_channel,
                    get_welcome_message(next_channel->get_name(), client->name)
            );

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
std::string MessageHandler::format_message(std::string client_name, std::string message) {
    return "<" + client_name + ">: " + message + "\n";
}

std::string MessageHandler::get_welcome_message(std::string channel_name, std::string client_name) {
    return client_name + " joined " + channel_name + "\n";
}

std::string MessageHandler::get_goodbye_message(std::string channel_name, std::string client_name) {
    return client_name + " left " + channel_name + "\n";
}

void MessageHandler::send_message_to_channel(Channel* channel, std::string message) {
    std::vector clients_ids = channel->get_clients_ids();
    send_message_to_clients_ids(clients_ids, message);
}

void MessageHandler::send_message_to_client_id(int client_id, const std::string message) {
    std::vector<int> client_ids = { client_id };
    send_message_to_clients_ids(client_ids, message);
}

void MessageHandler::set_send_message_to_clients_ids(send_message_to_clients_function send_message_to_clients) {
    this->send_message_to_clients_ids = send_message_to_clients;
}

