#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <string>
#include <map>

class Channel {
    public:
        virtual std::string getValueString() = 0;

        static Channel* getChannel(const std::string &name);
        static const std::map<std::string,Channel*> &getAllChannels();

    protected:
        Channel(const std::string &name);

    private:
        static std::map<std::string,Channel*> &allChannels();
};

#endif