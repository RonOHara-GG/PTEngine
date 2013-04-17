#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    void Set(float x, float y, float z);

public:
    float mX;
    float mY;
    float mZ;
}

#include "Vector3_Default.h"

#endif // _VECTOR3_H_