#include <Wire.h>
#include <PCA9685.h>
#include "leg.h"
#include "logger.h"
#include "serialLogger.h"
#include "controller.h"
#include "boredRobot.h"

ServoDriver pwm = ServoDriver();
Leg leg1;
Leg leg2;
Leg leg3;
Leg leg4;
unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long interval = 10;      // interval at which to blink (milliseconds)
Logger *logger;
Controller *controller;
int leg1Stage = 0;
int leg2Stage = 0;
int leg3Stage = 0;
int leg4Stage = 0;
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
    leg1.calibrateHip(60);
    leg2.calibrateHip(-20);
    leg3.calibrateHip(20);
    leg4.calibrateHip(20);

    logger = new SerialLogger();
    //leg1.initLog(logger);

    resetServos();
    controller = new BoredRobot(leg1, leg2, leg3, leg4);
    previousMillis = millis();
    //leg1.setDesiredAngles(angle1, -1, -1);
    //leg2.setDesiredAngles(angle2, -1, -1);
}

void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis > interval)
    {
        long timeElapsed = currentMillis - previousMillis;
        previousMillis = currentMillis;
        updateState();

        renderUpdate(timeElapsed);
    }
}
void updateState()
{
    if (leg1.gotDesiredAngles())
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

        leg1.setDesiredAngles(angle1, angle2, angle3);
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
    leg2.setDesiredAngles(-1, -1,30);
    leg3.setDesiredAngles(-1, -1, -1);
    if (leg4.gotDesiredAngles())
    {
        leg4.setDesiredAngles(-1, -1, 90);
    }
}

void renderUpdate(long timeElapsed)
{
    //logger->log("leg1");
    leg1.update(timeElapsed);
    //logger->log("leg2");
    leg2.update(timeElapsed);
    //logger->log("leg3");
    leg3.update(timeElapsed);
    //logger->log("leg4");
    leg4.update(timeElapsed);
}

void resetServos()
{
    leg1.reset();
    leg2.reset();
    leg3.reset();
    leg4.reset();
}
