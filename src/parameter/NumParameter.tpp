#include "NumParameter.h"

template<typename T>
NumParameter<T>::NumParameter(const char *name, T value, T min, T max) : BaseParameter<T>(name, value){
    minValue = min;
    maxValue = max;
}

template<typename T>
int NumParameter<T>::setValue(const T value) {
    if (value < minValue || value > maxValue) {
        return PARAMETER_RCODE_INVALID_VALUE;
    }
    return BaseParameter<T>::setValue(value);
}

// Int
template<>
int NumParameter<int>::setValueString(const String *value) {
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
    return this->setValue(i);
}

template<>
String NumParameter<int>::getValueString() {
    return String(this->getValue());
}

// Float
template<>
int NumParameter<float>::setValueString(const String *value) {
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
    return this->setValue(f);
}

template<>
String NumParameter<float>::getValueString() {
    return String(this->getValue());
}