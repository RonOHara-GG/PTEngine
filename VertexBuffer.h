#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include "Renderer.h";

#define VF_POSITION     0x00000001
#define VF_NORMAL       0x00000002
#define VF_UV0          0x00000004


class VertexBuffer : public OwnedObject
{
public:
    VertexBuffer(void);
    ~VertexBuffer(void);

    void Lock();
    void Unlock();
    
    void SetPosition(int vertexIndex, float x, float y, float z);
    void SetPosition(int vertexIndex, float x, float y, float z, float w);
    void SetPosition(int vertexIndex, Vector3 position);
    void SetPosition(int vertexIndex, Vector4 position);
    
    void SetNormal(int vertexIndex, float x, float y, float z);
    void SetNormal(int vertexIndex, float x, float y, float z, float w);
    void SetNormal(int vertexIndex, Vector3 normal);
    void SetNormal(int vertexIndex, Vector4 normal);
    
    void SetUV(int uvChannel, int vertexIndex, float u, float v);
    void SetUV(int uvChannel, int vertexIndex, float u, float v, float s);
    void SetUV(int uvChannel, int vertexIndex, float u, float v, float s, float t);
    void SetUV(int uvChannel, int vertexIndex, Vector3 uv);
    void SetUV(int uvChannel, int vertexIndex, Vector4 uv);
    
protected:

};

#endif // _VERTEX_BUFFER_H_