#include "..\PTEngine.h"
#include "RendererD3D.h"
#include "TextureD3D9.h"


TextureD3D9::TextureD3D9(IDirect3DTexture9* d3dTexture, DDS* dds)
{
    mTexture = d3dTexture;
    mDDSInfo = *dds;
}


TextureD3D9::~TextureD3D9(void)
{
    mTexture->Release();
}
