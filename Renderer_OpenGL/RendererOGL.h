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

    virtual void SetViewport(const Box& viewSpace);
    virtual const Box& GetViewport();

    virtual void SetViewMatrix(const Matrix4x4& view);
    virtual void SetProjectionMatrix(const Matrix4x4& projection);

    virtual void Clear(bool bClearColor = true, const RGBA& color = RGBA::Black, bool bClearDepth = true, float depthValue = 1.0f, bool bClearStencil = false, unsigned int stencilValue = 0);
    
    virtual VertexShader* CreateVertexShader(void* shaderData, uint shaderDataSize);
    virtual PixelShader* CreatePixelShader(void* shaderData, uint shaderDataSize);
    virtual VertexProfile* CreateVertexProfile(const DynamicArray<VertexBuffer*>& vertexBuffers);
    virtual VertexBuffer* CreateVertexBuffer(int vertexCount, const VertexFormat& format, bool dynamic = false);
    virtual IndexBuffer* CreateIndexBuffer(int indexCount, bool sixteenBit = true);
        
    virtual Material* SetMaterial(Material* material, const Matrix4x4& ltw);
    virtual VertexProfile* SetVertexProfile(VertexProfile* profile);
    virtual VertexBuffer* SetVertexBuffer(uint index, VertexBuffer* vertexBuffer);
    virtual IndexBuffer* SetIndexBuffer(IndexBuffer* indexBuffer);

private:
	HWND	mWindow;
	HDC		mDeviceContext;
	HGLRC	mRenderContext;
};

#endif // _RENDERER_OGL_H_
