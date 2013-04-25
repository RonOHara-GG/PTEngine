#ifndef _RGBA_H_
#define _RGBA_H_

#include "Math.h"

class RGBA
{
public:
    RGBA();
    RGBA(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, unsigned int scale = 0xFF);
    RGBA(float red, float green, float blue, float alpha);

    void Set(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, unsigned int scale = 0xFF);
    void Set(float red, float green, float blue, float alpha);

public:
    float mRed;
    float mGreen;
    float mBlue;
    float mAlpha;
    

public:
    static const RGBA   Black;
    static const RGBA   White;
    static const RGBA   Grey;
    static const RGBA   Red;
    static const RGBA   Green;
    static const RGBA   Blue;
};

inline RGBA::RGBA()
{
    Set(0.0f, 0.0f, 0.0f, 1.0f);
}

inline RGBA::RGBA(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, unsigned int scale)
{
    Set(red, green, blue, alpha, scale);
}

inline RGBA::RGBA(float red, float green, float blue, float alpha)
{
    Set(red, green, blue, alpha);
}

inline void RGBA::Set(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, unsigned int scale)
{
    float fScale = 1.0f / (float)scale;
    Set((float)red * fScale, (float)green * fScale, (float)blue * fScale, (float)alpha * fScale);
}

inline void RGBA::Set(float red, float green, float blue, float alpha)
{
    mRed = CLAMP(red, 0, 1);
    mGreen = CLAMP(green, 0, 1);
    mBlue = CLAMP(blue, 0, 1);
    mAlpha = CLAMP(alpha, 0, 1);
}

#endif // _RGBA_H_