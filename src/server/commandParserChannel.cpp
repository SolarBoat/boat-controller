#include "commandParser.h"
#include "server.h"
#include "channel/Channel.h"

namespace commandParser {

    Logger parseChannelLog("app.parser.channel");

    void parseChannel(std::string &params) {
        if (params.rfind("get ", 0) == 0) {
            params.erase(0, params.find(' ') + 1);
            if (params == "all") {
                const std::map<std::string, Channel*> &channels = Channel::getAllChannels();
                for(auto it = channels.begin(); it != channels.end(); it++) {
                    std::string text = it->first + ": " + it->second->getValueString();
                    server::sendText(text);
                }
            } else {
                Channel* channel = Channel::getChannel(params);
                if (channel == nullptr) {
                    parseChannelLog.error("Channel not found: %s", params.c_str());
                } else {
                    std::string text = params + ": " + channel->getValueString();
                    server::sendText(text);
                }
            }
        }
    }

}