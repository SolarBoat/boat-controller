#include "BaseChannel.h"

template<typename T>
void BaseChannel<T>::setValue(const T &value) {
    this->value = value;
}

template<typename T>
T BaseChannel<T>::getValue() {
    return value;
}

template<typename T>
BaseChannel<T>::BaseChannel(const std::string &name) : Channel(name) {

}

template<typename T>
BaseChannel<T> &BaseChannel<T>::get(const std::string &name) {
    Channel *channel = Channel::getChannel(name);
    if (channel != nullptr) {
        return *((BaseChannel<T>*) channel);
    } else {
        return *(new BaseChannel<T>(name));
    }
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