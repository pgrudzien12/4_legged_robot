#ifndef __DEFAULTMESSAGEINTERPRETER_H_
#define __DEFAULTMESSAGEINTERPRETER_H_
#include "../messageInterpreter.h"

class DefaultMessageInterpreter : public MessageInterpreter
{
public:
    bool interpret(int) override
    {
    }
};

#endif