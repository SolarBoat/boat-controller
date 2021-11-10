/*
 * Project boat-controller
 * Description:
 * Author:
 * Date:
 */
#include "parameter/Parameter.h"
#include "parameter/BaseParameter.h"
#include "parameter/NumParameter.h"
#include "server/server.h"


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

    server::begin();

    Serial.println("Ready");
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
        server::loop();
        delay(20);
    }
    server::sendText("-ping-");
}