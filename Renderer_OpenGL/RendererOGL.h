#ifndef _RENDERER_OGL_H_
#define _RENDERER_OGL_H_

#include "..\Renderer.h"
#include "gl.h"

class IndexBufferOGL;

class RendererOGL : Renderer
{
public:
    RendererOGL(void);
    ~RendererOGL(void);

    virtual bool Init(void* window, int width, int height, bool fullScreen);
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
    virtual VertexProfile* CreateVertexProfile(const VertexBuffer** vertexBuffers, int numVertexBuffers);
    virtual VertexBuffer* CreateVertexBuffer(int vertexCount, const VertexFormat& format, bool dynamic = false);
    virtual IndexBuffer* CreateIndexBuffer(int indexCount, bool sixteenBit = true);
    virtual Texture* CreateTexture(DDS* textureFile, uint dataSize);
        
    virtual Material* SetMaterial(Material* material, const Matrix4x4& ltw);
    virtual Material* SetSpriteMaterial(Material* material);
    virtual VertexProfile* SetVertexProfile(VertexProfile* profile);
    virtual VertexBuffer* SetVertexBuffer(uint index, VertexBuffer* vertexBuffer);
    virtual IndexBuffer* SetIndexBuffer(IndexBuffer* indexBuffer);

    virtual void Draw(int vertexCount, int primitiveCount, ePrimitiveType primitiveType);
    virtual void DrawSprites(Texture* texture, int numSprites, VertexBuffer* vb);

    virtual void EnableDepthTest(bool enable = true);
    virtual void SetCullMode(eCullMode cullMode);

private:
    bool PlatformInit(void* window, int width, int height, bool fullScreen);
    void PlatformShutdown();
    void PlatformFinishFrame();

    void UpdateViewProjection();

private:
    IndexBufferOGL*             mCurrentIndexBuffer;
    Material*                   mCurrentMaterial;
    Material*                   mSpriteMaterial;
    Box                         mCurrentViewport;

    Matrix4x4                   mViewMatrix;
    Matrix4x4                   mProjectionMatrix;
    Matrix4x4                   mViewProjectionMatrix;
};

#endif // _RENDERER_OGL_H_
