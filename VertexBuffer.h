#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include "Vector3.h"
#include "Vector4.h"

#define VF_POSITION     0x00000001
#define VF_NORMAL       0x00000002
#define VF_UV0          0x00000004


class VertexBuffer : public OwnedObject
{
public:
    virtual ~VertexBuffer(void) {}

    virtual void Lock() = 0;
    virtual void Unlock() = 0;
    
    virtual void SetPosition(int vertexIndex, float x, float y, float z) = 0;
    virtual void SetPosition(int vertexIndex, float x, float y, float z, float w) = 0;
    virtual void SetPosition(int vertexIndex, Vector3 position) = 0;
    virtual void SetPosition(int vertexIndex, Vector4 position) = 0;
    
    virtual void SetNormal(int vertexIndex, float x, float y, float z) = 0;
    virtual void SetNormal(int vertexIndex, float x, float y, float z, float w) = 0;
    virtual void SetNormal(int vertexIndex, Vector3 normal) = 0;
    virtual void SetNormal(int vertexIndex, Vector4 normal) = 0;
    
    virtual void SetUV(int uvChannel, int vertexIndex, float u, float v) = 0;
    virtual void SetUV(int uvChannel, int vertexIndex, float u, float v, float s) = 0;
    virtual void SetUV(int uvChannel, int vertexIndex, float u, float v, float s, float t) = 0;
    virtual void SetUV(int uvChannel, int vertexIndex, Vector3 uv) = 0;
    virtual void SetUV(int uvChannel, int vertexIndex, Vector4 uv) = 0;
    
protected:

};

#endif // _VERTEX_BUFFER_H_