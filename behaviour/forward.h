#ifndef __FORWARD_H_
#define __FORWARD_H_
#include "../behaviour.h"
#include "../robot.h"

class Forward : public Behaviour
{
public:
    Forward(Robot *robot)
    {
        this->robot = robot;
    }

    void update(long timeElapsed) override
    {
    }

private:
    Robot *robot;
};

#endif // __FORWARD_H_