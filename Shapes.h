#ifndef _SHAPES_H_
#define _SHAPES_H_

class Renderer;
class Material;
class Mesh;
class Matrix4x4;

namespace Shapes
{
    void Init();
    void Shutdown();

    Mesh* CreateCube(Renderer* renderer, Material* material = 0);

};

#endif // _SHAPES_H_

