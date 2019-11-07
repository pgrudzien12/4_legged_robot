#ifndef __CALCULATORBEHAVIOUR_H_
#define __CALCULATORBEHAVIOUR_H_
#include "../behaviour.h"
#include "../hidMessage.h"

class CalculatorBehaviour : public Behaviour
{
public:
    CalculatorBehaviour(Logger *logger, Robot *robot)
        : Behaviour(logger, robot)
    {
    }

    bool inServoRange(float angle)
    {
        return angle > 0 and angle < 3.14;
    }

    void IK(float x, float y, float *q1_out, float *q2_out)
    {
        const float tibia = 6.2;
        const float tarsus = 7;

        // tak a note that this is a different reference system (for x,y) than in calcAngles
        float L1 = tibia;
        float L2 = tarsus;

        float q2_up = x * x + y * y - L1 * L1 - L2 * L2;
        float q2_down = 2 * L1 * L2;
        float q2 = acos(q2_up / q2_down);

        float q1_up = L2 * sin(q2);
        float q1_down = sqrt(x * x + y * y);
        float q1 = atan(y / x) - asin(q1_up / q1_down);

        (*q1_out) = q1 - PI / 4;
        (*q2_out) = q2 - PI / 4;
    }

    void calcAngles(float *result)
    {
        // const float F[3] = {6.28198052, 6.28198052, 11.38406204};
        float x = result[0] + 6.28198052f;
        float y = result[1] + 6.28198052f;
        float z = result[2] + 11.38406204f;
        const float femur = 4.5;

        float alpha = atan(x / y);
        float w = sqrt(x * x + y * y);
        float mi = w - femur;

        float q1, q2;
        IK(mi, z, &q1, &q2);

        result[0] = q2 * RAD_TO_DEG;
        result[1] = q1 * RAD_TO_DEG;
        result[2] = (alpha - PI / 4) * RAD_TO_DEG;
    }

    void update(long) override
    {
    }

    void onMessage(HidMessage message)
    {
        String logMessage;
        logMessage += message.isUpPressed();
        logMessage += message.isDownPressed();
        logMessage += message.isLeftPressed();
        logMessage += message.isRightPressed();
        logMessage += message.isCtrlPressed();
        logMessage += message.isShiftPressed();
        logMessage += message.isAltPressed();
        logMessage += " C:";
        logMessage += message.isCorrectMessage();
        logMessage += " ";
        logMessage += message.noArrowPressed();
        logMessage += " Axis=(";
        logMessage += message.getX();
        logMessage += ", ";
        logMessage += message.getY();
        logMessage += ")";
        logMessage += " Rotation=(";
        logMessage += message.getRotationX();
        logMessage += ", ";
        logMessage += message.getRotationY();
        logMessage += ") ";
        float X = (message.getRotationX() - 64);
        float Y = (message.getRotationY() - 64);
        float Z = -(message.getY() - 64);
        if (X != 0)
            X = X / 64.f;
        if (Y != 0)
            Y = Y / 64.f;
        if (Z != 0)
            Z = Z / 64.f;
        float F[3] = { 6.28198052 * X,  6.28198052 * Y, 3*Z };

        logMessage += " F=(";
        logMessage += F[0];
        logMessage += ", ";
        logMessage += F[1];
        logMessage += ", ";
        logMessage += F[2];
        logMessage += ") ";
        //float F[3] = {0, 0, 0};
        calcAngles(F);

        logMessage += " Leg1=(";
        logMessage += F[0];
        logMessage += ", ";
        logMessage += F[1];
        logMessage += ", ";
        logMessage += F[2];
        logMessage += ") ";

        logger->log(logMessage);
    }
};

#endif // __CALCULATORBEHAVIOUR_H_