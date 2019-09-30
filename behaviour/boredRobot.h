#ifndef __BOREDROBOT_H__
#define __BOREDROBOT_H__
#include "../behaviour.h"
#include "../leg.h"
#include "../robot.h"
#include "../logger.h"

class BoredRobotBehaviour : public Behaviour
{
public:
    BoredRobotBehaviour(Logger *logger, Robot *robot) 
        : Behaviour(logger, robot)
    {
        this->leg1 = robot->GetLeg(1);
        this->leg2 = robot->GetLeg(2);
        this->leg3 = robot->GetLeg(3);
        this->leg4 = robot->GetLeg(4);
    }

    void update(long timeElapsed) override
    {
        timeElapsedInStage += timeElapsed;
        if (stage == 0)
        {
            if (timeElapsedInStage > 15000)
                logger->log((String)"" + timeElapsedInStage);
            if (timeElapsedInStage > 20000)
            {
                stage = 1;
                timeElapsedInStage = 0;
                leg2->setSpeedDPS(120, 120, 60);
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
            if (leg2->gotDesiredAngles() && timeElapsedInStage > 2000)
            {
                leg2->setSpeedDPS(120, 120, 120);
                timeElapsedInStage = 0;
                stage = 2;
            }
            return;
        }
        if (stage == 2)
        {
            if (timeElapsedInStage > 20000)
            {
                timeElapsedInStage = 0;
                stage = 0;
                return;
            }
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
    }

private:
    Leg *leg1, *leg2, *leg3, *leg4;

    int stage = 0;
    long timeElapsedInStage = 0;

    int leg1Stage;
};

#endif