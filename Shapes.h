#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Renderer.h"
#include "Material.h"

namespace Shapes
{
    void Init();
    void Shutdown();

    void InitCube(Renderer* renderer);
    void DrawCube(Renderer* renderer, Matrix4x4 localToWorld, Material* material = 0);


    extern Material* sDefaultMaterial;
};

#endif // _SHAPES_H_

