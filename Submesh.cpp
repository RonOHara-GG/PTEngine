#include "PTEngine.h"
#include "Submesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexProfile.h"
#include "Material.h"


Submesh::Submesh(Renderer::ePrimitiveType primType, int primCount, int vertexCount, int numVertexBuffers) : mVertexBuffers(numVertexBuffers)
{
    mIndexBuffer = 0;
    mMaterial = 0;
    mPrimitiveType = primType;
    mPrimitiveCount = primCount;
    mVertexCount = vertexCount;
    mVertexProfile = 0;
}

Submesh::~Submesh(void)
{
    if( mVertexProfile )
    {
        delete mVertexProfile;
        mVertexProfile = 0;
    }

    // Clear vertex buffers
    for( int i = 0; i < mVertexBuffers.Count(); i++ )
    {
        if( mVertexBuffers[i] && mVertexBuffers[i]->GetOwner() == this )
            delete mVertexBuffers[i];
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

void Submesh::CreateVertexProfile(Renderer* renderer)
{
    if( mVertexProfile )
        delete mVertexProfile;

    VertexBuffer* ptr = mVertexBuffers.Get(0);
    mVertexProfile = renderer->CreateVertexProfile((const VertexBuffer**)&ptr, mVertexBuffers.Count());
}

void Submesh::AddVertexBuffer(VertexBuffer* buffer, bool submeshOwnsThis)
{
    if( submeshOwnsThis )
        buffer->SetOwner(this);
    mVertexBuffers.Add(buffer);
}

void Submesh::SetIndexBuffer(IndexBuffer* indexBuffer, bool submeshOwnsThis)
{
    if( submeshOwnsThis )
        indexBuffer->SetOwner(this);
    mIndexBuffer = indexBuffer;
}

void Submesh::Draw(Renderer* renderer, const Matrix4x4& ltw)
{
    // Bind Material
    renderer->SetMaterial(mMaterial, ltw);

    // Bind Vertex Buffers
    renderer->SetVertexProfile(mVertexProfile);
    for( int i = 0; i < mVertexBuffers.Count(); i++ )
    {
        renderer->SetVertexBuffer(i, mVertexBuffers[i]);
    }

    // Bind Index Buffer
    renderer->SetIndexBuffer(mIndexBuffer);

    // Draw the mesh
    renderer->Draw(mVertexCount, mPrimitiveCount, mPrimitiveType);
}