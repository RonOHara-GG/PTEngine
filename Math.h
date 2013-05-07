#ifndef _MATH_H_
#define _MATH_H_

#define MAX(a, b)                   ((a > b) ? a : b)
#define MIN(a, b)                   ((a < b) ? a : b)
#define CLAMP(val, min, max)        (MIN(MAX(val, min), max))

#include <math.h>

#endif // _MATH_H_