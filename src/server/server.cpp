#include "server.h"
#include <Particle.h>
#include <WebSocketsClient.h>
#include <map>
#include "commandParser.h"
#include "serverLogHandler.h"

#define SERVER_

namespace server {

    namespace {
        const String SERVER_IP = "82.165.125.185";
        const int SERVER_PORT = 80;
        const String WEBSOCKET_URL = "/ws/boat/";

        ServerLogHandler logHandler(LOG_LEVEL_ERROR);
        Logger log("app.server");

        WebSocketsClient webSocket;

        std::map<std::string,void (*)(std::string &command)> commandParsers;

        void handleCommand(const char *text) {
            std::string str(text);
            int seperator = str.find(' ');
            std::string name = seperator == -1 ? str : str.substr(0, seperator);
            auto command = commandParsers.find(name);
            if (command == commandParsers.end()) {
                log.error("Command not found: %s", name.c_str());
                return;
            }
            std::string params = seperator == -1 ? "" : str.substr(seperator + 1);
            command->second(params);
        }

        void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
            switch(type) {
                case WStype_DISCONNECTED:
                    log.info("Websocket disconnected.");
                    break;
                case WStype_CONNECTED:
                    log.info("Websocket connected to url: %s", payload);
                    break;
                case WStype_TEXT:
                    log.info("Websocket get command: %s", payload);
                    handleCommand((char*)payload);
                    break;
                case WStype_BIN:
                    log.info("Websocket get binary length: %u", length);
                    break;
            }
        }

        void addCommandParser(void (*fnPtr)(std::string &params), const std::string &command) {
            commandParsers[command] = fnPtr;
        }

    }

    void begin() {
        webSocket.begin(SERVER_IP, SERVER_PORT, WEBSOCKET_URL);
        webSocket.onEvent(webSocketEvent);

        addCommandParser(commandParser::parseParameter, "p");
        addCommandParser(commandParser::parseParameter, "parameter");
        
        addCommandParser(commandParser::parseChannel, "c");
        addCommandParser(commandParser::parseChannel, "channel");
    }

    void loop() {
        webSocket.loop();
    }

    void sendText(const std::string &text) {
        webSocket.sendTXT(text.c_str());
    }

    void sendText(const char *text) {
        webSocket.sendTXT(text);
    }

}