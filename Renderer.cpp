#include "PTEngine.h"
#include "Renderer.h"

int Renderer::GetPrimitiveIndexCount(int primitiveCount, ePrimitiveType primitiveType)
{
    int count = 0;
    switch( primitiveType )
    {
        case ePT_Triangles:
            count = primitiveCount * 3;
            break;
        case ePT_TriangleStrip:
            count = 3 + (primitiveCount - 1);
            break;
        case ePT_TriangleFan:
            count = 1 + primitiveCount;
            break;
        case ePT_Lines:
            count = 1 + primitiveCount;
            break;
    }
    return count;
}