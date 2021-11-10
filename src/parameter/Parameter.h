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
        virtual int setValueString(const String *value) = 0;
        virtual String getValueString() = 0;

        static int setParameter(const String *name, const String *value);
        static String getParameter(const String *name);
        static const std::map<String, Parameter*>* getAllParameters();

        static void saveAll();
        static void loadAll();

    private:
        static std::map<String, Parameter*> parameters;
};

#endif