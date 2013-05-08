#ifndef _MATH_H_
#define _MATH_H_

#define MAX(a, b)                   ((a > b) ? a : b)
#define MIN(a, b)                   ((a < b) ? a : b)
#define CLAMP(val, min, max)        (MIN(MAX(val, min), max))

#define TAO     6.283185307179586476925286766559

#define DEGREES_TO_RADIANS(deg)     (deg * (TAO / 360.0f))

#include <math.h>

#endif // _MATH_H_