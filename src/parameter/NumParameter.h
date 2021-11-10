#ifndef NUM_PARAMETER_H_
#define NUM_PARAMETER_H_

#include "BaseParameter.h"

template<typename T>
class NumParameter : public BaseParameter<T> {
    public:
        NumParameter(const char *name, T value, T min, T max);
        int set_value_string(const String *value) override;
        String get_value_string() override;
        int set_value(const T value) override;
    
    private:
        T minValue;
        T maxValue;
};

#include "NumParameter.tpp"

#endif