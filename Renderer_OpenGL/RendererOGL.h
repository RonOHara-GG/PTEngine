#ifndef _RENDERER_OGL_H_
#define _RENDERER_OGL_H_

#include "..\Renderer.h"
#undef malloc
#undef free

#include <Windows.h>

class RendererOGL : Renderer
{
public:
    RendererOGL(void);
    ~RendererOGL(void);

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

    virtual VertexBuffer* CreateVertexBuffer(int vertexCount, uint vertexComponents, bool dynamic = false);
    virtual IndexBuffer* CreateIndexBuffer(int indexCount, bool sixteenBit = true);

    virtual void DrawMesh(Mesh* mesh);

private:
	HWND	mWindow;
	HDC		mDeviceContext;
	HGLRC	mRenderContext;
};

#endif // _RENDERER_OGL_H_
