#ifndef IRC_SERVER_H
#define IRC_SERVER_H


class Server {

public:
    Server();

    void start();

    int get_descriptor() const;

    virtual ~Server();

private:
    int server_descriptor;
    sockaddr_in server_address;

    void create_socket();

    void create_address();
};


#endif //IRC_SERVER_H
