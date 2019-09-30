#ifndef __ROBOT_H_
#define __ROBOT_H_
#include "logger.h"
#include "leg.h"

class Robot
{
public:
    Robot(Logger *logger, Leg *leg1, Leg *leg2, Leg *leg3, Leg *leg4)
    {
        this->logger = logger;
        this->leg[0] = leg1;
        this->leg[1] = leg2;
        this->leg[2] = leg3;
        this->leg[3] = leg4;
    }

    void executeStep(long timeElapsed)
    {
        for (int i = 0; i < 4; i++)
            leg[i]->update(timeElapsed);
    }

    void resetServos()
    {
        for (int i = 0; i < 4; i++)
            leg[i]->reset();
    }

    Leg *GetLeg(int i)
    {
        if (i < 1 || i > 4)
        {
            logger->log("wrong leg !!");
            return this->leg[0];
        }
        return this->leg[i - 1];
    }

private:
    Logger *logger;
    Leg *leg[4];
};

#endif // __ROBOT_H_