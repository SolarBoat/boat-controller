#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <Particle.h>
#include <string>
#include <map>

#define PARAMETER_RCODE_OK 1
#define PARAMETER_RCODE_NOT_FOUND -1
#define PARAMETER_RCODE_INVALID_VALUE -2

class Parameter {
    public:
        Parameter(const char *name);
        virtual int setValueString(const std::string &value) = 0;
        virtual std::string getValueString() = 0;

        static int setParameter(const std::string &name, const std::string &value);
        static std::string getParameter(const std::string &name);
        static const std::map<std::string, Parameter*>* getAllParameters();

        static void saveAll();
        static void loadAll();

    private:
        static std::map<std::string, Parameter*> &allParameters();
};

#endif