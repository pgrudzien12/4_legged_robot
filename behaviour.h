#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__
#include "robot.h"
#include "logger.h"

class Behaviour
{
protected:
    Behaviour(Logger *logger, Robot *robot)
    {
        this->robot = robot;
        this->logger = logger;
    }

public:
    virtual void update(long timeElapsed) = 0;

private:
    Robot *robot;
    Logger *logger;
};

#endif
