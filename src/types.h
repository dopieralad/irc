#ifndef IRC_TYPES_H
#define IRC_TYPES_H

#include <string>
#include <functional>

typedef std::function<void(int client_id, std::string message)> message_callback;

typedef std::function<void(int)> read_function;

typedef std::function<bool(int)> write_function;

enum MessageType { text_message, login_command, join_command, unknown_command, disconnect_command };

struct Client {
    int id;
    std::string name;
};

#endif //IRC_TYPES_H
