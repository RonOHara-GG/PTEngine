#include "..\PTEngine.h"
#include "RendererD3D.h"
#include "IndexBufferD3D9.h"


IndexBufferD3D9::IndexBufferD3D9(IDirect3DIndexBuffer9* ib, int indexCount, bool sixteenBit)
{
    mIB = ib;
    mIndexCount = indexCount;
    mSixteenBit = sixteenBit;
    mIndexSize = sixteenBit ? 2 : 4;
    mLockData = 0;
}


IndexBufferD3D9::~IndexBufferD3D9(void)
{
    mIB->Release();
}

void IndexBufferD3D9::Lock()
{
    if( !mLockData )
    {
        mIB->Lock(0, 0, &mLockData, 0);
    }
}

void IndexBufferD3D9::Unlock()
{
    if( mLockData )
    {
        mIB->Unlock();
        mLockData = 0;
    }
}

void IndexBufferD3D9::Set(int index, uint vertex)
{
    Lock();

    char* ptr = (char*)mLockData;
    ptr += index * mIndexSize;
    if( mSixteenBit )
    {
        *(ushort*)ptr = (ushort)vertex;
    }
    else
    {
        *(uint*)ptr = vertex;
    }
}