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

#include <WebSocketsClient.h>

#include "parameter/BaseParameter.h"
#include "parameter/NumParameter.h"

void setup();
void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght);
void handleCommand(char * command);
void paraChange();
void loop();
#line 13 "c:/Users/Tobias/Documents/Projekte/Solarboat/boat-controller/src/boat-controller.ino"
WebSocketsClient webSocket;

BaseParameter<bool> para1("para-bool", true);
NumParameter<int> para2("para-int", 42);
NumParameter<float> para3("para-float", 3.14);

// setup() runs once, when the device is first turned on.
void setup() {
  String str = "test";
  Serial.begin(115200);

  para1.set_on_change(paraChange);
  para2.set_on_change(paraChange);
  para3.set_on_change(paraChange);

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
      webSocket.sendTXT("Connected");
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
      String value = Parameter::get_parameter(&com);
      com = com + ": " + value;
      webSocket.sendTXT(com);
    } else if (com.startsWith("set ")) {
      com = com.substring(com.indexOf(' ') + 1);
      int index = com.indexOf(' ');
      if (index == -1) {
        return;
      }
      String param = com.substring(0,index);
      String value = com.substring(index + 1);
      Parameter::set_parameter(&param, &value);
      webSocket.sendTXT("OK");
    }
  }
}

void paraChange() {
  Serial.println("Parameter Changed:");
  Serial.print("para-bool: ");
  Serial.println(para1.get_value());
  Serial.print("para-int: ");
  Serial.println(para2.get_value());
  Serial.print("para-float: ");
  Serial.println(para3.get_value());
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    for(int i = 0; i < 500; i++) {
        webSocket.loop();
        delay(20);
    }
    webSocket.sendTXT("ping");
}