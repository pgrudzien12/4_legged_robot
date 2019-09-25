#include <Wire.h>
#include <PCA9685.h>
#include "leg.h"
#include "logger.h"
#include "serialLogger.h"

ServoDriver pwm = ServoDriver();
Leg leg1;
Leg leg2;
Leg leg3;
Leg leg4;
unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long interval = 10;      // interval at which to blink (milliseconds)
Logger *logger;
int maxAngle = 120;
int minAngle = 60;
int angle1 = 120;
int angle2 = 120;
int angle3 = 120;
int angle4 = 120;
void setup()
{
    // put your setup code here, to run once:
    Wire.begin();
    Serial.begin(9600);

    //pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
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
    previousMillis = millis();
    leg1.setDesiredAngles(angle1, -1, -1);
    leg2.setDesiredAngles(angle2, -1, -1);
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
        if (angle1 == maxAngle)
            angle1 = minAngle;
        else
            angle1 = maxAngle;

        leg1.setDesiredAngles(angle1, -1, -1);
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
    // }    
    // if (leg4.gotDesiredAngles())
    // {
    //     if (angle4 == maxAngle)
    //         angle4 = minAngle;
    //     else
    //         angle4 = maxAngle;

    //     leg4.setDesiredAngles(angle4, -1, -1);
    // }
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
