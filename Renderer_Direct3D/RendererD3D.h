#ifndef _RENDERER_D3D_H_
#define _RENDERER_D3D_H_

#include "..\Renderer.h"
#undef malloc
#undef free

#include <Windows.h>
#include <d3d9.h>
#include <D3DX9Shader.h>

class RendererD3D : Renderer
{
public:
    RendererD3D(void);
    ~RendererD3D(void);

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
    virtual VertexBuffer* CreateVertexBuffer(int vertexCount, const VertexFormat& vertexFormat, bool dynamic = false);
    virtual IndexBuffer* CreateIndexBuffer(int indexCount, bool sixteenBit = true);
    virtual Texture* CreateTexture(DDS* textureFile, uint dataSize);

    virtual Material* SetMaterial(Material* material, const Matrix4x4& ltw);
    virtual Material* SetSpriteMaterial(Material* material);
    virtual VertexProfile* SetVertexProfile(VertexProfile* profile);
    virtual VertexBuffer* SetVertexBuffer(uint index, VertexBuffer* vertexBuffer);
    virtual IndexBuffer* SetIndexBuffer(IndexBuffer* indexBuffer);

    virtual void Draw(int vertexCount, int primitiveCount, ePrimitiveType primitiveType);
    virtual void DrawSprites(Texture* texture, int numSprites);

private:
    ID3DXBuffer* CompileShader(void* shaderData, uint shaderDataSize, const char* entryPoint, const char* shaderProfile);
    void UpdateViewProjection();
    
private:
    IDirect3DDevice9*           mDevice;
    D3DCAPS9                    mDeviceCaps;

    VertexBuffer**              mCurrentVertexBuffers;
    IndexBuffer*                mCurrentIndexBuffer;
    VertexProfile*              mCurrentVertexProfile;
    Material*                   mCurrentMaterial;
    Material*                   mSpriteMaterial;
    
    const char*                 mVertexShaderProfile;
    const char*                 mPixelShaderProfile;

    Box                         mCurrentViewport;
    Matrix4x4                   mViewProjectionMatrix;
    Matrix4x4                   mViewMatrix;
    Matrix4x4                   mProjectionMatrix;
};

#endif // _RENDERER_D3D_H_

