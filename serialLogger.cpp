#include "serialLogger.h"

void SerialLogger::log(const char message[])
{
    Serial.println(message);
}

void SerialLogger::log(const String message)
{
    Serial.println(message);
}