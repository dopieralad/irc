#ifndef IRC_SERVER_H
#define IRC_SERVER_H

#include "../connection_accepter/connection_accepter.h"
#include "../multiplexer/multiplexer.h"
#include "../types.h"

class Server {

public:
    Server();
    void start();
    void on_message(message_callback);

private:
    ConnectionAccepter connection_accepter;
    Multiplexer multiplexer;
    message_callback incoming_message_callback;

};


#endif //IRC_SERVER_H
