#ifndef IRC_MULTIPLEXER_H
#define IRC_MULTIPLEXER_H


#include <sys/param.h>

class Multiplexer {

public:

    Multiplexer(int server_descriptor, bool (* read_function)(int), bool (* write_function)(int));

    void start();

private:

    bool started = true;

    int server_descriptor;
    int greatest_descriptor;

    fd_set read_mask;
    fd_set write_mask;

    bool (* read_from_client)(int);

    bool (* write_to_client)(int);

    void wait_for_ready_descriptors();

    int establish_connection();

    void check_incoming_connection();

    void check_readability(int client_descriptor);

    void check_writeability(int client_descriptor);
};


#endif //IRC_MULTIPLEXER_H
