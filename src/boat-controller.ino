/*
 * Project boat-controller
 * Description:
 * Author:
 * Date:
 */

#include <WebSocketsClient.h>

#include "parameter/Parameter.h"
#include "parameter/BaseParameter.h"
#include "parameter/NumParameter.h"

WebSocketsClient webSocket;

BaseParameter<bool> para1("p-bool", true);
BaseParameter<String> para2("p-str", "Hello World!");
NumParameter<int> para3("p-int", 42, -100, 100);
NumParameter<float> para4("p-float", 3.14, -100, 100);

// setup() runs once, when the device is first turned on.
void setup() {
    String str = "test";
    Serial.begin(115200);

    para1.setOnChange(paraChange);
    para2.setOnChange(paraChange);
    para3.setOnChange(paraChange);
    para4.setOnChange(paraChange);

    paraChange();

    Serial.println("Connect ...");

    webSocket.begin("82.165.125.185", 80, "/ws/boat/");
    webSocket.onEvent(webSocketEvent);

    Serial.println("Ready");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            Serial.printf("[WSc] Connected to url: %s\n",  payload);
            break;
        case WStype_TEXT:
            Serial.printf("[WSc] get text: %s\n", payload);
            handleCommand((char*)payload);
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary lenght: %u\n", lenght);
            break;
    }
}

void handleCommand(char * command) {
    String com(command);
    if (com.startsWith("p ") || com.startsWith("parameter ")) {
        com = com.substring(com.indexOf(' ') + 1);
        if (com.startsWith("get ")) {
            com = com.substring(com.indexOf(' ') + 1);
            if (com.equals("all")) {
                const std::map<String, Parameter*> *params = Parameter::getAllParameters();
                for(auto it = params->begin(); it != params->end(); it++) {
                    String text = it->first + ": " + it->second->getValueString();
                    webSocket.sendTXT(text);
                }
            } else {
                String value = Parameter::getParameter(com);
                com = com + ": " + value;
                webSocket.sendTXT(com);
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
                webSocket.sendTXT("OK");
            } else if (rcode == PARAMETER_RCODE_NOT_FOUND) {
                webSocket.sendTXT("Parameter not found");
            } else if (rcode == PARAMETER_RCODE_INVALID_VALUE) {
                webSocket.sendTXT("Invalid value");
            }
        } else if (com.equals("save")) {
            Parameter::saveAll();
            webSocket.sendTXT("OK");
        } else if (com.equals("load")) {
            Parameter::loadAll();
            webSocket.sendTXT("OK");
        }
    }
}

void paraChange() {
    Serial.println("Parameter Changed:");
    const std::map<String, Parameter*> *params = Parameter::getAllParameters();
    for(auto it = params->begin(); it != params->end(); it++) {
        Serial.print(it->first);
        Serial.print(": ");
        Serial.println(it->second->getValueString());
    }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    for(int i = 0; i < 500; i++) {
        webSocket.loop();
        delay(20);
    }
    webSocket.sendTXT("-ping-");
}