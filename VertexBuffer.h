#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include "Vector3.h"
#include "Vector4.h"
#include "VertexFormat.h"

class VertexBuffer : public OwnedObject
{
public:
    virtual ~VertexBuffer(void) {}

    virtual void Lock() = 0;
    virtual void Unlock() = 0;

    virtual void SetVertexElement(int vertexIndex, int elementOffset, int elementSize, void* elementData) = 0;
    
protected:

};

#endif // _VERTEX_BUFFER_H_