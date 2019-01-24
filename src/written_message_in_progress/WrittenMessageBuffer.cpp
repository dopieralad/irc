#include "WrittenMessageBuffer.h"
#include <unistd.h>


WrittenMessageBuffer::WrittenMessageBuffer(std::string message) {
    this->message = message;
}

void WrittenMessageBuffer::write_some(int descriptor) {
    const char* buffer = message.c_str();

    int bytes_written = (int) write(descriptor, buffer + written_bytes, message.size());

    written_bytes += bytes_written;
}

bool WrittenMessageBuffer::has_been_written_completely() {
    return message.size() == written_bytes;
}

