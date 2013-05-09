#include "..\PTEngine.h"
#include "RendererOGL.h"
#include "VertexBufferOGL.h"


VertexBufferOGL::VertexBufferOGL(int vertexCount, const VertexFormat& format)
{
    mLockData = 0;
    mVertexFormat = format;
    mVertexCount = vertexCount;

    glGenBuffers(1, &mGLBufferName);
}

VertexBufferOGL::~VertexBufferOGL(void)
{
    if( mLockData )
    {
        free(mLockData);
        mLockData = 0;
    }
    glDeleteBuffers(1, &mGLBufferName);
}

void VertexBufferOGL::Lock()
{
    if( !mLockData )
    {
        mLockData = malloc(mVertexCount * mVertexFormat.GetSize());
    }
}

void VertexBufferOGL::Unlock()
{
    if( mLockData )
    {
        glBindBuffer(GL_ARRAY_BUFFER, mGLBufferName);
        glBufferData(GL_ARRAY_BUFFER, mVertexCount * mVertexFormat.GetSize(), mLockData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        free(mLockData);
        mLockData = 0;
    }
}

void VertexBufferOGL::SetVertexElement(int vertexIndex, int elementOffset, int elementSize, void* elementData)
{
    Lock();
    ASSERT(mLockData);

    char* ptr = (char*)mLockData;
    ptr += vertexIndex * mVertexFormat.GetSize();
    ptr += elementOffset;
    memcpy(ptr, elementData, elementSize);
}