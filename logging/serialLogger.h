#ifndef __SERIALLOGGER_H_
#define __SERIALLOGGER_H_
#include "../logger.h"
#include "USBAPI.h"

extern Serial_ Serial;

class SerialLogger : public Logger
{
public:
    void log(const char message[]) override
    {
        Serial.println(message);
    }

    void log(const String message) override
    {
        Serial.println(message);
    }
};

#endif
