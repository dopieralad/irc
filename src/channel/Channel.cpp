#include "Channel.h"

Channel::Channel(std::string name): name(name) {

}

void Channel::add_client(struct Client* client) {
    clients.push_back(client);
}

std::vector<int> Channel::get_clients_ids() {
    std::vector<int> clients_ids;

    // map clients to their ids
    clients_ids.resize(clients.size());
    std::transform(
            clients.begin(),
            clients.end(),
            clients_ids.begin(),
            [](Client* client) {
                return client->id;
            }
    );

    return clients_ids;
}

std::string Channel::get_name() {
    return name;
}
