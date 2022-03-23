#ifndef BASE_CHANNEL_H_
#define BASE_CHANNEL_H_

#include "Channel.h"

template<typename T>
class BaseChannel  : public Channel {
    public:
        std::string getValueString() override;
        void setValue(const T &value);
        T getValue();

        static BaseChannel<T> &get(const std::string &name);
    
    private:
        BaseChannel(const std::string &name);

        T value;
};

#include "BaseChannel.tpp"

#endif