#include <unistd.h>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "server.h"
#include "../error/error.h"
#include "../written_message_in_progress/WrittenMessageBuffer.h"

const int MESSAGE_SIZE_LENGTH = 10;

Server::Server() {
    int server_descriptor = connection_accepter.get_descriptor();
    multiplexer.set_server_descriptor(server_descriptor);

    multiplexer.set_read_from_client([this](int client_descriptor) -> void {
        if (this->messages_being_read.count(client_descriptor) == 0) {
            int message_content_length = read_message_content_length(client_descriptor);
            this->messages_being_read[client_descriptor] = new ReadMessageBuffer(message_content_length);
        }

        auto* messageInProgress = this->messages_being_read[client_descriptor];
        messageInProgress->read_some(client_descriptor);

        if (messageInProgress->has_been_read_completely()) {
            this->incoming_message_callback(client_descriptor, messageInProgress->get_message());
            this->messages_being_read.erase(client_descriptor);
        }
    });

    multiplexer.set_write_to_client([this](int client_descriptor) -> bool {
        if (this->messages_being_written.count(client_descriptor) == 1) {
            WrittenMessageBuffer* message = messages_being_written[client_descriptor];
            message->write_some(client_descriptor);

            if (message->has_been_written_completely()) {
                messages_being_written.erase(client_descriptor);
                multiplexer.stop_writing_to(client_descriptor);
            }
        }
    });
}


void Server::start() {
    connection_accepter.start();
    multiplexer.start();
}

int Server::read_message_content_length(int client_descriptor) {
    char buffer[MESSAGE_SIZE_LENGTH];

    // NOTE: probably waits on this read after connection, is the file empty?
    Error::guard(
            (int) read(client_descriptor, buffer, MESSAGE_SIZE_LENGTH),
            "Couldn't read from the client descriptor!"
    );

    // TODO?: handle error
    return atoi(buffer);
}

void Server::on_message(message_callback incoming_message_callback) {
    this->incoming_message_callback = incoming_message_callback;
}

std::string format_message(std::string raw_message) {
    int length = raw_message.length();
    std::ostringstream out;
    out << std::internal << std::setfill('0') << std::setw(10) << length;
    std::string padded_length = out.str();

    return padded_length + raw_message;
}

void Server::send_message_to_client(int client_id, std::string message) {
    std::string formatted_message = format_message(message);

    std::cout << std::to_string(client_id) << " <- " << formatted_message << std::endl;

    // FIXME: memory leak
    this->messages_being_written[client_id] = new WrittenMessageBuffer(formatted_message);
    multiplexer.start_writing_to(client_id);
}

void Server::send_message_to_clients(std::vector<int> client_ids, std::string message) {
    for (int client_id : client_ids) {
        send_message_to_client(client_id, message);
    }
}

void Server::close_connection_with(int client_descriptor) {
    multiplexer.close_connection_with(client_descriptor);
}


