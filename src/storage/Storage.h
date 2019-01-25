#ifndef IRC_STORAGE_H
#define IRC_STORAGE_H


#include "../types.h"
#include "../channel/Channel.h"

class Storage {

public:
    Storage();

    struct Client* create_client(int client_descriptor, std::string message);
    Channel* get_default_channel();
    void add_client_to_channel(struct Client* client, struct Channel* channel);

    bool is_client_with_id_logged_in(int client_id);

    ~Storage();

private:
    Channel* default_channel;
    std::vector<struct Channel*> channels;
    std::vector<struct Client*> clients;
};


#endif //IRC_STORAGE_H
