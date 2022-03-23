/*
 * Project boat-controller
 * Description:
 * Author:
 * Date:
 */

#include "sensorController/sensorController.h"


#include "parameter/Parameter.h"
#include "parameter/BaseParameter.h"
#include "parameter/NumParameter.h"
#include "channel/BaseChannel.h"
#include "server/server.h"
#include <string>

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

BaseParameter<bool> para1("p-bool", true);
BaseParameter<std::string> para2("p-str", "Hello World!");
NumParameter<int> para3("p-int", 42, -100, 100);
NumParameter<float> para4("p-float", 3.14, -100, 100);

BaseChannel<int> &channel = BaseChannel<int>::get("test_i");

SerialLogHandler logHandler(LOG_LEVEL_INFO);


// setup() runs once, when the device is first turned on.
void setup() {

    
    SystemPowerConfiguration conf;
    conf.powerSourceMaxCurrent(3000);
    conf.feature(SystemPowerFeature::USE_VIN_SETTINGS_WITH_USB_HOST);
    int res = System.setPowerConfiguration(conf);
    Log.info("setPowerConfiguration=%d", res);
    
    Serial.begin(115200);

    para1.setOnChange(paraChange);
    para2.setOnChange(paraChange);
    para3.setOnChange(paraChange);
    para4.setOnChange(paraChange);

    paraChange();

    server::begin();
    
    sensorController::begin();
    Particle.connect();
    
}

void paraChange() {
    Serial.println("Parameter Changed:");
    const std::map<std::string, Parameter*> *params = Parameter::getAllParameters();
    for(auto it = params->begin(); it != params->end(); it++) {
        Serial.print(it->first.c_str());
        Serial.print(": ");
        Serial.println(it->second->getValueString().c_str());
    }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    static int i = 0;
    i++;
    if(i >= 100) {
        i = 0;
        server::sendText("-ping-");
    }
    server::loop();
    delay(100);
}