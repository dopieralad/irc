//
// Created by virzen on 24.01.19.
//

#include "MessageInProgress.h"

MessageInProgress::MessageInProgress(int desired_size) {
    this->desired_size = desired_size;
}

bool MessageInProgress::is_complete() {
    return desired_size == message.size();
}

std::string MessageInProgress::get_message() {
    return message;
}

void MessageInProgress::append(char *chars, int length) {
    int chars_to_add = length;

    // insert only as many characters as is left to the desired size
    if (message.size() + length > desired_size) {
        chars_to_add = desired_size - (int) message.size();
    }

    for (int i = 0; i < chars_to_add; i++) {
        message += chars[i];
    }
}
