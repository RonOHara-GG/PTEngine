#include "PTEngine.h"
#include "Submesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Material.h"


Submesh::Submesh(void)
{
    memset(mVertexBuffers, 0, sizeof(mVertexBuffers));
    mIndexBuffer = 0;
    mMaterial = 0;
    mPrimitiveCount = 0;
}

Submesh::~Submesh(void)
{
    // Clear vertex buffers
    for( int i = 0; i < MAX_VERTEX_BUFFERS; i++ )
    {
        SetVertexBuffer(i, 0);
    }

    // Destroy the index buffer
    if( mIndexBuffer && mIndexBuffer->GetOwner() == this )
    {
        delete mIndexBuffer;
        mIndexBuffer = 0;
    }

    // Destroy the material
    if( mMaterial && mMaterial->GetOwner() == this )
    {
        delete mMaterial;
        mMaterial = 0;
    }
}

bool Submesh::Create(Renderer* renderer, int vertexCount, const VertexFormat& vertexFormat, int primitiveCount, Renderer::ePrimitiveType primType, bool sixteenBitIndices, bool dynamicVB)
{
    // Create vertex buffer
    VertexBuffer* vb = renderer->CreateVertexBuffer(vertexCount, vertexFormat, dynamicVB);
    if( !vb )
        return false;
    SetVertexBuffer(0, vb);

    // Create index buffer
    mIndexBuffer = renderer->CreateIndexBuffer(Renderer::GetPrimitiveIndexCount(primitiveCount, primType), sixteenBitIndices);
    if( !mIndexBuffer )
        return false;

    return true;
}

void Submesh::SetVertexBuffer(int index, VertexBuffer* buffer)
{
    if( index >= 0 && index < MAX_VERTEX_BUFFERS )
    {
        // Clear any existing vertex buffer in this spot if we own it
        if( mVertexBuffers[index] && mVertexBuffers[index]->GetOwner() == this )
        {
            delete mVertexBuffers[index];
        }
        mVertexBuffers[index] = buffer;
    }
}