//
// Created by virzen on 24.01.19.
//

#include "ReadMessageInProgress.h"

ReadMessageInProgress::ReadMessageInProgress(int desired_size) {
    this->desired_size = desired_size;
}

bool ReadMessageInProgress::is_complete() {
    return desired_size == message.size();
}

std::string ReadMessageInProgress::get_message() {
    return message;
}

void ReadMessageInProgress::append(char *chars, int length) {
    int chars_to_add = length;

    // insert only as many characters as is left to the desired size
    if (message.size() + length > desired_size) {
        chars_to_add = desired_size - (int) message.size();
    }

    for (int i = 0; i < chars_to_add; i++) {
        message += chars[i];
    }
}
