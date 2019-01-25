#include "Message.h"

const char COMMAND_PREFIX = '/';
const std::string LOGIN_COMMAND_NAME("login");
const std::string JOIN_COMMAND_NAME("join");

Message::Message(std::string raw_message) {
    bool is_command = raw_message[0] == COMMAND_PREFIX;

    if (!is_command) {
        type = text_message;
        content = raw_message;
        return;
    }

    // http://www.cplusplus.com/reference/string/string/compare/
    if (raw_message.compare(1, LOGIN_COMMAND_NAME.size(), LOGIN_COMMAND_NAME) == 0) {
        type = login_command;
        content = raw_message.substr(1 + LOGIN_COMMAND_NAME.size() + 1);
        return;
    }

    if (raw_message.compare(1, JOIN_COMMAND_NAME.size(), JOIN_COMMAND_NAME) == 0) {
        type = join_command;
        content = raw_message.substr(1 + JOIN_COMMAND_NAME.size() + 1);
        return;
    }

    type = unknown_command;
    content = "";
}

MessageType Message::get_type() {
    return type;
}

std::string Message::get_content() {
    return content;
}
