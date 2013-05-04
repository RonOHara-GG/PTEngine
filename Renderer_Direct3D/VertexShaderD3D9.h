#ifndef _VERTEX_SHADER_D3D9_H_
#define _VERTEX_SHADER_D3D9_H_

#include "..\VertexShader.h"

class VertexShaderD3D9 : public VertexShader
{
public:
    VertexShaderD3D9(IDirect3DVertexShader9* shader);
    virtual ~VertexShaderD3D9(void);

    IDirect3DVertexShader9* GetShader() { return mShader; }

protected:
    IDirect3DVertexShader9* mShader;
};

#endif // _VERTEX_SHADER_D3D9_H_