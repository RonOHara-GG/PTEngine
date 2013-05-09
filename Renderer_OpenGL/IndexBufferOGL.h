#ifndef _INDEX_BUFFER_OGL_H_
#define _INDEX_BUFFER_OGL_H_

#include "..\IndexBuffer.h"

class IndexBufferOGL : public IndexBuffer
{
public:
    IndexBufferOGL(int indexCount, bool sixteenBit);
    virtual ~IndexBufferOGL(void);
        
    virtual void Lock();
    virtual void Unlock();
    
    virtual void Set(int index, uint vertex);

    uint GetBufferName()        { return mGLBufferName; }
    bool IsSixteenBit()         { return mSixteenBit; }
    int GetIndexCount()         { return mIndexCount; }

protected:
    uint mGLBufferName;
    void* mLockData;

    int mIndexCount;
    int mIndexSize;
    bool mSixteenBit;
};

#endif // _INDEX_BUFFER_OGL_H_