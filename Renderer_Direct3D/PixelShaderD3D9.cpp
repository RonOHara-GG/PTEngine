#include "..\PTEngine.h"
#include "RendererD3D.h"
#include "PixelShaderD3D9.h"


PixelShaderD3D9::PixelShaderD3D9(IDirect3DPixelShader9* shader)
{
    mShader = shader;
}

PixelShaderD3D9::~PixelShaderD3D9(void)
{
    mShader->Release();
}
