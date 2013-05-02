#include "..\PTEngine.h"
#include "RendererD3D.h"
#include "VertexProfileD3D.h"


VertexProfileD3D::VertexProfileD3D(IDirect3DVertexDeclaration9* declaration)
{
    mDeclaration = declaration;
}


VertexProfileD3D::~VertexProfileD3D(void)
{
    mDeclaration->Release();
}
