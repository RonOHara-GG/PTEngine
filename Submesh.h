#ifndef _SUBMESH_H_
#define _SUBMESH_H_

#include "Renderer.h"

#define MAX_VERTEX_BUFFERS  4

class Submesh : public OwnedObject
{
public:
    Submesh(void);
    virtual ~Submesh(void);

    bool Create(Renderer* renderer, int vertexCount, uint vertexComponents, int primitiveCount, Renderer::ePrimitiveType primType, bool sixteenBitIndices = true, bool dynamicVB = false);

    VertexBuffer* GetVertexBuffer(int index = 0)    { return mVertexBuffers[index]; }
    void SetVertexBuffer(int index, VertexBuffer* vertexBuffer);
    
    IndexBuffer* GetIndexBuffer()                   { return mIndexBuffer; }
    
    int GetPrimitiveCount()                         { return mPrimitiveCount; }
    Renderer::ePrimitiveType GetPrimitiveType()     { return mPrimitiveType; }

    Material* GetMaterial()                         { return mMaterial; }
    void SetMaterial(Material* material)            { mMaterial = material; }

protected:
    VertexBuffer* mVertexBuffers[MAX_VERTEX_BUFFERS];
    IndexBuffer* mIndexBuffer;
    Renderer::ePrimitiveType mPrimitiveType;
    int mPrimitiveCount;
    Material* mMaterial;

};

#endif // _SUBMESH_H_