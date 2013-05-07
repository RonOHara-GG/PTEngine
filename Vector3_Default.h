#ifndef _VECTOR3_DEFAULT_H_
#define _VECTOR3_DEFAULT_H_

inline Vector3::Vector3()
{
    Set(0, 0, 0);
}

inline Vector3::Vector3(float x, float y, float z)
{
    Set(x, y, z);
}

inline void Vector3::Set(float x, float y, float z)
{    
    mX = x;
    mY = y;
    mZ = z;
}

inline float Vector3::Length() const
{
    return (float)sqrt(LengthSq());
}

inline float Vector3::LengthSq() const
{
    return Dot(*this);
}

inline float Vector3::Dot(const Vector3& other) const
{
    return (mX * other.mX) + (mY * other.mY) + (mZ * other.mZ);
}

inline void Vector3::Normalize()
{
    float scale = 1.0f / Length();
    mX *= scale;
    mY *= scale;
    mZ *= scale;
}

inline Vector3 Vector3::operator -(const Vector3& rhs) const
{
    return Vector3(mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ);
}

inline Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.mY * v2.mZ - v1.mZ * v2.mY, v1.mZ * v2.mX - v1.mX * v2.mZ, v1.mX * v2.mY - v1.mY * v2.mX);
}

#endif // _VECTOR3_DEFAULT_H_