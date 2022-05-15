#include "BaseChannel.h"

template class BaseChannel<std::string>; 
template class BaseChannel<int>; 
template class BaseChannel<float>; 
template class BaseChannel<bool>; 

template<typename T>
void BaseChannel<T>::setValue(const T &value) {
    this->value = value;
}

template<typename T>
T BaseChannel<T>::getValue() {
    return value;
}

template<typename T>
int BaseChannel<T>::getLogLevel() {
    return logLevel;
}

template<typename T>
BaseChannel<T>::BaseChannel(const std::string &name) : Channel(name) {

}

template<typename T>
BaseChannel<T>& BaseChannel<T>::get(const std::string &name) {
    Channel *channel = Channel::getChannel(name);
    if (channel != nullptr) {
        return *((BaseChannel<T>*) channel);
    } else {
        return *(new BaseChannel<T>(name));
    }
}

template<typename T>
BaseChannel<T>& BaseChannel<T>::get(const std::string &name, int logLevel) {
    BaseChannel<T>& channel = BaseChannel<T>::get(name);
    channel.logLevel = logLevel;
    return channel;
}


// String
template<>
std::string BaseChannel<std::string>::getValueString() {
    return value;
}

// int
template<>
std::string BaseChannel<int>::getValueString() {
    return std::to_string(value);
}

//float
template<>
std::string BaseChannel<float>::getValueString() {
    return std::to_string(value);
}

//bool
template<>
std::string BaseChannel<bool>::getValueString() {
    return value ? "true" : "false";
}