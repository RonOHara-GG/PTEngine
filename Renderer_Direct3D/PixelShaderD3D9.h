#ifndef _PIXEL_SHADER_D3D9_H_
#define _PIXEL_SHADER_D3D9_H_

#include "..\PixelShader.h"

class PixelShaderD3D9 : public PixelShader
{
public:
    PixelShaderD3D9(IDirect3DPixelShader9* shader);
    virtual ~PixelShaderD3D9(void);

    IDirect3DPixelShader9* GetShader()          { return mShader; }

protected:
    IDirect3DPixelShader9* mShader;
};


#endif // _PIXEL_SHADER_D3D9_H_