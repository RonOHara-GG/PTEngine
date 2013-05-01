#ifndef _VERTEX_BUFFER_D3D9_H_
#define _VERTEX_BUFFER_D3D9_H_

#include "..\VertexBuffer.h"
class Renderer;

class VertexBufferD3D9 : public VertexBuffer
{
public:
    VertexBufferD3D9(Renderer* renderer, IDirect3DVertexBuffer9* vb, const VertexFormat& format);
    virtual ~VertexBufferD3D9(void);

    virtual void Lock();
    virtual void Unlock();
    
    virtual void SetVertexElement(int vertexIndex, int elementOffset, int elementSize, void* elementData);

protected:
    Renderer*               mRenderer;
    IDirect3DVertexBuffer9* mVB;
    VertexFormat            mVertexFormat;

    void*                   mLockedData;
};

#endif // _VERTEX_BUFFER_D3D9_H_