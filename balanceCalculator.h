#ifndef __BALANCECALCULATOR_H__
#define __BALANCECALCULATOR_H__
#include "logger.h"
#include "leg.h"
#include "robot.h"

class BalanceResult
{
private:
    void calcAngles(float x, float y, float z, float *result);
    inline bool isCorrect(float tab[3])
    {
        return !(isnan(tab[0]) || isnan(tab[1]) || isnan(tab[2]));
    }

public:
    float leg1[3];
    float leg2[3];
    float leg3[3];
    float leg4[3];
    BalanceResult(float x, float y, float z)
    {
        calcAngles(-x, -y, z, this->leg1);
        calcAngles(-x, y, z, this->leg2);
        calcAngles(x, y, z, this->leg3);
        calcAngles(x, -y, z, this->leg4);
    }

    void setBalance(Robot *robot)
    {
        robot->GetLeg(1)->setDesiredAngles(90 - leg1[0], 90 + leg1[1], 90 + leg1[2]);
        robot->GetLeg(2)->setDesiredAngles(90 + leg2[0], 90 - leg2[1], 90 - leg2[2]);
        robot->GetLeg(3)->setDesiredAngles(90 - leg3[0], 90 + leg3[1], 90 + leg3[2]);
        robot->GetLeg(4)->setDesiredAngles(90 + leg4[0], 90 - leg4[1], 90 - leg4[2]);
    }

    bool isCorrect()
    {
        return isCorrect(this->leg1) || isCorrect(this->leg2) || isCorrect(this->leg3) || isCorrect(this->leg4);
    }

private:
    void IK(float x, float y, float *q1_out, float *q2_out)
    {
        const float tibia = 6.2;
        const float tarsus = 7;

        // tak a note that this is a different reference system (for x,y) than in calcAngles
        float L1 = tibia;
        float L2 = tarsus;

        float q2_up = x * x + y * y - L1 * L1 - L2 * L2;
        float q2_down = 2 * L1 * L2;
        float q2 = acos(q2_up / q2_down);

        float q1_up = L2 * sin(q2);
        float q1_down = sqrt(x * x + y * y);
        float q1 = atan(y / x) - asin(q1_up / q1_down);

        (*q1_out) = q1 - PI / 4;
        (*q2_out) = q2 - PI / 4;
    }
};

class BalanceCalculator
{
private:
    float max[3];
    float min[3];

public:
    BalanceCalculator(float minX, float minY, float minZ
        float maxX, float maxY, float maxZ)
    {
        max[0] = maxX;
        max[1] = maxY;
        max[2] = maxZ;
        min[0] = minX;
        min[1] = minY;
        min[2] = minZ;
    }

    /**
     * 
     * Calculates closest BalanceResult using binary chop
     * 
     **/
    BalanceResult calculate(float x, float y, float z)
    {
        float factorX = x > 0 ? maxX : minX;
        float factorY = y > 0 ? maxY : minY;
        float factorZ = z > 0 ? maxZ : minZ;
        BalanceResult lastCorrect(factorX * x, factorY * y, factorZ * z);
        if (lastCorrect.isCorrect())
            return lastCorrect;

        float factor = 0.5f;
        float factorSum = 0.5f;

        for (size_t i = 0; i < 10; i++)
        {
            BalanceResult balance(factorX * x * factorSum, factorY * y * factorSum, factorZ * z * factorSum);
            factor = factor/2.f;
            if (balance.isCorrect())
            {
                lastCorrect = balance;
                factorSum += factor;
            }else
            {
                factorSum -= factor;
            }
            
        }

        return lastCorrect;
    }
};

void
BalanceResult::calcAngles(float x, float y, float z, float *result)
{
    // const float F[3] = {6.28198052, 6.28198052, 11.38406204};
    x = x + 6.28198052f;
    y = y + 6.28198052f;
    z = z + 11.38406204f;
    const float femur = 4.5;

    float alpha = atan(x / y);
    float w = sqrt(x * x + y * y);
    float mi = w - femur;

    float q1, q2;
    IK(mi, z, &q1, &q2);

    result[0] = q2 * RAD_TO_DEG;
    result[1] = q1 * RAD_TO_DEG;
    result[2] = (alpha - PI / 4) * RAD_TO_DEG;
}

#endif
