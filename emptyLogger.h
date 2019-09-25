#pragma once
#include "logger.h"

class EmptyLogger : public Logger
{
public:
    void log(const char[]) override
    {
    }
    void log(const String) override
    {
    }
};
