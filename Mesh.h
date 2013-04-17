#ifndef _MESH_H_
#define _MESH_H_

#include "Submesh.h"

class Mesh : public OwnedObject
{
public:
    Mesh(void);
    virtual ~Mesh(void);

    void AddSubmesh(Submesh* submesh)       { mSubmeshes.Add(submesh); }
    Submesh* GetSubmesh(int index)          { return mSubmeshes[index]; }

protected:
    DynamicArray<Submesh*>  mSubmeshes;
};

#endif //_MESH_H_

