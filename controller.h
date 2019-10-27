#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_
#include "robot.h"
#include "logger.h"
#include "behaviour.h"

class Controller
{
public:
    virtual Behaviour* getBehaviour() = 0;
private:
};

#endif //__CONTROLLER_H_