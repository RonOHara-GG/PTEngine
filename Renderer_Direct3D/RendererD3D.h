#ifndef _RENDERER_D3D_H_
#define _RENDERER_D3D_H_

#include "..\Renderer.h"
#undef malloc
#undef free

#include <Windows.h>
#include <d3d9.h>

class RendererD3D : Renderer
{
public:
    RendererD3D(void);
    ~RendererD3D(void);

    virtual bool Init(void* window, bool fullScreen);
    virtual void Shutdown();

    virtual void BeginFrame();
    virtual void EndFrame();
    virtual void FinishFrame();

    virtual void SetViewport(Box viewSpace);
    virtual void GetViewport(Box& viewSpace);

    virtual void SetViewMatrix(const Matrix4x4& view);
    virtual void SetProjectionMatrix(const Matrix4x4& projection);

    virtual void Clear(bool bClearColor = true, const RGBA& color = RGBA::Black, bool bClearDepth = true, float depthValue = 1.0f, bool bClearStencil = false, unsigned int stencilValue = 0);

    virtual VertexBuffer* CreateVertexBuffer(int vertexCount, const VertexFormat& vertexFormat, bool dynamic = false);
    virtual IndexBuffer* CreateIndexBuffer(int indexCount, bool sixteenBit = true);

    virtual void DrawMesh(Mesh* mesh);

private:
    IDirect3DDevice9*   mDevice;
};

#endif // _RENDERER_D3D_H_

