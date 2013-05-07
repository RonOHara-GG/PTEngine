#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    void Set(float x, float y, float z);    
    void Normalize();
        
    float Length() const;
    float LengthSq() const;
    float Dot(const Vector3& other) const;

    Vector3 operator -(const Vector3& rhs) const;

    static Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs);

public:
    float mX;
    float mY;
    float mZ;
};

#include "Vector3_Default.h"

#endif // _VECTOR3_H_