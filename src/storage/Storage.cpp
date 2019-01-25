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

struct Client* Storage::get_client_with_id(int client_id) {
    for (struct Client* client : clients) {
        if (client->id == client_id) {
            return client;
        }
    }

    throw std::invalid_argument("Client with id " + std::to_string(client_id) + " doesn't exist.");
}

Channel* Storage::get_channel_of_client(Client* client_to_look_for) {
    for (Channel* channel : channels) {
        for (struct Client* client : clients) {
            if (client->id == client_to_look_for->id) {
                return channel;
            }
        }
    }

    throw std::invalid_argument("Client with id " + std::to_string(client_to_look_for->id) + " is not on any channel.");
}

Storage::~Storage() {
    for (Channel* channel : channels) {
        delete channel;
    }

    for (struct Client* client : clients) {
        delete client;
    }
}



