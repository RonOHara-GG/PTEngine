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




#endif // _VECTOR4_DEFAULT_H_