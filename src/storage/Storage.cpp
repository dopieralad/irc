#include "Storage.h"

Storage::Storage() : default_channel("default") {
    channels.push_back(default_channel);
};


struct Client Storage::create_client(int client_descriptor, std::string name) {
    struct Client new_client = { .id = client_descriptor, .name = name };
    clients.push_back(new_client);

    return new_client;
}

struct Channel Storage::get_default_channel() {
    return default_channel;
}

Channel Storage::add_client_to_channel(struct Client client, struct Channel channel) {
    channel.add_client(client);

    if (channel.get_name() == default_channel.get_name()) {
        default_channel = channel;
    }

    return channel;
}

bool Storage::is_client_with_id_logged_in(int client_id) {
    for (struct Client client : clients) {
        if (client.id == client_id) {
            return true;
        }
    }

    return false;
}

