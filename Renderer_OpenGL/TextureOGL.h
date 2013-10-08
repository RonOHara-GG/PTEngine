#ifndef _TEXTURE_OGL_H_
#define _TEXTURE_OGL_H_

#include "..\Texture.h"
#include "..\DDS.h"

class TextureOGL : public Texture
{
public:
    TextureOGL(void);
    virtual ~TextureOGL(void);

    bool Init(DDS* dds);

    void Bind();

    virtual int GetWidth()      { return mDDS.mWidth; }
    virtual int GetHeight()     { return mDDS.mHeight; }

protected:
    DDS         mDDS;
    uint        mTexture;
};

#endif // _TEXTURE_OGL_H_