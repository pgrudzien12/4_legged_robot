#pragma once
#include "WString.h"

class Logger
{
public:
    virtual void log(const char message[]) = 0; 
    virtual void log(const String message) = 0; 
};
