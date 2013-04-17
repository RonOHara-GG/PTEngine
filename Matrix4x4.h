#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include "Vector4.h"

class Matrix4x4
{
public:
    Matrix4x4();


public:
    Vector4 mA;
    Vector4 mB;
    Vector4 mC;
    Vector4 mD;
};

inline Matrix4x4::Matrix4x4()
{
    mA.Set(1.0f, 0.0f, 0.0f, 0.0f);
    mB.Set(0.0f, 1.0f, 0.0f, 0.0f);
    mC.Set(0.0f, 0.0f, 1.0f, 0.0f);
    mD.Set(0.0f, 0.0f, 0.0f, 1.0f);
}

#endif // _MATRIX4X4_H_