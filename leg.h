#ifndef __LEG_H__
#define __LEG_H__

#include <PCA9685.h>
#include "logger.h"

#define HIP 2
#define KNEE 1
#define FEET 0

class Leg
{
public:
    void init(ServoDriver *driver, byte feet, byte knee, byte hip);
    void initLog(Logger *logger);

    void setSpeedDPS(float feet, float knee, float hip);
    
/**
 *
 * Sets the speed of the motors to finish at the desired moment.
 * 
 */
    void setSpeedTTF(float timeToFinish);

    void setDesiredAngles(float *angles);
    void setDesiredAngles(float feet, float knee, float hip);

    bool gotDesiredAngles();

    // timeElapsed in miliseconds
    void update(unsigned long timeElapsed);

    void setTo(int angle);

    void moveHip(int angle);

    void moveKnee(int angle);

    void moveFeet(int angle);

    void calibrateHip(int angle);

    void reset();

private:
    float dps[3];
    float desiredAngle[3];
    float currentAngle[3];
    byte servoMap[3];
    int calib[3];
    byte feet, knee, hip;
    ServoDriver *driver;
    Logger *logger;
};

#endif // __LEG_H__
