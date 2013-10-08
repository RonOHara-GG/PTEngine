#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Box.h"
#include "RGBA.h"
#include "Matrix4x4.h"

class Mesh;
class VertexBuffer;
class IndexBuffer;
class VertexFormat;
class VertexProfile;
class VertexShader;
class PixelShader;
class Material;
class Texture;

#include "DDS.h"

class Renderer
{
public:
    enum ePrimitiveType
    {
        ePT_Triangles,
        ePT_TriangleStrip,
        ePT_TriangleFan,
        ePT_Lines
    };

    enum eCullMode
    {
        eCM_None,
        eCM_Clockwise,
        eCM_CounterClockwise,
    };

public:
    virtual ~Renderer() {};

    virtual bool Init(void* window, int width, int height, bool fullScreen) = 0;
    virtual void Shutdown() = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void FinishFrame() {}

    virtual void SetViewport(const Box& viewSpace) = 0;
    virtual const Box& GetViewport() = 0;

    virtual void SetViewMatrix(const Matrix4x4& view) = 0;
    virtual void SetProjectionMatrix(const Matrix4x4& projection) = 0;

    virtual void Clear(bool bClearColor = true, const RGBA& color = RGBA::Black, bool bClearDepth = true, float depthValue = 1.0f, bool bClearStencil = false, unsigned int stencilValue = 0) = 0;

    virtual VertexShader* CreateVertexShader(void* shaderData, uint shaderDataSize) = 0;
    virtual PixelShader* CreatePixelShader(void* shaderData, uint shaderDataSize) = 0;
    virtual VertexProfile* CreateVertexProfile(const VertexBuffer** vertexBuffers, int numVertexBuffers) = 0;
    virtual VertexBuffer* CreateVertexBuffer(int vertexCount, const VertexFormat& format, bool dynamic = false) = 0;
    virtual IndexBuffer* CreateIndexBuffer(int indexCount, bool sixteenBit = true) = 0;
    virtual Texture* CreateTexture(DDS* textureFile, uint dataSize) = 0;

    virtual Material* SetMaterial(Material* material, const Matrix4x4& ltw) = 0;
    virtual Material* SetSpriteMaterial(Material* material) = 0;
    virtual VertexProfile* SetVertexProfile(VertexProfile* profile) = 0;
    virtual VertexBuffer* SetVertexBuffer(uint index, VertexBuffer* vertexBuffer) = 0;
    virtual IndexBuffer* SetIndexBuffer(IndexBuffer* indexBuffer) = 0;
      
    virtual void Draw(int vertexCount, int primitiveCount, ePrimitiveType primitiveType) = 0;
    virtual void DrawSprites(Texture* texture, int numSprites, VertexBuffer* vb) = 0;
    
    virtual void EnableDepthTest(bool enable = true) = 0;
    virtual void SetCullMode(eCullMode cullMode) = 0;

    static int GetPrimitiveIndexCount(int primitiveCount, ePrimitiveType primitiveType);

};


#endif // _RENDERER_H_