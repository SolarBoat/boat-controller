#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <Particle.h>
#include <map>

#define PARAMETER_RCODE_OK 1
#define PARAMETER_RCODE_NOT_FOUND -1
#define PARAMETER_RCODE_INVALID_VALUE -2

class Parameter {
    public:
        Parameter(const char *name);
        virtual int set_value_string(const String *value) = 0;
        virtual String get_value_string() = 0;

        static int set_parameter(const String *name, const String *value);
        static String get_parameter(const String *name);
        static const std::map<String, Parameter*>* get_all_parameters();

        static void save_all();
        static void load_all();

    private:
        static std::map<String, Parameter*> parameters;
};

#endif