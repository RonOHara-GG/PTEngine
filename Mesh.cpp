#include "PTEngine.h"
#include "Mesh.h"


Mesh::Mesh(void)
{
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