#include "server.h"
#include <WebSocketsClient.h>
#include <map>
#include "commandParser.h"

#define SERVER_

namespace server {

    namespace {
        const String SERVER_IP = "82.165.125.185";
        const int SERVER_PORT = 80;
        const String WEBSOCKET_URL = "/ws/boat/";

        WebSocketsClient webSocket;

        std::map<String,void (*)(const String &command)> commandParsers;

        void handleCommand(const char *text) {
            String str(text);
            int seperator = str.indexOf(' ');
            String name = seperator == -1 ? str : str.substring(0, seperator);
            auto command = commandParsers.find(name);
            if (command == commandParsers.end()) {
                sendText("Command not found");
                return;
            }
            String params = seperator == -1 ? "" : str.substring(seperator + 1);
            command->second(params);
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

        void addCommandParser(void (*fnPtr)(const String &params), const String &command) {
            commandParsers[command] = fnPtr;
        }

    }

    void begin() {
        webSocket.begin(SERVER_IP, SERVER_PORT, WEBSOCKET_URL);
        webSocket.onEvent(webSocketEvent);

        addCommandParser(commandParser::parseParameter, "p");
        addCommandParser(commandParser::parseParameter, "parameter");
    }

    void loop() {
        webSocket.loop();
    }

    void sendText(const String &text) {
        webSocket.sendTXT(text);
    }

    void sendText(const char *text) {
        webSocket.sendTXT(text);
    }

}