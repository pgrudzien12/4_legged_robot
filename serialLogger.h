#pragma once
#include "logger.h"
#include "USBAPI.h"

extern Serial_ Serial;

class SerialLogger : public Logger
{
public:
    void log(const char message[]) override;
    void log(const String message) override;
};
