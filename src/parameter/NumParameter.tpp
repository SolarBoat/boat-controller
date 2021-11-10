#include "NumParameter.h"

template<typename T>
NumParameter<T>::NumParameter(const char *name, T value, T min, T max) : BaseParameter<T>(name, value){
    minValue = min;
    maxValue = max;
}

template<typename T>
int NumParameter<T>::set_value(const T value) {
    if (value < minValue || value > maxValue) {
        return PARAMETER_RCODE_INVALID_VALUE;
    }
    return BaseParameter<T>::set_value(value);
}

// Int
template<>
int NumParameter<int>::set_value_string(const String *value) {
    int i;
    if (value->charAt(0) == '-') {
        i = -value->substring(1).toInt();
        if (i == 0 && value->charAt(1) != '0') {
            return PARAMETER_RCODE_INVALID_VALUE;
        }
    } else {
        i = -value->toInt();
        if (i == 0 && value->charAt(0) != '0') {
            return PARAMETER_RCODE_INVALID_VALUE;
        }
    }
    return this->set_value(i);
}

template<>
String NumParameter<int>::get_value_string() {
    return String(this->get_value());
}

// Float
template<>
int NumParameter<float>::set_value_string(const String *value) {
    float f;
    if (value->charAt(0) == '-') {
        f = -value->substring(1).toFloat();
        if (f == 0 && value->charAt(1) != '0') {
            return PARAMETER_RCODE_INVALID_VALUE;
        }
    } else {
        f = value->toFloat();
        if (f == 0 && value->charAt(0) != '0') {
            return PARAMETER_RCODE_INVALID_VALUE;
        }
    }
    return this->set_value(f);
}

template<>
String NumParameter<float>::get_value_string() {
    return String(this->get_value());
}