#include "BaseParameter.h"

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

// String
template<>
int BaseParameter<String>::setValueString(const String &value) {
    return setValue(value);
}

template<>
String BaseParameter<String>::getValueString() {
    return value;
}

// Bool
template<>
int BaseParameter<bool>::setValueString(const String &value) {
    if (value.equals("1") || value.equals("true") || value.equals("on")) {
        return setValue(true);
    } else if (value.equals("0") || value.equals("false") || value.equals("off")) {
        return setValue(false);
    } else {
        return PARAMETER_RCODE_INVALID_VALUE;
    } 
}

template<>
String BaseParameter<bool>::getValueString() {
    if (this->value) {
        return String("true");
    } else {
        return String("false");
    }
}