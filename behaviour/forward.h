#ifndef __FORWARD_H_
#define __FORWARD_H_
#include "../behaviour.h"
#include "../robot.h"
#include "../logger.h"

class ForwardBehaviour : public Behaviour
{
public:
    ForwardBehaviour(Logger *logger, Robot *robot) 
        : Behaviour(logger, robot)
    {
    }

    void update(long ) override
    {

    }
};

#endif // __FORWARD_H_