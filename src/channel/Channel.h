#ifndef IRC_CHANNEL_H
#define IRC_CHANNEL_H


#include "../types.h"

class Channel {

public:
    explicit Channel(std::string name);

    void add_client(struct Client client);
    std::vector<int> get_clients_ids();
    std::string get_name();

private:
    std::string name;
    std::vector<struct Client> clients;
};


#endif //IRC_CHANNEL_H
