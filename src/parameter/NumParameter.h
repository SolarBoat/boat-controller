#ifndef NUM_PARAMETER_H_
#define NUM_PARAMETER_H_

#include "BaseParameter.h"

template<typename T>
class NumParameter : public BaseParameter<T> {
    public:
        NumParameter(const char *name, T value);
        void set_value_string(const String *value) override;
        String get_value_string() override;
};

#include "NumParameter.tpp"

#endif