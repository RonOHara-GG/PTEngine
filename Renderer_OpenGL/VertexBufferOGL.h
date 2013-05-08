#ifndef _VERTEX_BUFFER_OGL_H_
#define _VERTEX_BUFFER_OGL_H_

#include "..\VertexBuffer.h"

class VertexBufferOGL : public VertexBuffer
{
public:
    VertexBufferOGL(int vertexCount, const VertexFormat& format);
    virtual ~VertexBufferOGL(void);
    
    virtual void Lock();
    virtual void Unlock();

    virtual void SetVertexElement(int vertexIndex, int elementOffset, int elementSize, void* elementData);

    virtual void* GetBuffer();

protected:
    int mVertexCount;
    uint mGLBufferName;
};

#endif // _VERTEX_BUFFER_OGL_H_