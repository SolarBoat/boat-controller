#ifndef NUM_PARAMETER_H_
#define NUM_PARAMETER_H_

#include "BaseParameter.h"

template<typename T>
class NumParameter : public BaseParameter<T> {
    public:
        NumParameter(const char *name, T value, T min, T max);
        int setValueString(const String *value) override;
        String getValueString() override;
        int setValue(const T value) override;
    
    private:
        T minValue;
        T maxValue;
};

#include "NumParameter.tpp"

#endif