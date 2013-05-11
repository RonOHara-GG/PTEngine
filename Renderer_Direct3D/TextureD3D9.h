#ifndef _TEXTURE_D3D9_H_
#define _TEXTURE_D3D9_H_

#include "..\Texture.h"
#include "..\DDS.h"

class TextureD3D9 : public Texture
{
public:
    TextureD3D9(IDirect3DTexture9* d3dTexture, DDS* dds);
    virtual ~TextureD3D9(void);

    virtual int GetWidth()      { return (int)mDDSInfo.mWidth; }
    virtual int GetHeight()     { return (int)mDDSInfo.mHeight; }

protected:
    IDirect3DTexture9*  mTexture;
    DDS                 mDDSInfo;
};

#endif // _TEXTURE_D3D9_H_