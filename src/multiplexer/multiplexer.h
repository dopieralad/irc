#ifndef IRC_MULTIPLEXER_H
#define IRC_MULTIPLEXER_H

#include <functional>
#include <sys/param.h>
#include "../types.h"

class Multiplexer {

public:

    explicit Multiplexer();

    void set_server_descriptor(int descriptor);
    void set_read_from_client(read_function);
    void set_write_to_client(write_function);

    void start();

    void stop_writing_to(int client_descriptor);

    void start_writing_to(int client_descriptor);

private:

    bool started = true;

    int server_descriptor;

    fd_set read_mask;
    fd_set write_mask;

    std::vector<int> open_connections;

    read_function read_from_client;

    write_function write_to_client;

    void wait_for_ready_descriptors();

    int establish_connection();

    void check_incoming_connection();

    void check_readability(int client_descriptor);

    void check_writeability(int client_descriptor);

    int greatest_descriptor();
};


#endif //IRC_MULTIPLEXER_H
