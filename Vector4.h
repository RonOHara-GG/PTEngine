#ifndef _VECTOR4_H_
#define _VECTOR4_H_

class Vector4
{
public:
    Vector4();
    Vector4(float x, float y, float z, float w = 1.0f);

    void Set(float x, float y, float z, float w);

    float Dot(const Vector4& v) const;

public:
    float mX;
    float mY;
    float mZ;
    float mW;
};

#include "Vector4_Default.h"

#endif // _VECTOR4_H_