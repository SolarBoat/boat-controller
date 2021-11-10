#include "BaseParameter.h"

template<typename T>
BaseParameter<T>::BaseParameter(const char *name, T value) : Parameter(name){
    this->value = value;
}

template<typename T>
int BaseParameter<T>::set_value(const T value) {
    if (this->value != value) {
        this->value = value;
        if(on_change_function) {        
            on_change_function();
        }
    }
    return PARAMETER_RCODE_OK;
}

template<typename T>
T BaseParameter<T>::get_value() {
    return this->value;
}

template<typename T>
void BaseParameter<T>::set_on_change(void (*fnPtr)()) {
    this->on_change_function = fnPtr;
}

// String
template<>
int BaseParameter<String>::set_value_string(const String *value) {
    return set_value(*value);
}

template<>
String BaseParameter<String>::get_value_string() {
    return value;
}

// Bool
template<>
int BaseParameter<bool>::set_value_string(const String *value) {
    if (value->equals("1") || value->equals("true") || value->equals("on")) {
        return set_value(true);
    } else if (value->equals("0") || value->equals("false") || value->equals("off")) {
        return set_value(false);
    } else {
        return PARAMETER_RCODE_INVALID_VALUE;
    } 
}

template<>
String BaseParameter<bool>::get_value_string() {
    if (this->value) {
        return String("true");
    } else {
        return String("false");
    }
}