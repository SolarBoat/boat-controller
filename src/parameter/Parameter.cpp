#include "Parameter.h"
#include <fcntl.h>

std::map<String, Parameter*> Parameter::parameters;

Parameter::Parameter(const char *name) {
    parameters.insert(std::pair<String, Parameter*>(String(name), this));
}

int Parameter::setParameter(const String *name, const String *value) { 
    auto search = parameters.find(*name);
    if (search != parameters.end()) {
        return parameters[*name]->setValueString(value);
    } else {
        return PARAMETER_RCODE_NOT_FOUND;
    }
}

String Parameter::getParameter(const String *name) { 
    auto search = parameters.find(*name);
    if (search != parameters.end()) {
        return parameters[*name]->getValueString();
    } else {
        return String("NP");
    }
}

const std::map<String, Parameter*>* Parameter::getAllParameters() { 
    return &parameters;
}

void Parameter::saveAll() {
    int fd = open("parameter.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        Serial.println("unable to open file parameters.txt");
        return;
    }
    for(auto it = parameters.begin(); it != parameters.end(); it++) {
        String text = it->first + ":" + it->second->getValueString() + "\n";
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
                String text = String(buffer + bufferOffset);
                int seperator = text.indexOf(':');
                String name = text.substring(0, seperator);
                String value = text.substring(seperator + 1);
                setParameter(&name, &value);
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