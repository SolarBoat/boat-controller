#include "BaseParameter.h"

template class BaseParameter<std::string>;
template class BaseParameter<bool>;

template class BaseParameter<int>;
template class BaseParameter<float>;

template<typename T>
BaseParameter<T>::BaseParameter(const char *name, T value) : Parameter(name){
    this->value = value;
}

template<typename T>
int BaseParameter<T>::setValue(const T value) {
    if (this->value != value) {
        this->value = value;
        if(on_change_function) {        
            on_change_function();
        }
    }
    return PARAMETER_RCODE_OK;
}

template<typename T>
T BaseParameter<T>::getValue() {
    return this->value;
}

template<typename T>
void BaseParameter<T>::setOnChange(void (*fnPtr)()) {
    this->on_change_function = fnPtr;
}

template<typename T>
int BaseParameter<T>::setValueString(const std::string &value) {
    return 0;
}

template<typename T>
std::string BaseParameter<T>::getValueString() {
    return 0;
}

// String
template<>
int BaseParameter<std::string>::setValueString(const std::string &value) {
    return setValue(value);
}

template<>
std::string BaseParameter<std::string>::getValueString() {
    return value;
}

// Bool
template<>
int BaseParameter<bool>::setValueString(const std::string &value) {
    if (value == "1" || value == "true" || value == "on") {
        return setValue(true);
    } else if (value == "0" || value == "false" || value == "off") {
        return setValue(false);
    } else {
        return PARAMETER_RCODE_INVALID_VALUE;
    } 
}

template<>
std::string BaseParameter<bool>::getValueString() {
    if (this->value) {
        return "true";
    } else {
        return "false";
    }
}