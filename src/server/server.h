#ifndef IRC_SERVER_H
#define IRC_SERVER_H

#include <map>
#include "../connection_accepter/connection_accepter.h"
#include "../multiplexer/multiplexer.h"
#include "../types.h"
#include "../read_message_in_progress/ReadMessageInProgress.h"
#include "../written_message_in_progress/WrittenMessageInProgress.h"

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
    std::map<int, ReadMessageInProgress*> messages_being_read;
    std::map<int, WrittenMessageInProgress*> messages_being_written;

    int create_new_message_in_progress(int client_descriptor);
};


#endif //IRC_SERVER_H
