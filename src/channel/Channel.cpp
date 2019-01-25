#include "Channel.h"

Channel::Channel(std::string name): name(name) {

}

void Channel::add_client(struct Client* client) {
    clients.push_back(client);
}

void Channel::remove_client(Client *client) {
    // https://en.cppreference.com/w/cpp/algorithm/remove
    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
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

bool Channel::is_client_in_it(Client *client_to_look_for) {
    for (Client *client : clients) {
        if (client == client_to_look_for) {
            return true;
        }
    }

    return false;
}
