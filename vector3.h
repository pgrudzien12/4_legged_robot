#ifndef __VECTOR3_H_
#define __VECTOR3_H_

class Vector3
{
public:
    Vector3(float u, float v, float w)
    {
        vector[0] = u;
        vector[1] = v;
        vector[2] = w;
    }

private:
    float vector[3];
};

#endif
