#include "Parameter.h"

std::map<String, Parameter*> Parameter::parameters;

Parameter::Parameter(const char *name) {
    parameters.insert(std::pair<String, Parameter*>(String(name), this));
}

void Parameter::set_parameter(const String *name, const String *value) { 
    auto search = parameters.find(*name);
    if (search != parameters.end()) {
        parameters[*name]->set_value_string(value);
    }
}

String Parameter::get_parameter(const String *name) { 
    auto search = parameters.find(*name);
    if (search != parameters.end()) {
        return parameters[*name]->get_value_string();
    } else {
        return String("NP");
    }
}

const std::map<String, Parameter*>* Parameter::get_all_parameters() { 
    return &parameters;
}