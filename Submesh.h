#ifndef _SUBMESH_H_
#define _SUBMESH_H_

#include "Renderer.h"

class Material;
class VertexFormat;
class VertexProfile;

class Submesh : public OwnedObject
{
public:
    Submesh(Renderer::ePrimitiveType primType, int primCount, int numVertexBuffers = 1);
    virtual ~Submesh(void);

    void CreateVertexProfile(Renderer* renderer);

    VertexBuffer* GetVertexBuffer(int index = 0)    { return mVertexBuffers[index]; }
    void AddVertexBuffer(VertexBuffer* vertexBuffer, bool submeshOwnsThis = true);
    
    IndexBuffer* GetIndexBuffer()                   { return mIndexBuffer; }
    void SetIndexBuffer(IndexBuffer* indexBuffer, bool submeshOwnsThis = true);
    
    int GetPrimitiveCount()                         { return mPrimitiveCount; }
    Renderer::ePrimitiveType GetPrimitiveType()     { return mPrimitiveType; }

    Material* GetMaterial()                         { return mMaterial; }
    void SetMaterial(Material* material)            { mMaterial = material; }

    void Draw(Renderer* renderer, const Matrix4x4& ltw);

protected:
    VertexProfile* mVertexProfile;
    DynamicArray<VertexBuffer*> mVertexBuffers;

    IndexBuffer* mIndexBuffer;

    Renderer::ePrimitiveType mPrimitiveType;
    int mPrimitiveCount;
    Material* mMaterial;

};

#endif // _SUBMESH_H_