#ifndef __SERIALBALANCECONTROLLER_H_
#define __SERIALBALANCECONTROLLER_H_
#include "USBAPI.h"
#include "../controller.h"
#include "../behaviour.h"
#include "../behaviour/balance.h"
#include "../logger.h"
#include "../robot.h"
#include "../behaviour/balanceMessage.h"

class SerialBalanceController : public Controller
{
public:
    SerialBalanceController(Serial_ *serial, Logger *logger, Robot *robot)
    {
        this->serial = serial;
        this->logger = logger;
        this->robot = robot;
        this->behaviour = new BalanceBehaviour(logger, robot);
    }

    Behaviour *getBehaviour() override
    {
        if (this->serial->available())
        {
            int inByte = this->serial->read();
            BalanceMessage message(inByte);
            behaviour->onMessage(message);

            logger->log("got message");
        }

        return this->behaviour;
    };

private:
    Serial_ *serial;
    Logger *logger;
    Robot *robot;
    BalanceBehaviour *behaviour;
};

#endif //__SERIALBALANCECONTROLLER_H_