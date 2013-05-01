#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Box.h"
#include "RGBA.h"
#include "Matrix4x4.h"

class Mesh;
class VertexBuffer;
class IndexBuffer;
class VertexFormat;

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

public:
    virtual ~Renderer() {};

    virtual bool Init(void* window, bool fullScreen) = 0;
    virtual void Shutdown() = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void FinishFrame() {}

    virtual void SetViewport(Box viewSpace) = 0;
    virtual void GetViewport(Box& viewSpace) = 0;

    virtual void SetViewMatrix(const Matrix4x4& view) = 0;
    virtual void SetProjectionMatrix(const Matrix4x4& projection) = 0;

    virtual void Clear(bool bClearColor = true, const RGBA& color = RGBA::Black, bool bClearDepth = true, float depthValue = 1.0f, bool bClearStencil = false, unsigned int stencilValue = 0) = 0;

    virtual VertexBuffer* CreateVertexBuffer(int vertexCount, const VertexFormat& format, bool dynamic = false) = 0;
    virtual IndexBuffer* CreateIndexBuffer(int indexCount, bool sixteenBit = true) = 0;

    virtual void DrawMesh(Mesh* mesh) = 0;
    

    static int GetPrimitiveIndexCount(int primitiveCount, ePrimitiveType primitiveType);

};


#endif // _RENDERER_H_