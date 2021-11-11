#ifndef SERVER_H_
#define SERVER_H_

#include <string>

namespace server {

    void begin();
    void loop();

    void sendText(const std::string &text);
    void sendText(const char *text);

}

#endif