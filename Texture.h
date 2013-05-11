#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class Texture
{
public:
    virtual ~Texture()  {}

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
};

#endif // _TEXTURE_H_