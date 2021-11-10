#include "commandParser.h"
#include "server.h"
#include "parameter/Parameter.h"

namespace commandParser {

    Logger parseParamLog("app.parser.param");

    void parseParameter(const String &params) {
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
                parseParamLog.error("Parameter not found: %s", param.c_str());
            } else if (rcode == PARAMETER_RCODE_INVALID_VALUE) {
                parseParamLog.error("Invalid value \"%s\" for parameter \"%s\"", value.c_str(), param.c_str());
            }
        } else if (com.equals("save")) {
            Parameter::saveAll();
            server::sendText("OK");
        } else if (com.equals("load")) {
            Parameter::loadAll();
            server::sendText("OK");
        }
    }

}