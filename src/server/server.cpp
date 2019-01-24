#include <unistd.h>
#include "server.h"
#include "../error/error.h"
#include "../written_message_in_progress/WrittenMessageInProgress.h"

const int MESSAGE_SIZE_LENGTH = 10;
const int MESSAGE_CONTENT_BUFFER_LENGTH = 128;

Server::Server() {
    int server_descriptor = connection_accepter.get_descriptor();
    multiplexer.set_server_descriptor(server_descriptor);

    multiplexer.set_read_from_client([this](int client_descriptor) -> void {
        if (this->messages_being_read.count(client_descriptor) == 0) {
            this->create_new_message_in_progress(client_descriptor);
        }

        auto* messageInProgress = this->messages_being_read[client_descriptor];
        char content_buffer[MESSAGE_CONTENT_BUFFER_LENGTH];

        int bytes_read = Error::guard(
                read(client_descriptor, content_buffer, MESSAGE_CONTENT_BUFFER_LENGTH),
                "Couldn't read message content"
        );

        messageInProgress->append(content_buffer, bytes_read);

        if (messageInProgress->is_complete()) {
            this->incoming_message_callback(client_descriptor, messageInProgress->get_message());

            this->messages_being_read.erase(client_descriptor);
        }
    });

    multiplexer.set_write_to_client([this](int client_descriptor) -> bool {
        if (this->messages_being_written.count(client_descriptor) == 1) {
            WrittenMessageInProgress* message = messages_being_written[client_descriptor];
            bool has_whole_message_been_written = message->write_some(client_descriptor);

            if (has_whole_message_been_written) {
                messages_being_written.erase(client_descriptor);
                multiplexer.stop_writing_to(client_descriptor);
            }
        }
    });
}

int Server::create_new_message_in_progress(int client_descriptor) {
    char buffer[MESSAGE_SIZE_LENGTH];

    // NOTE: probably waits on this read after connection, is the file empty?
    int bytes_read = Error::guard(
            (int) read(client_descriptor, buffer, MESSAGE_SIZE_LENGTH),
            "Couldn't read from the client descriptor!"
    );

    // TODO: handle error
    int message_content_length = atoi(buffer);

    auto * message = new ReadMessageInProgress(message_content_length);

    this->messages_being_read[client_descriptor] = message;

    return bytes_read;
}

void Server::start() {
    connection_accepter.start();
    multiplexer.start();
}

void Server::on_message(message_callback incoming_message_callback) {
    this->incoming_message_callback = incoming_message_callback;
}

void Server::send_message_to_client(int client_id, std::string message) {
    this->messages_being_written[client_id] = new WrittenMessageInProgress(message);
    multiplexer.start_writing_to(client_id);
}

