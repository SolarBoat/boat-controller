#ifndef BASE_PARAMETER_H_
#define BASE_PARAMETER_H_

#include "Parameter.h"

template<typename T>
class BaseParameter : public Parameter {
    public:
        BaseParameter(const char *name, T value);
        int set_value_string(const String *value) override;
        String get_value_string() override;

        T get_value();
        virtual int set_value(const T value);
        void set_on_change(void (*fnPtr)());
    
    private:
        T value;
        void (*on_change_function)();
};

#include "BaseParameter.tpp"

#endif