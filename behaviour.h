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

    void setStablePose()
    {
        robot->GetLeg(1)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(2)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(3)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(4)->setDesiredAngles(90, 90, 90);
    }

    void setBalanceForward()
    {
        float q1 = 52;
        float q2 = -25;
        float q3 = 17;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = 26;
        q2 = -32;
        q3 = -11;
        robot->GetLeg(2)->setDesiredAngles(90 - q1, 90 - q2, 90 - q3);
        robot->GetLeg(3)->setDesiredAngles(90 + q1, 90 + q2, 90 + q3);
    }

    void setBalanceBackwards()
    {
        float q1, q2, q3;
        q1 = 26;
        q2 = -32;
        q3 = -11;
        robot->GetLeg(1)->setDesiredAngles(90 + q1, 90 + q2, 90 + q3);
        robot->GetLeg(4)->setDesiredAngles(90 - q1, 90 - q2, 90 - q3);

        q1 = 52;
        q2 = -25;
        q3 = 17;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
    }

    void setBalanceDown()
    {
        float q1, q2, q3;
        q1 = 86;
        q2 = -80;
        q3 = 0;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
    }

    
    void setBalanceUp()
    {
        float q1, q2, q3;
        q1 = -45;
        q2 = 45;
        q3 = 0;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
    }

    bool gotDesiredPose()
    {
        for (int i = 0; i < 4; i++)
        {
            if (!robot->GetLeg(i + 1)->gotDesiredAngles())
                return false;
        }

        return true;
    }

    void setSpeetTTF(float ttf)
    {
        for (int i = 1; i <= 4; i++)
        {
            robot->GetLeg(i)->setSpeedTTF(ttf);
        }
    }

public:
    virtual void update(long timeElapsed) = 0;

protected:
    Robot *robot;
    Logger *logger;
};

#endif
