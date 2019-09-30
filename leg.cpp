#include "leg.h"
#include "logging/emptyLogger.h"

void Leg::init(ServoDriver *driver, byte feet, byte knee, byte hip)
{
    this->feet = feet;
    this->knee = knee;
    this->hip = hip;
    this->servoMap[FEET] = feet;
    this->servoMap[KNEE] = knee;
    this->servoMap[HIP] = hip;
    const int defaultSpeed = 120; // degrees per second
    this->setSpeedDPS(defaultSpeed, defaultSpeed, defaultSpeed);

    this->driver = driver;
    this->logger = new EmptyLogger();
}

bool Leg::gotDesiredAngles()
{
    for (int i = 0; i < 3; i++)
    {
        if (desiredAngle[i] != currentAngle[i])
            return false;
    }

    return true;
}

void Leg::initLog(Logger *logger)
{
    this->logger = logger;
}

void Leg::setSpeedDPS(float feet, float knee, float hip)
{
    if (feet > 0)
        dps[FEET] = feet;

    if (knee > 0)
        dps[KNEE] = knee;

    if (hip > 0)
        dps[HIP] = hip;
}

void Leg::setDesiredAngles(float *angles)
{
    if (angles[0] > 0)
        desiredAngle[FEET] = feet;

    if (angles[1] > 0)
        desiredAngle[KNEE] = knee;

    if (angles[2] > 0)
        desiredAngle[HIP] = hip;
}

void Leg::setDesiredAngles(float feet, float knee, float hip)
{
    if (feet > 0)
        desiredAngle[FEET] = feet;

    if (knee > 0)
        desiredAngle[KNEE] = knee;

    if (hip > 0)
        desiredAngle[HIP] = hip;
}

// timeElapsed in miliseconds
void Leg::update(unsigned long timeElapsed)
{
    for (int i = 0; i < 3; i++)
    {
        if (desiredAngle[i] != currentAngle[i])
        {
            float turnAngle = (timeElapsed / 1000.0) * (dps[i]);

            String tastatus = (String) "turn Angle=" + turnAngle;
            String dastatus = (String) "desiredAngle=" + desiredAngle[i];
            String castatus = (String) "currentAngle=" + currentAngle[i];

            this->logger->log((String) "Joint no:" + i);
            this->logger->log(tastatus);
            this->logger->log(dastatus);
            this->logger->log(castatus);

            if (desiredAngle[i] > currentAngle[i])
            {
                currentAngle[i] += turnAngle;
                if (currentAngle[i] > desiredAngle[i])
                    currentAngle[i] = desiredAngle[i];
            }
            if (desiredAngle[i] < currentAngle[i])
            {
                currentAngle[i] -= turnAngle;
                if (currentAngle[i] < desiredAngle[i])
                    currentAngle[i] = desiredAngle[i];
            }

            this->driver->setAngle(this->servoMap[i], round(currentAngle[i]) + this->calib[i]);
        }
    }
}

void Leg::setTo(int angle)
{
    moveFeet(angle);
    moveKnee(angle);
    moveHip(angle);
}

void Leg::moveHip(int angle)
{
    this->driver->setAngle(hip, angle + this->calib[HIP]);
}

void Leg::moveKnee(int angle)
{
    this->driver->setAngle(knee, angle + this->calib[KNEE]);
}

void Leg::moveFeet(int angle)
{
    this->driver->setAngle(feet, angle + this->calib[FEET]);
}

void Leg::calibrateHip(int angle)
{
    this->calib[HIP] = angle;
}

void Leg::reset()
{
    setTo(90);
    currentAngle[HIP] = 90;
    currentAngle[KNEE] = 90;
    currentAngle[FEET] = 90;
    desiredAngle[HIP] = 90;
    desiredAngle[KNEE] = 90;
    desiredAngle[FEET] = 90;
}
