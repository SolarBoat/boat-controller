#ifndef BASE_CHANNEL_H_
#define BASE_CHANNEL_H_

#include "Channel.h"

template<typename T>
class BaseChannel  : public Channel {
    public:

        static const int LOG_LEVEL_ESSENTIAL = 1;
        static const int LOG_LEVEL_MODERATE = 2;
        static const int LOG_LEVEL_ALL = 3;

        std::string getValueString() override;
        void setValue(const T &value);
        T getValue();
        int getLogLevel();

        static BaseChannel<T>& get(const std::string &name);

        static BaseChannel<T>& get(const std::string &name, int logLevel);
    
    private:
        BaseChannel(const std::string &name);

        T value;
        int logLevel;
};

#endif