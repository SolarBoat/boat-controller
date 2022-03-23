#include "Channel.h"
#include <Particle.h>

std::map<std::string,Channel*> &Channel::allChannels() {
    static std::map<std::string,Channel*> channels;
    return channels;
}

Channel *Channel::getChannel(const std::string &name) {
    std::map<std::string,Channel*> &channels = allChannels();
    auto search = channels.find(name);
    if (search != channels.end()) {
        return search->second;
    } else {
        return nullptr;
    }
}

const std::map<std::string,Channel*> &Channel::getAllChannels() {
    return allChannels();
}

Channel::Channel(const std::string &name) {
    allChannels().insert(std::pair<std::string, Channel*>(name, this));
    Log.info("Added channel: %s", name.c_str());
}