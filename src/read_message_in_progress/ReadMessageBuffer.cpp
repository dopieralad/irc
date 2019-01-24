//
// Created by virzen on 24.01.19.
//

#include <unistd.h>
#include "ReadMessageBuffer.h"
#include "../error/error.h"

const int MESSAGE_CONTENT_BUFFER_LENGTH = 128;

ReadMessageBuffer::ReadMessageBuffer(int desired_size) {
    this->desired_size = desired_size;
}

bool ReadMessageBuffer::has_been_read_completely() {
    return desired_size == message.size();
}

std::string ReadMessageBuffer::get_message() {
    return message;
}

void ReadMessageBuffer::append(char *chars, int length) {
    int chars_to_add = length;

    // insert only as many characters as is left to the desired size
    if (message.size() + length > desired_size) {
        chars_to_add = desired_size - (int) message.size();
    }

    for (int i = 0; i < chars_to_add; i++) {
        message += chars[i];
    }
}

void ReadMessageBuffer::read_some(int client_descriptor) {
    char content_buffer[MESSAGE_CONTENT_BUFFER_LENGTH];

    int bytes_read = Error::guard(
            read(client_descriptor, content_buffer, MESSAGE_CONTENT_BUFFER_LENGTH),
            "Couldn't read message content"
    );

    append(content_buffer, bytes_read);

}
