#include "Parameter.h"
#include <fcntl.h>

std::map<std::string, Parameter*> &Parameter::allParameters() {
    static std::map<std::string, Parameter*> parameters;
    return parameters;
}

Parameter::Parameter(const char *name) {
    allParameters().insert(std::pair<std::string, Parameter*>(std::string(name), this));
    Log.info("Added parameter: %s", name);
}

int Parameter::setParameter(const std::string &name, const std::string &value) { 
    std::map<std::string, Parameter*> &parameters = allParameters();
    auto search = parameters.find(name);
    if (search != parameters.end()) {
        return parameters[name]->setValueString(value);
    } else {
        return PARAMETER_RCODE_NOT_FOUND;
    }
}

std::string Parameter::getParameter(const std::string &name) { 
    std::map<std::string, Parameter*> &parameters = allParameters();
    auto search = parameters.find(name);
    if (search != parameters.end()) {
        return parameters[name]->getValueString();
    } else {
        return "NP";
    }
}

const std::map<std::string, Parameter*>* Parameter::getAllParameters() {
    return &allParameters();
}

void Parameter::saveAll() {
    int fd = open("parameter.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        Serial.println("unable to open file parameters.txt");
        return;
    }
    std::map<std::string, Parameter*> &parameters = allParameters();
    for(auto it = parameters.begin(); it != parameters.end(); it++) {
        std::string text = it->first + ":" + it->second->getValueString() + "\n";
        write(fd, text.c_str(), text.length());
    }
    close(fd);
}

void Parameter::loadAll() {
    int fd = open("parameter.txt", O_RDONLY);
    if (fd == -1) {
        Serial.println("unable to open file parameters.txt");
        return;
    }
    int position = 0;
    char buffer[64];  
    int readBytes = read(fd, buffer, 20);
    while (readBytes > 0) {
        int bufferOffset = 0;
        for (int i = 0; i < readBytes; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = 0;
                std::string text = std::string(buffer + bufferOffset);
                int seperator = text.find(':');
                std::string name = text.substr(0, seperator);
                std::string value = text.substr(seperator + 1);
                setParameter(name, value);
                bufferOffset = i + 1;
            }
        }
        if (bufferOffset == 0) {
            Serial.println("Parameter read buffer to small");
            break;
        }
        position += bufferOffset;
        lseek(fd, position, SEEK_SET);
        readBytes = read(fd, buffer, 20);
    } 
    close(fd);
}