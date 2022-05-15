#ifndef BASE_PARAMETER_H_
#define BASE_PARAMETER_H_

#include "Parameter.h"

template<typename T>
class BaseParameter : public Parameter {
    public:
        BaseParameter(const char *name, T value);
        int setValueString(const std::string &value) override;
        std::string getValueString() override;

        T getValue();
        virtual int setValue(const T value);
        void setOnChange(void (*fnPtr)());
    
    private:
        T value;
        void (*on_change_function)();
};

#endif