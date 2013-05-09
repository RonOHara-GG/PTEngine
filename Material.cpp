#include "PTEngine.h"
#include "Material.h"


Material::Material(void)
{
    mVertexShader = 0;
    mPixelShader = 0;
    mProgram = 0;
}


Material::~Material(void)
{
}

VertexShader* Material::SetVertexShader(VertexShader* shader)
{
    VertexShader* old = mVertexShader;
    mVertexShader = shader;
    return old;
}

PixelShader* Material::SetPixelShader(PixelShader* shader)
{
    PixelShader* old = mPixelShader;
    mPixelShader = shader;
    return old;
}