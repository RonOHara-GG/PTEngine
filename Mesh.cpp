#include "PTEngine.h"
#include "Mesh.h"
#include "Submesh.h"


Mesh::Mesh(Renderer* renderer)
{
    mRenderer = renderer;
}

Mesh::~Mesh(void)
{
    for( int i = 0; i < mSubmeshes.Count(); i++ )
    {
        if( mSubmeshes[i] && mSubmeshes[i]->GetOwner() == this )
        {
            delete mSubmeshes[i];
        }
    }
    mSubmeshes.Clear();
}

void Mesh::Draw(const Matrix4x4& ltw)
{
}