#include "NumParameter.h"

template class NumParameter<int>;
template class NumParameter<float>;

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
int NumParameter<int>::setValueString(const std::string &value) {
    char *endptr[1];
    const char *startptr = value.c_str();
    errno = 0;
    long int l = std::strtol(startptr, endptr, 10);
    if (errno == 0 && *endptr != startptr && **endptr == '\0') {
        if (l > INT_MAX || l < INT_MIN) {
            return PARAMETER_RCODE_INVALID_VALUE;
        } else {
            return setValue(l);
        }
    } else {
        return PARAMETER_RCODE_INVALID_VALUE;
    }
}

template<>
std::string NumParameter<int>::getValueString() {
    return std::to_string(this->getValue());
}

// Float
template<>
int NumParameter<float>::setValueString(const std::string &value) {
    char *endptr[1];
    const char *startptr = value.c_str();
    errno = 0;
    double d = std::strtod(startptr, endptr);
    if (errno == 0 && *endptr != startptr && **endptr == '\0') {
        return setValue(d);
    } else {
        return PARAMETER_RCODE_INVALID_VALUE;
    }
}

template<>
std::string NumParameter<float>::getValueString() {
    return std::to_string(this->getValue());
}