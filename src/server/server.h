#ifndef IRC_SERVER_H
#define IRC_SERVER_H

#include <map>
#include "../connection_accepter/connection_accepter.h"
#include "../multiplexer/multiplexer.h"
#include "../types.h"
#include "../message_in_progress/MessageInProgress.h"

class Server {

public:
    Server();
    void start();
    void on_message(message_callback);

private:
    ConnectionAccepter connection_accepter;
    Multiplexer multiplexer;
    message_callback incoming_message_callback;
    std::map<int, MessageInProgress*> messages_in_progress;

    int create_new_message_in_progress(int client_descriptor);
};


#endif //IRC_SERVER_H
