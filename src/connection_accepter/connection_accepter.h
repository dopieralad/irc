#ifndef IRC_CONNECTION_ACCEPTER_H
#define IRC_CONNECTION_ACCEPTER_H


class ConnectionAccepter {

public:
    ConnectionAccepter();

    void start();

    int get_descriptor() const;

    virtual ~ConnectionAccepter();

private:
    int server_descriptor;
    sockaddr_in server_address;

    void create_socket();

    void create_address();
};


#endif //IRC_CONNECTION_ACCEPTER_H
