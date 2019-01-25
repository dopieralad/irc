#include "Storage.h"

Storage::Storage() {
    Channel* default_channel = new Channel("default");

    this->default_channel = default_channel;

    channels.push_back(default_channel);
};


struct Client* Storage::create_client(int client_descriptor, std::string name) {
    auto * new_client = new Client { .id = client_descriptor, .name = name };
    clients.push_back(new_client);

    return new_client;
}

struct Channel* Storage::get_default_channel() {
    return default_channel;
}

void Storage::add_client_to_channel(struct Client* client, struct Channel* channel) {
    channel->add_client(client);
}

bool Storage::is_client_with_id_logged_in(int client_id) {
    for (struct Client* client : clients) {
        if (client->id == client_id) {
            return true;
        }
    }

    return false;
}

Storage::~Storage() {
    for (Channel* channel : channels) {
        delete channel;
    }

    for (struct Client* client : clients) {
        delete client;
    }
}



