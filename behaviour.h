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
        float q1, q2, q3;
        q1 = 54;
        q2 = -21;
        q3 = 45;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = -13;
        q2 = -21;
        q3 = -18;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
    }

    void setBalanceForwardLeft()
    {
        float q1, q2, q3;
        q1 = 56;
        q2 = -10;
        q3 = 0;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 37;
        q2 = -32;
        q3 = 26;
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = 2;
        q2 = -26;
        q3 = 0;
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 37;
        q2 = -32;
        q3 = -26;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
    }

    void setBalanceForwardRight()
    {
        float q1, q2, q3;
        q1 = 37;
        q2 = -32;
        q3 = 26;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 56;
        q2 = -10;
        q3 = 0;
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = 37;
        q2 = -32;
        q3 = -26;
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 2;
        q2 = -26;
        q3 = 0;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
    }

    void setBalanceBackwards()
    {
        float q1, q2, q3;
        q1 = -13;
        q2 = -21;
        q3 = -18;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = 54;
        q2 = -21;
        q3 = 45;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);
    }
    void setBalanceBackwardsLeft()
    {
        // calc angles for [3.18198052 9.38198052 8.38406204]
        // leg1=[ 37. -32. -26.]
        // calc angles for [9.38198052 9.38198052 8.38406204]
        // leg4=[  2. -26.   0.]
        // calc angles for [9.38198052 3.18198052 8.38406204]
        // leg3=[ 37. -32.  26.]
        // calc angles for [3.18198052 3.18198052 8.38406204]
        // leg2=[ 56. -10.   0.]

        float q1, q2, q3;
        q1 = 37;
        q2 = -32;
        q3 = -26;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 2;
        q2 = -26;
        q3 = 0;
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = 37;
        q2 = -32;
        q3 = 26;
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 56;
        q2 = -10;
        q3 = 0;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
    }

    void setBalanceBackwardsRight()
    {
        // calc angles for [9.38198052 9.38198052 8.38406204]
        // leg1=[  2. -26.   0.]
        // calc angles for [3.18198052 9.38198052 8.38406204]
        // leg4=[ 37. -32. -26.]
        // calc angles for [3.18198052 3.18198052 8.38406204]
        // leg3=[ 56. -10.   0.]
        // calc angles for [9.38198052 3.18198052 8.38406204]
        // leg2=[ 37. -32.  26.]

        float q1, q2, q3;
        q1 = 2;
        q2 = -26;
        q3 = 0;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 37;
        q2 = -32;
        q3 = -26;
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = 56;
        q2 = -10;
        q3 = 0;
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 37;
        q2 = -32;
        q3 = 26;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
    }
    
    void setBalanceLeft()
    {
        float q1, q2, q3;
        q1 = 54;
        q2 = -21;
        q3 = -45;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 54;
        q2 = -21;
        q3 = -45;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = -14;
        q2 = -20;
        q3 = 18;
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = -14;
        q2 = -20;
        q3 = 18;
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
    }

    void setBalanceRight()
    {
        float q1, q2, q3;
        q1 = -14;
        q2 = -20;
        q3 = 18;
        robot->GetLeg(1)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = -14;
        q2 = -20;
        q3 = 18;
        robot->GetLeg(2)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);

        q1 = 54;
        q2 = -21;
        q3 = -45;
        robot->GetLeg(3)->setDesiredAngles(90 - q1, 90 + q2, 90 + q3);

        q1 = 54;
        q2 = -21;
        q3 = -45;
        robot->GetLeg(4)->setDesiredAngles(90 + q1, 90 - q2, 90 - q3);
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
