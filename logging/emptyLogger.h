#ifndef __EMPTYLOGGER_H_
#define __EMPTYLOGGER_H_

#include "../logger.h"

class EmptyLogger : public Logger
{
public:
    void log(const char[]) override
    {
    }
    void log(const String) override
    {
    }
    void log(const bool) override
    {
    }
};

#endif