#include <Wire.h>
#include <PCA9685.h>
#include "leg.h"
#include "logger.h"
#include "logging/serialLogger.h"
#include "behaviour.h"
#include "robot.h"
#include "behaviour/forward.h"
#include "behaviour/boredRobot.h"
#include "behaviour/balance.h"
#include "controller.h"
#include "controller/serialController.h"

#define DEFAULTINTERVAL 10

ServoDriver pwm = ServoDriver();
Leg leg1;
Leg leg2;
Leg leg3;
Leg leg4;
unsigned long previousMillis = 0;
long long interval = DEFAULTINTERVAL;
Logger *logger;
Robot *robot;
//Behaviour *behaviour;
Controller *controller;

void setup()
{
    // put your setup code here, to run once:
    Wire.begin();
    Serial.begin(9600);

    pwm.init(0x7f);
    pwm.setFrequency(60);
    delay(10);

    leg1.init(&pwm, 1, 2, 3);
    leg2.init(&pwm, 4, 5, 6);
    leg3.init(&pwm, 9, 11, 10);
    leg4.init(&pwm, 16, 15, 14);

    leg4.calibrateHip(10);

    logger = new SerialLogger();
    leg1.initLog(logger);
    leg2.initLog(logger);
    leg3.initLog(logger);
    leg4.initLog(logger);

    robot = new Robot(logger, &leg1, &leg2, &leg3, &leg4);
    robot->resetServos();

    controller = new SerialController(Serial, logger, robot);
    previousMillis = millis();
}

void loop()
{
    unsigned long currentMillis = millis();
    Behaviour *behaviour = controller->getBehaviour();

    if (currentMillis - previousMillis > interval)
    {
        unsigned long timeElapsed = currentMillis - previousMillis;
        interval = DEFAULTINTERVAL - (currentMillis - previousMillis - interval);
        previousMillis = currentMillis;

        if (interval > 0)
        {
            behaviour->update(timeElapsed);
            robot->executeStep(timeElapsed);
        }
    }
}
