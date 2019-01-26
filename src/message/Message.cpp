#include "Message.h"
#include "../utils/Utils.h"

const char COMMAND_PREFIX = '/';
const std::string LOGIN_COMMAND_NAME("login");
const std::string DISCONNECT_COMMAND_NAME("disconnect");
const std::string JOIN_COMMAND_NAME("join");
const int max_command_size = 10; // TODO: calculate based on commands

Message::Message(std::string raw_message) {
    bool is_command = raw_message[0] == COMMAND_PREFIX;

    if (!is_command) {
        type = text_message;
        content = raw_message;
        return;
    }

    unsigned long raw_message_without_prefix_size = raw_message.size() - 1;

    // http://www.cplusplus.com/reference/string/string/compare/
    if (raw_message.compare(1, Utils::min(LOGIN_COMMAND_NAME.size(), raw_message_without_prefix_size), LOGIN_COMMAND_NAME) == 0) {
        type = login_command;
        content = raw_message.substr(1 + LOGIN_COMMAND_NAME.size() + 1);
        return;
    }

    if (raw_message.compare(1, Utils::min(JOIN_COMMAND_NAME.size(), raw_message_without_prefix_size), JOIN_COMMAND_NAME) == 0) {
        type = join_command;
        content = raw_message.substr(1 + JOIN_COMMAND_NAME.size() + 1);
        return;
    }

    if (raw_message.compare(1, Utils::min(DISCONNECT_COMMAND_NAME.size(), raw_message_without_prefix_size), DISCONNECT_COMMAND_NAME) == 0) {
        type = disconnect_command;
        content = "";
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
