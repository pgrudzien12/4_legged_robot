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

private: // functions
    void setStablePose()
    {
        robot->GetLeg(1)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(2)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(3)->setDesiredAngles(90, 90, 90);
        robot->GetLeg(4)->setDesiredAngles(90, 90, 90);
    }

    void setBalanceForward()
    {
        robot->GetLeg(1)->setDesiredAngles(60, 120, 60);
        robot->GetLeg(2)->setDesiredAngles(90, 60, 90);
        robot->GetLeg(3)->setDesiredAngles(110, 90, 90);
        robot->GetLeg(4)->setDesiredAngles(90, 90, 120);
    }

    bool gotDesiredPose()
    {
        for (int i = 0; i < 4; i++)
        {
            if (!robot->GetLeg(i+1)->gotDesiredAngles())
                return false;
        }

        return true;
    }

    bool inServoRange(float angle)
    {
        return angle > 0 and angle < 3.14;
    }

    void IK(float x, float y, float *q1_out, float *q2_out)
    {
        // tak a note that this is a different reference system (for x,y) than in calcAngles 
        const float calf = 7;
        const float thigh = 6.2;
        float L1 = thigh;
        float L2 = calf;
        float q2_up = x * x + y * y - L1 * L1 - L2 * L2;
        float q2_down = 2 * L1 * L2;
        float q2 = acos(q2_up / q2_down);

        float q1_up = L2 * sin(q2);
        float q1_down = sqrt(x * x + y * y);
        float q1 = atan(y / x) - asin(q1_up / q1_down);

        if (inServoRange(q1 + PI / 4) && inServoRange(q2 + PI / 4))
        {
            (*q1_out) = q1 + PI / 4;
            (*q2_out) = q2 + PI / 4;
            return;
        }
        else
        {
            float q2_sol2 = 2 * PI - q2;

            q1_up = L2 * sin(q2_sol2);

            (*q1_out) = atan(y / x) - asin(q1_up / q1_down) + PI / 4;
            (*q2_out) = q2_sol2 + PI / 4;
            return;
        }
    }

    float* calcAngles(float x, float y, float z)
    {
        const float hip = 4.5;

        float alpha = atan(x / y);
        float w = sqrt(x * x + y * y);
        float mi = w - hip;
        float q1, q2;
        IK(mi, z, &q1, &q2);

        float *result = new float[3];
        result[0] = (alpha + PI / 4) * RAD_TO_DEG;
        result[1] = q1 * RAD_TO_DEG;
        result[2] = q2 * RAD_TO_DEG;
        return result;
    }
public:
    void update(long timeElapsed) override
    {
        timeElapsedInStage += timeElapsed;
        if (stage == 0)
        {
            setStablePose();
            stage = 1;
            timeElapsedInStage = 0;
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

private: // data
    int stage = 0;
    long timeElapsedInStage = 0;
};

#endif // __BALANCE_H