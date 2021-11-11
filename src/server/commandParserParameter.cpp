#include "commandParser.h"
#include "server.h"
#include "parameter/Parameter.h"

namespace commandParser {

    Logger parseParamLog("app.parser.param");

    void parseParameter(std::string &params) {
        if (params.rfind("get ", 0) == 0) {
            params.erase(0, params.find(' ') + 1);
            if (params == "all") {
                const std::map<std::string, Parameter*> *params = Parameter::getAllParameters();
                for(auto it = params->begin(); it != params->end(); it++) {
                    std::string text = it->first + ": " + it->second->getValueString();
                    server::sendText(text);
                }
            } else {
                std::string value = Parameter::getParameter(params);
                params += ": " + value;
                server::sendText(params);
            }      
        } else if (params.rfind("set ", 0) == 0) {
            params.erase(0, params.find(' ') + 1);
            std::size_t index = params.find(' ');
            if (index == std::string::npos) {
                return;
            }
            std::string param = params.substr(0,index);
            std::string value = params.substr(index + 1);
            int rcode = Parameter::setParameter(param, value);
            if (rcode == PARAMETER_RCODE_OK) {
                server::sendText("OK");
            } else if (rcode == PARAMETER_RCODE_NOT_FOUND) {
                parseParamLog.error("Parameter not found: %s", param.c_str());
            } else if (rcode == PARAMETER_RCODE_INVALID_VALUE) {
                parseParamLog.error("Invalid value \"%s\" for parameter \"%s\"", value.c_str(), param.c_str());
            }
        } else if (params == "save") {
            Parameter::saveAll();
            server::sendText("OK");
        } else if (params == "load") {
            Parameter::loadAll();
            server::sendText("OK");
        }
    }

}