#ifndef __SERIALBALANCECONTROLLER_H_
#define __SERIALBALANCECONTROLLER_H_
#include "USBAPI.h"
#include "../controller.h"
#include "../behaviour.h"
#include "../behaviour/balance.h"
#include "../behaviour/calculator.h"
#include "../logger.h"
#include "../robot.h"
#include "../hidMessage.h"
#include "../serialProtocol.h"

class SerialBalanceController : public Controller
{
public:
    SerialBalanceController(Serial_ *serial, Logger *logger, Robot *robot)
    {
        this->serial = serial;
        this->logger = logger;
        this->robot = robot;
        //this->behaviour = new CalculatorBehaviour(logger, robot);
        this->behaviour = new BalanceBehaviour(logger, robot);
    }

    Behaviour *getBehaviour() override
    {
        HidMessage message = receive(Serial);
        if (message.isCorrectMessage())
        {
            behaviour->onMessage(message);
        }

        return this->behaviour;
    };

private:
    Serial_ *serial;
    Logger *logger;
    Robot *robot;
    //CalculatorBehaviour *behaviour;
    BalanceBehaviour *behaviour;
};

#endif //__SERIALBALANCECONTROLLER_H_