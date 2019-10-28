#ifndef __BALANCE_H
#define __BALANCE_H
#include "../behaviour.h"

class BalanceDemoBehaviour : public Behaviour
{
public:
    BalanceDemoBehaviour(Logger *logger, Robot *robot)
        : Behaviour(logger, robot)
    {
    }

public:
    void update(long timeElapsed) override
    {
        timeElapsedInStage += timeElapsed;
        //setBalanceForward();
        if (stage == 0)
        {
            setStablePose();
            stage = 1;
            timeElapsedInStage = 0;
        }
        else if (stage == 1)
        {
            if (timeElapsedInStage >= 2500)
            {
                stage = 2;
                timeElapsedInStage = 0;
                setBalanceForward();
                setSpeetTTF(0.2);
            }
        }
        else if (stage == 2)
        {
            if (timeElapsedInStage >= 5000 && gotDesiredPose())
            {
                stage = 3;
                timeElapsedInStage = 0;
                setStablePose();
                setSpeetTTF(0.5);
            }
        }
        else if (stage == 3)
        {
            if (timeElapsedInStage >= 2500)
            {
                stage = 4;
                timeElapsedInStage = 0;
                setBalanceBackwards();
                setSpeetTTF(0.2);
            }
        }
        else if (stage == 4)
        {
            if (timeElapsedInStage >= 2500 && gotDesiredPose())
            {
                stage = 5;
                timeElapsedInStage = 0;
                setStablePose();
                setSpeetTTF(0.5);
            }
        }
        else if (stage == 5)
        {
            if (timeElapsedInStage >= 2500 && gotDesiredPose())
            {
                stage = 6;
                timeElapsedInStage = 0;
                setBalanceDown();
                setSpeetTTF(0.8);
            }
        }
        else if (stage == 6)
        {
            if (timeElapsedInStage >= 2500 && gotDesiredPose())
            {
                stage = 1;
                timeElapsedInStage = 0;
                setStablePose();
                setSpeetTTF(0.3);
            }
        }
    }

private: // data
    int stage = 0;
    long timeElapsedInStage = 0;
};

#endif // __BALANCE_H