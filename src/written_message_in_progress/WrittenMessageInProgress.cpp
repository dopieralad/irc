#include "WrittenMessageInProgress.h"
#include <unistd.h>


WrittenMessageInProgress::WrittenMessageInProgress(std::string message) {
    this->message = message;
}

bool WrittenMessageInProgress::write_some(int descriptor) {
    const char* buffer = message.c_str();

    int bytes_written = (int) write(descriptor, buffer + written_bytes, message.size());

    written_bytes += bytes_written;

    return has_been_written_completely();
}

bool WrittenMessageInProgress::has_been_written_completely() {
    return message.size() == written_bytes;
}

