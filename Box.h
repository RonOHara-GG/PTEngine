#ifndef _BOX_H_
#define _BOX_H_

#include "Vector3.h"

class Box
{
public:
    Box();
    Box(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    Box(Vector3 min, Vector3 max);


public:
    Vector3 mMin;
    Vector3 mMax;
};


// Implementation
inline Box::Box()
{
}

inline Box::Box(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    mMin.Set(minX, minY, minZ);
    mMax.Set(maxX, maxY, maxZ);
}

inline Box::Box(Vector3 min, Vector3 max)
{
    mMin = min;
    mMax = max;
}

#endif // _BOX_H_