#ifndef IRC_SERVER_H
#define IRC_SERVER_H

#include <map>
#include "../connection_accepter/connection_accepter.h"
#include "../multiplexer/multiplexer.h"
#include "../types.h"
#include "../read_message_in_progress/ReadMessageBuffer.h"
#include "../written_message_in_progress/WrittenMessageBuffer.h"

class Server {

public:
    Server();
    void start();
    void on_message(message_callback);

    void send_message_to_client(int client_id, std::string basic_string);

private:
    ConnectionAccepter connection_accepter;
    Multiplexer multiplexer;
    message_callback incoming_message_callback;
    std::map<int, ReadMessageBuffer*> messages_being_read;
    std::map<int, WrittenMessageBuffer*> messages_being_written;

    int read_message_content_length(int client_descriptor);
};


#endif //IRC_SERVER_H
