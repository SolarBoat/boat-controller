#include "serverLogHandler.h"
#include "server.h"
#include <sstream>
#include <string>

ServerLogHandler::ServerLogHandler(LogLevel level) : LogHandler(level) {
    LogManager::instance()->addHandler(this);
}
        
ServerLogHandler::ServerLogHandler(LogLevel level, LogCategoryFilters filters) : LogHandler(level, filters) {
    LogManager::instance()->addHandler(this);
}

ServerLogHandler::~ServerLogHandler() {
    LogManager::instance()->removeHandler(this);
}

void ServerLogHandler::logMessage(const char *msg, LogLevel level, const char *category, const LogAttributes &attr) {
    std::stringstream ss;
    ss << "{\"log\":{\"msg\":\"" << msg << "\"";
    ss << ",\"level\":\"" << levelName(level) << "\"";
    ss << ",\"category\":\"" << category << "\"";
    ss << "}}";
    server::sendText(ss.str().c_str());
}