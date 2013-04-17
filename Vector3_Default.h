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




#endif // _VECTOR3_DEFAULT_H_