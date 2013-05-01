#include "..\PTEngine.h"
#include "RendererD3D.h"
#include "VertexBufferD3D9.h"

VertexBufferD3D9::VertexBufferD3D9(IDirect3DVertexBuffer9* vb, const VertexFormat& format)
{
    mVB = vb;
    mLockedData = 0;
    mVertexFormat = format;
}

VertexBufferD3D9::~VertexBufferD3D9(void)
{
    Unlock();
    mVB->Release();
}

void VertexBufferD3D9::Lock()
{
    if( !mLockedData )
    {
        mVB->Lock(0, 0, &mLockedData, 0);
    }
}

void VertexBufferD3D9::Unlock()
{
    if( mLockedData )
    {
        mVB->Unlock();
        mLockedData = 0;
    }
}

void VertexBufferD3D9::SetVertexElement(int vertexIndex, int elementOffset, int elementSize, void* elementData)
{
    Lock();

    char* ptr = (char*)mLockedData;
    ptr += (vertexIndex * mVertexFormat.GetSize()) + elementOffset;
    memcpy(ptr, elementData, elementSize);
}