#ifndef IRC_MESSAGEHANDLER_H
#define IRC_MESSAGEHANDLER_H

#include <string>
#include <functional>
#include "../types.h"
#include "../storage/Storage.h"

typedef std::function<void(std::vector<int>, std::string message)> send_message_to_clients_function;

const std::string UKNOWN_COMMAND_WARNING("Uknown command.");


class MessageHandler {

public:
    explicit MessageHandler(Storage storage);

    void receive_message(int client_id, std::string message);

    void set_send_message_to_clients(send_message_to_clients_function);

private:
    Storage storage;

    send_message_to_clients_function send_message_to_clients_ids;

    void send_message_to_client_id(int client_id, const std::string message);

    void send_message_to_channel(Channel channel, std::string);

    std::string format_message(Client client, std::string message);

    std::string get_welcome_message(Channel channel, struct Client client);
};


#endif //IRC_MESSAGEHANDLER_H
