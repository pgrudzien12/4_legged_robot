#ifndef __SERIALBALANCECONTROLLER_H_
#define __SERIALBALANCECONTROLLER_H_
#include "USBAPI.h"
#include "../controller.h"
#include "../behaviour.h"
#include "../behaviour/balance.h"
#include "../logger.h"
#include "../robot.h"
#include "../behaviour/keyboardMessage.h"

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
            char buffer[10];
            int length = this->serial->readBytesUntil((char)0, buffer, 10);
            if (length == 1)
            {
                KeyboardMessage message((int)buffer[0]);
                behaviour->onMessage(message);
            }
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