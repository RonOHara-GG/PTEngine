#ifndef _MESH_H_
#define _MESH_H_

class Renderer;
class Submesh;
class Matrix4x4;

class Mesh : public OwnedObject
{
public:
    Mesh(Renderer* renderer);
    virtual ~Mesh(void);

    void AddSubmesh(Submesh* submesh)       { mSubmeshes.Add(submesh); }
    Submesh* GetSubmesh(int index)          { return mSubmeshes[index]; }

    void Draw(const Matrix4x4& ltw);

protected:
    DynamicArray<Submesh*>  mSubmeshes;
    Renderer*               mRenderer;
};

#endif //_MESH_H_

