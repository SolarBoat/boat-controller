#ifndef SERVER_LOG_HANDLER_H_
#define SERVER_LOG_HANDLER_H_

#include <Particle.h>

// library implementation in wiring\inc\spark_wiring\logging.h

class ServerLogHandler : public LogHandler {
    public:
        ServerLogHandler(LogLevel level = LOG_LEVEL_INFO);
        ServerLogHandler(LogLevel level, LogCategoryFilters filters);

        ~ServerLogHandler();

        void logMessage(const char *msg, LogLevel level, const char *category, const LogAttributes &attr) override;
};

#endif