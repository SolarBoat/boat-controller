/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Tobias/Documents/Projekte/Solarboat/boat-controller/src/boat-controller.ino"
/*
 * Project boat-controller
 * Description:
 * Author:
 * Date:
 */

#include "parameter/BaseParameter.h"
#include "parameter/NumParameter.h"

void setup();
void paraChange();
void loop();
#line 11 "c:/Users/Tobias/Documents/Projekte/Solarboat/boat-controller/src/boat-controller.ino"
BaseParameter<bool> para1("Para1", true);
NumParameter<int> para2("Para2", 42);
NumParameter<float> para3("Para3", 3.14);

// setup() runs once, when the device is first turned on.
void setup() {
  String str = "test";
  Serial.begin(115200);

  para1.set_on_change(paraChange);
  para2.set_on_change(paraChange);
  para3.set_on_change(paraChange);

  paraChange();
}

void paraChange() {
  Serial.println("Parameter Changed:");
  Serial.print("Para1: ");
  Serial.println(para1.get_value());
  Serial.print("Para2: ");
  Serial.println(para2.get_value());
  Serial.print("Para3: ");
  Serial.println(para3.get_value());
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  String p("Para2");
  String v1("42");
  String v2("12");
  Parameter::set_parameter(&p, &v2);
  Serial.print("Result: ");
  Serial.println(Parameter::get_parameter(&p));
  delay(1000);
  Parameter::set_parameter(&p, &v1);  
  Serial.print("Result: ");
  Serial.println(Parameter::get_parameter(&p));
  delay(1000);
}