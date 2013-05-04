#ifndef _VECTOR4_DEFAULT_H_
#define _VECTOR4_DEFAULT_H_

inline Vector4::Vector4()
{
    Set(0, 0, 0, 1.0f);
}

inline Vector4::Vector4(float x, float y, float z, float w)
{
    Set(x, y, z, w);
}

inline void Vector4::Set(float x, float y, float z, float w)
{    
    mX = x;
    mY = y;
    mZ = z;
    mW = w;
}

inline float Vector4::Dot(const Vector4& v) const
{
    return ((mX * v.mX) + (mY * v.mY) + (mZ * v.mZ) + (mW * v.mW));
}


#endif // _VECTOR4_DEFAULT_H_