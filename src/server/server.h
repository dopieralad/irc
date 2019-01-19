#ifndef IRC_SERVER_H
#define IRC_SERVER_H

#include "../connection_accepter/connection_accepter.h"
#include "../multiplexer/multiplexer.h"

class Server {

public:
    Server();
    void start();

private:
    ConnectionAccepter connection_accepter;
    Multiplexer multiplexer;

};


#endif //IRC_SERVER_H
