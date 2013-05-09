#include "..\PTEngine.h"
#include "RendererOGL.h"
#include "IndexBufferOGL.h"

IndexBufferOGL::IndexBufferOGL(int indexCount, bool sixteenBit)
{
    mLockData = 0;
    mIndexCount = indexCount;
    mIndexSize = sixteenBit ? 2 : 4;
    mSixteenBit = sixteenBit;

    glGenBuffers(1, &mGLBufferName);
}

IndexBufferOGL::~IndexBufferOGL(void)
{
    if( mLockData )
    {
        free(mLockData);
        mLockData = 0;
    }
    glDeleteBuffers(1, &mGLBufferName);
}

void IndexBufferOGL::Lock()
{
    if( !mLockData )
    {
        mLockData = malloc(mIndexCount * mIndexSize);
    }
}

void IndexBufferOGL::Unlock()
{
    if( mLockData )
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mGLBufferName);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount * mIndexSize, mLockData, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        free(mLockData);
        mLockData = 0;
    }
}

void IndexBufferOGL::Set(int index, uint vertex)
{
    Lock();

    char* ptr = (char*)mLockData;
    ptr += index * mIndexSize;
    if( !mSixteenBit )
    {
        *(uint*)ptr = vertex;
    }
    else
    {
        *(ushort*)ptr = vertex;
    }
}