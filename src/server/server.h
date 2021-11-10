#ifndef SERVER_H_
#define SERVER_H_

#include <Particle.h>

namespace server {

    void begin();
    void loop();

    void sendText(const String &text);
    void sendText(const char *text);

}

#endif