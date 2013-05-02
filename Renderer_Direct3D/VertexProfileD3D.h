#ifndef _VERTEX_PROIFLE_D3D_H_
#define _VERTEX_PROIFLE_D3D_H_

#include "..\VertexProfile.h"

class VertexProfileD3D : public VertexProfile
{
public:
    VertexProfileD3D(IDirect3DVertexDeclaration9* declaration);
    virtual ~VertexProfileD3D(void);

    IDirect3DVertexDeclaration9* GetDeclaration()   { return mDeclaration; }

protected:
    IDirect3DVertexDeclaration9*    mDeclaration;
};

#endif // _VERTEX_PROIFLE_D3D_H_