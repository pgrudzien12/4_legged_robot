#ifndef __SERIALCONTROLLER_H_
#define __SERIALCONTROLLER_H_
#include "USBAPI.h"
#include "../controller.h"
#include "../behaviour.h"
#include "../behaviour/balance.h"
#include "../logger.h"
#include "../robot.h"
#include "../messageInterpreter.h"

class SerialController : public Controller
{
public:
    SerialController(Serial_ serial, Logger *logger, Robot *robot)
    {
        this->serial = serial;
        this->logger = logger;
        this->robot = robot;
        this->behaviour = new BalanceBehaviour(logger, robot);
    }

    Behaviour *getBehaviour() override
    {
        if (this->serial.available())
        {
            int inByte = this->serial.read();
            MessageInterpreter *messageInterpreter = this->behaviour->getMessageInterpreter();
            if (messageInterpreter->interpret(inByte))
            {
                behaviour->onMessage(messageInterpreter.getMessage());
            }
            logger->log("got message");
        }

        return this->behaviour;
    };

private:
    Serial_ serial;
    Logger *logger;
    Robot *robot;
    BalanceBehaviour *behaviour;
};

#endif //__SERIALCONTROLLER_H_