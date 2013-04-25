#include "PTEngine.h"
#include "Shapes.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

static Mesh* sCube = 0;

void Shapes::InitCube(Renderer* renderer)
{
    sCube = new Mesh();
    Submesh* submesh = new Submesh();
    sCube->AddSubmesh(submesh);
    submesh->Create(renderer, 24, VF_POSITION | VF_NORMAL | VF_UV0, 12, Renderer::ePT_Triangles);
    VertexBuffer* verts = submesh->GetVertexBuffer();
    IndexBuffer* indices = submesh->GetIndexBuffer();

    Vector3 topLeftFront(-1, 1, -1);
    Vector3 topRightFront(1, 1, -1);
    Vector3 bottomRightFront(1, -1, -1);
    Vector3 bottomLeftFront(-1, -1, -1);
    Vector3 topLeftBack(-1, 1, 1);
    Vector3 topRightBack(1, 1, 1);
    Vector3 bottomRightBack(1, -1, 1);
    Vector3 bottomLeftBack(-1, -1, 1);

    Vector3 front(0.0f, 0.0f, -1.0f);
    Vector3 right(1.0f, 0.0f, 0.0f);
    Vector3 back(0.0f, 0.0f, 1.0f);
    Vector3 left(-1.0f, 0.0f, 0.0f);
    Vector3 top(0.0f, 1.0f, 0.0f);
    Vector3 bottom(0.0f, -1.0f, 0.0f);

    int vertex = 0;
    int index = 0;
    // Front
    verts->SetPosition(vertex, topLeftFront);
    verts->SetNormal(vertex, front);
    verts->SetUV(0, vertex++, 0.0f, 0.0f);

    verts->SetPosition(vertex, topRightFront);
    verts->SetNormal(vertex, front);
    verts->SetUV(0, vertex++, 1.0f, 0.0f);

    verts->SetPosition(vertex, bottomRightFront);
    verts->SetNormal(vertex, front);
    verts->SetUV(0, vertex++, 1.0f, 1.0f);

    verts->SetPosition(vertex, bottomLeftFront);
    verts->SetNormal(vertex, front);
    verts->SetUV(0, vertex++, 0.0f, 1.0f);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Right
    verts->SetPosition(vertex, topRightFront);
    verts->SetNormal(vertex, right);
    verts->SetUV(0, vertex++, 0.0f, 0.0f);

    verts->SetPosition(vertex, topRightBack);
    verts->SetNormal(vertex, right);
    verts->SetUV(0, vertex++, 1.0f, 0.0f);

    verts->SetPosition(vertex, bottomRightBack);
    verts->SetNormal(vertex, right);
    verts->SetUV(0, vertex++, 1.0f, 1.0f);

    verts->SetPosition(vertex, bottomRightFront);
    verts->SetNormal(vertex, right);
    verts->SetUV(0, vertex++, 0.0f, 1.0f);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Back
    verts->SetPosition(vertex, topRightBack);
    verts->SetNormal(vertex, back);
    verts->SetUV(0, vertex++, 0.0f, 0.0f);

    verts->SetPosition(vertex, topLeftBack);
    verts->SetNormal(vertex, back);
    verts->SetUV(0, vertex++, 1.0f, 0.0f);

    verts->SetPosition(vertex, bottomLeftBack);
    verts->SetNormal(vertex, back);
    verts->SetUV(0, vertex++, 1.0f, 1.0f);

    verts->SetPosition(vertex, bottomRightBack);
    verts->SetNormal(vertex, back);
    verts->SetUV(0, vertex++, 0.0f, 1.0f);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Left
    verts->SetPosition(vertex, topLeftBack);
    verts->SetNormal(vertex, left);
    verts->SetUV(0, vertex++, 0.0f, 0.0f);

    verts->SetPosition(vertex, topLeftFront);
    verts->SetNormal(vertex, left);
    verts->SetUV(0, vertex++, 1.0f, 0.0f);

    verts->SetPosition(vertex, bottomLeftFront);
    verts->SetNormal(vertex, left);
    verts->SetUV(0, vertex++, 1.0f, 1.0f);

    verts->SetPosition(vertex, bottomLeftBack);
    verts->SetNormal(vertex, left);
    verts->SetUV(0, vertex++, 0.0f, 1.0f);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Top
    verts->SetPosition(vertex, topLeftBack);
    verts->SetNormal(vertex, top);
    verts->SetUV(0, vertex++, 0.0f, 0.0f);

    verts->SetPosition(vertex, topRightBack);
    verts->SetNormal(vertex, top);
    verts->SetUV(0, vertex++, 1.0f, 0.0f);

    verts->SetPosition(vertex, topRightFront);
    verts->SetNormal(vertex, top);
    verts->SetUV(0, vertex++, 1.0f, 1.0f);

    verts->SetPosition(vertex, topLeftFront);
    verts->SetNormal(vertex, top);
    verts->SetUV(0, vertex++, 0.0f, 1.0f);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Bottom
    verts->SetPosition(vertex, bottomLeftFront);
    verts->SetNormal(vertex, bottom);
    verts->SetUV(0, vertex++, 0.0f, 0.0f);

    verts->SetPosition(vertex, bottomRightFront);
    verts->SetNormal(vertex, bottom);
    verts->SetUV(0, vertex++, 1.0f, 0.0f);

    verts->SetPosition(vertex, bottomRightBack);
    verts->SetNormal(vertex, bottom);
    verts->SetUV(0, vertex++, 1.0f, 1.0f);

    verts->SetPosition(vertex, bottomLeftBack);
    verts->SetNormal(vertex, bottom);
    verts->SetUV(0, vertex++, 0.0f, 1.0f);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);
}

void Shapes::DrawCube(Renderer* renderer, Matrix4x4 ltw, Material* material)
{
    if( !sCube )
        InitCube(renderer);

    if( !material )
        material = Shapes::sDefaultMaterial;
    sCube->GetSubmesh(0)->SetMaterial(material);

    renderer->DrawMesh(sCube);
}