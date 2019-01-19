#ifndef IRC_MULTIPLEXER_H
#define IRC_MULTIPLEXER_H

#include <sys/param.h>

class Multiplexer {

public:

    explicit Multiplexer();

    void set_server_descriptor(int descriptor);

    void start();

private:

    bool started = true;

    int server_descriptor;
    int greatest_descriptor;

    fd_set read_mask;
    fd_set process_mask;
    fd_set write_mask;

    bool (* read_from_client)(int);

    bool (* process_client)(int);

    bool (* write_to_client)(int);

    void wait_for_ready_descriptors();

    int establish_connection();

    void check_incoming_connection();

    void check_readability(int client_descriptor);

    void check_processability(int client_descriptor);

    void check_writeability(int client_descriptor);
};


#endif //IRC_MULTIPLEXER_H
