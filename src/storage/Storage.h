#ifndef IRC_STORAGE_H
#define IRC_STORAGE_H


#include "../types.h"
#include "../channel/Channel.h"

class Storage {

public:
    Storage();

    struct Client* create_client(int client_descriptor, std::string message);
    Channel* get_default_channel();
    void move_client_to_channel(struct Client *client, Channel *channel);
    void add_client_to_channel(struct Client *client, Channel *channel);

    bool is_client_with_id_logged_in(int client_id);

    struct Client* get_client_with_id(int client_id);

    Channel* get_channel_of_client(Client* client_to_look_for);

    ~Storage();

    Channel *get_or_create_channel(std::string basic_string);

    void remove_client_from_channel(Client *pClient, Channel *pChannel);

private:
    Channel* default_channel;
    std::vector<struct Channel*> channels;
    std::vector<struct Client*> clients;
};


#endif //IRC_STORAGE_H
