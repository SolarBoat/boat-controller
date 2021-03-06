#ifndef NUM_PARAMETER_H_
#define NUM_PARAMETER_H_

#include "BaseParameter.h"

template<typename T>
class NumParameter : public BaseParameter<T> {
    public:
        NumParameter(const char *name, T value, T min, T max);
        int setValueString(const std::string &value) override;
        std::string getValueString() override;
        int setValue(const T value) override;
    
    private:
        T minValue;
        T maxValue;
};

#endif