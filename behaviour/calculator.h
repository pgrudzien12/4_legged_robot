#ifndef __CALCULATORBEHAVIOUR_H_
#define __CALCULATORBEHAVIOUR_H_
#include "../behaviour.h"
#include "../hidMessage.h"
#include "../balanceCalculator.h"

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
        float X = (message.getX() - 64);
        float Y = -(message.getY() - 64);
        float Z = (message.getRotationY() - 64);
        if (X != 0)
            X = X / 64.f;
        if (Y != 0)
            Y = Y / 64.f;
        if (Z != 0)
            Z = Z / 64.f;
        BalanceCalculator calc(6.28198052, 6.28198052, 3);
        BalanceResult balance = calc.calculate(X, Y, Z);
        if (balance.isCorrect())
            balance.setBalance(this->robot);

        logMessage += " leg1=(";
        logMessage += balance.leg1[0];
        logMessage += ", ";
        logMessage += balance.leg1[1];
        logMessage += ", ";
        logMessage += balance.leg1[2];
        logMessage += ") ";
        //float F[3] = {0, 0, 0};

        logMessage += " Leg2=(";
        logMessage += balance.leg2[0];
        logMessage += ", ";
        logMessage += balance.leg2[1];
        logMessage += ", ";
        logMessage += balance.leg2[2];
        logMessage += ") ";

        logger->log(logMessage);
    }
};

#endif // __CALCULATORBEHAVIOUR_H_