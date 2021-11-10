#include "commandParser.h"
#include "server.h"
#include "parameter/Parameter.h"

void handleCommand(const String &params) {
    Serial.println(params);
    String com = params;
    if (com.startsWith("get ")) {
        com = com.substring(com.indexOf(' ') + 1);
        if (com.equals("all")) {
            const std::map<String, Parameter*> *params = Parameter::getAllParameters();
            for(auto it = params->begin(); it != params->end(); it++) {
                String text = it->first + ": " + it->second->getValueString();
                server::sendText(text);
            }
        } else {
            String value = Parameter::getParameter(com);
            com = com + ": " + value;
            server::sendText(com);
        }      
    } else if (com.startsWith("set ")) {
        com = com.substring(com.indexOf(' ') + 1);
        int index = com.indexOf(' ');
        if (index == -1) {
            return;
        }
        String param = com.substring(0,index);
        String value = com.substring(index + 1);
        int rcode = Parameter::setParameter(param, value);
        if (rcode == PARAMETER_RCODE_OK) {
            server::sendText("OK");
        } else if (rcode == PARAMETER_RCODE_NOT_FOUND) {
            server::sendText("Parameter not found");
        } else if (rcode == PARAMETER_RCODE_INVALID_VALUE) {
            server::sendText("Invalid value");
        }
    } else if (com.equals("save")) {
        Parameter::saveAll();
        server::sendText("OK");
    } else if (com.equals("load")) {
        Parameter::loadAll();
        server::sendText("OK");
    }
}