#ifndef IRC_MESSAGEHANDLER_H
#define IRC_MESSAGEHANDLER_H

#include <string>
#include <functional>

typedef std::function<void(std::vector<int>, std::string message)> send_message_to_clients_function;

const std::string UKNOWN_COMMAND_WARNING("Uknown command.");


class MessageHandler {

public:
    MessageHandler();

    void receive_message(int client_id, std::string message);

    void set_send_message_to_clients(send_message_to_clients_function);

private:
    send_message_to_clients_function send_message_to_clients;
};


#endif //IRC_MESSAGEHANDLER_H
