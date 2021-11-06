#include "BaseParameter.h"

template<typename T>
BaseParameter<T>::BaseParameter(const char *name, T value) : Parameter(name){
    this->value = value;
}

template<typename T>
void BaseParameter<T>::set_value(const T value) {
    this->value = value;
    if(on_change_function) {        
        on_change_function();
    }
}

template<typename T>
T BaseParameter<T>::get_value() {
    return this->value;
}

template<typename T>
void BaseParameter<T>::set_on_change(void (*fnPtr)()) {
    this->on_change_function = fnPtr;
}

// Bool
template<>
void BaseParameter<bool>::set_value_string(const String *value) {
    this->value = value->equals("1") || value->equals("true") || value->equals("on");
}

template<>
String BaseParameter<bool>::get_value_string() {
    if (this->value) {
        return String("true");
    } else {
        return String("false");
    }
}