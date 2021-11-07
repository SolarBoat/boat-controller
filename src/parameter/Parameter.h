#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <Particle.h>
#include <map>

class Parameter {
    public:
        Parameter(const char *name);
        virtual void set_value_string(const String *value) = 0;
        virtual String get_value_string() = 0;

        static void set_parameter(const String *name, const String *value);
        static String get_parameter(const String *name);
        static const std::map<String, Parameter*>* get_all_parameters();

        static void save_all();
        static void load_all();

    private:
        static std::map<String, Parameter*> parameters;
};

#endif