#ifndef __BALANCEMESSAGEINTERPRETER_H__
#define __BALANCEMESSAGEINTERPRETER_H__

#include "../messageInterpreter.h"
#include "balance.h"
#include "balanceMessage.h"

class BalanceMessageInterpreter
{
private:
    void (*ptr)(BalanceMessage *);
public:
    BalanceMessageInterpreter(void (*ptr)(BalanceMessage *));
    ~BalanceMessageInterpreter();
};

BalanceMessageInterpreter::BalanceMessageInterpreter(void (*ptr)(BalanceMessage *))
{
    this->ptr = ptr;
}

BalanceMessageInterpreter::~BalanceMessageInterpreter()
{
}

#endif