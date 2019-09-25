#ifndef __BOREDROBOT_H__
#define __BOREDROBOT_H__
#include "controller.h"
#include "leg.h"
#include "logger.h"

class BoredRobot : public Controller
{
public:
    BoredRobot(Logger *logger, Leg *leg1, Leg *leg2, Leg *leg3, Leg *leg4)
    {
        this->logger = logger;
        this->leg1 = leg1;
        this->leg2 = leg2;
        this->leg3 = leg3;
        this->leg4 = leg4;
    }

    void update(long timeElapsed) override
    {
        if (stage == 0)
        {
            timeElapsedInStage += timeElapsed;
            if (timeElapsedInStage > 20000)
                logger->log((String)"" + timeElapsedInStage);
            if (timeElapsedInStage > 30000)
            {
                stage = 1;
                timeElapsedInStage = 0;
                leg2->setSpeed(120, 120, 60);
                leg2->setDesiredAngles(-1, -1, 30);
            }
            else
            {
                leg1->setDesiredAngles(90, 90, 90);
                leg2->setDesiredAngles(90, 90, 90);
                leg3->setDesiredAngles(90, 90, 90);
                leg4->setDesiredAngles(90, 90, 90);
            }
            return;
        }
        if (stage == 1)
        {
            timeElapsedInStage += timeElapsed;
            if (leg2->gotDesiredAngles() && timeElapsedInStage > 2000)
            {
                leg2->setSpeed(120, 120, 120);
                stage = 2;
            }
            return;
        }
        if (stage == 2)
        {
            if (leg1->gotDesiredAngles())
            {
                int angle1 = 0;
                int angle2 = 0;
                int angle3 = 0;
                if (leg1Stage == 0)
                {
                    angle1 = 90;
                    angle2 = 50;
                    angle3 = 90;

                    leg1Stage = 1;
                }
                else
                {
                    angle1 = 90;
                    angle2 = 40;
                    angle3 = 90;

                    leg1Stage = 0;
                }

                leg1->setDesiredAngles(angle1, angle2, angle3);
            }
        }

        // if (leg2.gotDesiredAngles())
        // {
        //     if (angle2 == maxAngle)
        //         angle2 = minAngle;
        //     else
        //         angle2 = maxAngle;

        //     leg2.setDesiredAngles(angle2, -1, -1);
        // }
        // if (leg3.gotDesiredAngles())
        // {
        //     if (angle3 == maxAngle)
        //         angle3 = minAngle;
        //     else
        //         angle3 = maxAngle;

        //     leg3.setDesiredAngles(angle3, -1, -1);
        //    }
    }

private:
    Leg *leg1, *leg2, *leg3, *leg4;
    Logger *logger;

    int stage = 0;
    long timeElapsedInStage = 0;

    int leg1Stage;
    int leg2Stage;
    int leg3Stage;
    int leg4Stage;
};

#endif