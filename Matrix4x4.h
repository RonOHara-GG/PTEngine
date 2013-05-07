#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include "Vector3.h"
#include "Vector4.h"

class Matrix4x4
{
public:
    Matrix4x4();

    operator const float*() const;
    Matrix4x4 operator *(const Matrix4x4& rhs) const;

    void Transpose();

    void SetIdentity();
    void SetPerspective(float width, float height, float near, float far, bool leftHanded = true);
    void SetPerspectiveFov(float fovY, float aspectRatio, float near, float far, bool leftHanded = true);
    void SetLook(const Vector3& eyePosition, const Vector3& lookAt, const Vector3& upDirection, bool leftHanded = true);

public:
    Vector4 mA;
    Vector4 mB;
    Vector4 mC;
    Vector4 mD;
};

inline Matrix4x4::Matrix4x4()
{
    SetIdentity();
}

inline void Matrix4x4::SetIdentity()
{
    mA.Set(1.0f, 0.0f, 0.0f, 0.0f);
    mB.Set(0.0f, 1.0f, 0.0f, 0.0f);
    mC.Set(0.0f, 0.0f, 1.0f, 0.0f);
    mD.Set(0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4::operator const float*() const
{
    return (const float*)&mA;
}

inline Matrix4x4 Matrix4x4::operator *(const Matrix4x4& rhs) const
{
    Matrix4x4 ret;
    Matrix4x4 trans = rhs;
    trans.Transpose();
    
    float fX, fY, fZ, fW;
    fX = mA.Dot(trans.mA);
    fY = mA.Dot(trans.mB);
    fZ = mA.Dot(trans.mC);
    fW = mA.Dot(trans.mD);
    ret.mA.Set(fX, fY, fZ, fW);
    
    fX = mB.Dot(trans.mA);
    fY = mB.Dot(trans.mB);
    fZ = mB.Dot(trans.mC);
    fW = mB.Dot(trans.mD);
    ret.mB.Set(fX, fY, fZ, fW);
    
    fX = mC.Dot(trans.mA);
    fY = mC.Dot(trans.mB);
    fZ = mC.Dot(trans.mC);
    fW = mC.Dot(trans.mD);
    ret.mC.Set(fX, fY, fZ, fW);
    
    fX = mD.Dot(trans.mA);
    fY = mD.Dot(trans.mB);
    fZ = mD.Dot(trans.mC);
    fW = mD.Dot(trans.mD);
    ret.mD.Set(fX, fY, fZ, fW);
    
    return ret;
}

inline void Matrix4x4::Transpose()
{
#define SWAP(a, b, c)   { c = a; a = b; b = c; }
    float temp;
    float* floats = (float*)&mA;
    
    SWAP(floats[1], floats[4], temp);
    SWAP(floats[2], floats[8], temp);
    SWAP(floats[3], floats[12], temp);
    SWAP(floats[6], floats[9], temp);
    SWAP(floats[7], floats[13], temp);
    SWAP(floats[11], floats[14], temp);
}

#endif // _MATRIX4X4_H_