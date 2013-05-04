#include "PTEngine.h"
#include "Shapes.h"
#include "Mesh.h"
#include "Submesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"

Mesh* Shapes::CreateCube(Renderer* renderer, Material* material)
{
    Mesh* mesh = new Mesh(renderer);
    Submesh* submesh = new Submesh(Renderer::ePT_Triangles, 12);
    mesh->AddSubmesh(submesh);

    VertexFormat format;
    int positionOffset = format.Add(VertexFormat::eVU_Position, VertexFormat::eVET_Float3);
    int normalOffset = format.Add(VertexFormat::eVU_Normal, VertexFormat::eVET_Float3);
    int uvOffset = format.Add(VertexFormat::eVU_UV0, VertexFormat::eVET_Float2);
    
    VertexBuffer* verts = renderer->CreateVertexBuffer(24, format);
    IndexBuffer* indices = renderer->CreateIndexBuffer(Renderer::GetPrimitiveIndexCount(12, Renderer::ePT_Triangles));
    submesh->AddVertexBuffer(verts);
    submesh->SetIndexBuffer(indices);
    submesh->CreateVertexProfile(renderer);
    submesh->SetMaterial(material);

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

    Vector3 uv00(0.0f, 0.0f, 0.0f);
    Vector3 uv01(0.0f, 0.0f, 0.0f);
    Vector3 uv10(1.0f, 0.0f, 0.0f);
    Vector3 uv11(1.0f, 1.0f, 0.0f);

    int vertex = 0;
    int index = 0;
    // Front
    verts->SetVertexElement(vertex, positionOffset, 16, &topLeftFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &front);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv00);

    verts->SetVertexElement(vertex, positionOffset, 16, &topRightFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &front);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv10);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomRightFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &front);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv11);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomLeftFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &front);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv01);
        
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Right
    verts->SetVertexElement(vertex, positionOffset, 16, &topRightFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &right);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv00);

    verts->SetVertexElement(vertex, positionOffset, 16, &topRightBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &right);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv10);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomRightBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &right);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv11);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomRightFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &right);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv01);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Back
    verts->SetVertexElement(vertex, positionOffset, 16, &topRightBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &back);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv00);

    verts->SetVertexElement(vertex, positionOffset, 16, &topLeftBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &back);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv10);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomLeftBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &back);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv11);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomRightBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &back);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv01);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Left
    verts->SetVertexElement(vertex, positionOffset, 16, &topLeftBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &left);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv00);

    verts->SetVertexElement(vertex, positionOffset, 16, &topLeftFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &left);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv10);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomLeftFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &left);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv11);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomLeftBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &left);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv01);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Top
    verts->SetVertexElement(vertex, positionOffset, 16, &topLeftBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &top);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv00);

    verts->SetVertexElement(vertex, positionOffset, 16, &topRightBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &top);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv10);

    verts->SetVertexElement(vertex, positionOffset, 16, &topRightFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &top);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv11);

    verts->SetVertexElement(vertex, positionOffset, 16, &topLeftFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &top);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv01);
        
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    // Bottom
    verts->SetVertexElement(vertex, positionOffset, 16, &bottomLeftFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &bottom);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv00);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomRightFront);
    verts->SetVertexElement(vertex, normalOffset, 16, &bottom);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv10);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomRightBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &bottom);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv11);

    verts->SetVertexElement(vertex, positionOffset, 16, &bottomLeftBack);
    verts->SetVertexElement(vertex, normalOffset, 16, &bottom);
    verts->SetVertexElement(vertex++, uvOffset, 8, &uv01);
    
    indices->Set(index++, vertex - 4);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 1);
    indices->Set(index++, vertex - 3);
    indices->Set(index++, vertex - 2);

    return mesh;
}