#ifndef _INDEX_BUFFER_D3D9_H_
#define _INDEX_BUFFER_D3D9_H_

#include "..\IndexBuffer.h"

class IndexBufferD3D9 : public IndexBuffer
{
public:
    IndexBufferD3D9(IDirect3DIndexBuffer9* ib, int indexCount, bool sixteenBit);
    virtual ~IndexBufferD3D9(void);

    virtual void Lock();
    virtual void Unlock();
    
    virtual void Set(int index, uint vertex);

    virtual void* GetBuffer()       { return mIB; }

protected:
    IDirect3DIndexBuffer9*  mIB;
    int                     mIndexCount;
    int                     mIndexSize;
    bool                    mSixteenBit;
    void*                   mLockData;
};

#endif // _INDEX_BUFFER_D3D9_H_