#ifndef __BALANCE_H
#define __BALANCE_H
#include "../behaviour.h"

class BalanceBehaviour : public Behaviour
{
public:
    BalanceBehaviour(Logger *logger, Robot *robot)
        : Behaviour(logger, robot)
    {
    }

    void update(long timeElapsed) override
    {
        timeElapsedInStage += timeElapsed;
        if (stage == 0)
        {
            setStablePose();
            stage = 1 timeElapsedInStage = 0;
        }
        else if (stage == 1)
        {
            if (timeElapsedInStage >= 100)
            {
                stage = 2;
                timeElapsedInStage = 0;
                setBalanceForward();
            }
        }
        else if (stage == 2)
        {
            if (gotDesiredPose())
            {
                stage = 3;
                timeElapsedInStage = 0;
            }
        }
    }

private: // functions
    void setStablePose()
    {
        robot->GetLeg(1)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(2)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(3)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(4)->setDesiredAngles(90, 90, 90);
    }

    void setBalanceOnLegPose(int leg)
    {
        robot->GetLeg(1)->setDesiredAngles(60, 120, 60);
        robot->GetLeg(2)->setDesiredAngles(90, 60, 90);
        robot->GetLeg(3)->setDesiredAngles(110, 90, 90);
        robot->GetLeg(4)->setDesiredAngles(90, 90, 120);
    }

    void gotDesiredPose(int leg)
    {
    }

private: // data
    int stage = 0;
    long timeElapsedInStage = 0;
};

#endif // __BALANCE_H