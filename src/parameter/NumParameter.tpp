#include "NumParameter.h"

template<typename T>
NumParameter<T>::NumParameter(const char *name, T value) : BaseParameter<T>(name, value){
}


// Int
template<>
void NumParameter<int>::set_value_string(const String *value) {
    this->set_value(value->toInt());
}

template<>
String NumParameter<int>::get_value_string() {
    return String(this->get_value());
}

// Float
template<>
void NumParameter<float>::set_value_string(const String *value) {
    this->set_value(value->toFloat());
}

template<>
String NumParameter<float>::get_value_string() {
    return String(this->get_value());
}