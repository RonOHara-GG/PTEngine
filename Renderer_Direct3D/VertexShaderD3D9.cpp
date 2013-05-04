#include "..\PTEngine.h"
#include "RendererD3D.h"
#include "VertexShaderD3D9.h"


VertexShaderD3D9::VertexShaderD3D9(IDirect3DVertexShader9* shader)
{
    mShader = shader;
}


VertexShaderD3D9::~VertexShaderD3D9(void)
{
    mShader->Release();
}
