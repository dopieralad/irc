#ifndef IRC_TYPES_H
#define IRC_TYPES_H

#include <string>
#include <functional>

typedef std::function<void(int client_id, std::string message)> message_callback;

typedef std::function<bool(int)> read_function;

#endif //IRC_TYPES_H
