#include "Storage.h"

Storage::Storage() {
    default_channel = get_or_create_channel("default");
};


struct Client* Storage::create_client(int client_descriptor, std::string name) {
    auto * new_client = new Client { .id = client_descriptor, .name = name };
    clients.push_back(new_client);

    return new_client;
}

struct Channel* Storage::get_default_channel() {
    return default_channel;
}

void Storage::move_client_to_channel(struct Client *client, struct Channel *channel) {
    Channel* current_channel = get_channel_of_client(client);
    current_channel->remove_client(client);

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
        if (channel->is_client_in_it(client_to_look_for)) {
            return channel;
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

Channel *Storage::get_or_create_channel(std::string channel_name) {
    for (Channel* channel : channels) {
        if (channel->get_name() == channel_name) {
            return channel;
        }
    }

    Channel *channel = new Channel(channel_name);

    channels.push_back(channel);

    return channel;
}

void Storage::add_client_to_channel(struct Client *client, Channel *channel) {
    channel->add_client(client);
}

void Storage::remove_client_from_channel(Client *client, Channel *channel) {
    channel->remove_client(client);
}



