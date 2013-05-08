#include "..\PTEngine.h"
#include "RendererOGL.h"
#include "VertexBufferOGL.h"


VertexBufferOGL::VertexBufferOGL(int vertexCount, const VertexFormat& format)
{
    mVertexFormat = format;
    mVertexCount = vertexCount;

    glGenBuffers(1, &mGLBufferName);
}

VertexBufferOGL::~VertexBufferOGL(void)
{
    glDeleteBuffers(1, &mGLBufferName);
}
