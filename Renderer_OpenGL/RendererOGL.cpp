#include "..\PTEngine.h"
#include "RendererOGL.h"


RendererOGL::RendererOGL(void)
{
}


RendererOGL::~RendererOGL(void)
{
}

bool RendererOGL::Init(void* window, bool fullScreen)
{
    return false;
}

void RendererOGL::Shutdown()
{
}

void RendererOGL::BeginFrame()
{
}

void RendererOGL::EndFrame()
{
}

void RendererOGL::FinishFrame()
{
}

void RendererOGL::SetViewport(Box viewSpace)
{
}

void RendererOGL::GetViewport(Box& viewSpace)
{
}

void RendererOGL::SetViewMatrix(const Matrix4x4& view)
{
}

void RendererOGL::SetProjectionMatrix(const Matrix4x4& projection)
{
}

void RendererOGL::Clear(bool bClearColor, const RGBA& color, bool bClearDepth, float depthValue, bool bClearStencil, unsigned int stencilValue)
{
}

VertexBuffer* RendererOGL::CreateVertexBuffer(int vertexCount, uint vertexComponents, bool dynamic)
{
    return 0;
}

IndexBuffer* RendererOGL::CreateIndexBuffer(int indexCount, bool sixteenBit)
{
    return 0;
}

void RendererOGL::DrawMesh(Mesh* mesh)
{
}