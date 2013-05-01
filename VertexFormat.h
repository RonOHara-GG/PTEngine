#ifndef _VERTEX_FORMAT_H_
#define _VERTEX_FORMAT_H_

class VertexFormat
{
public:
    enum VertexUsage
    {
        eVU_Position,
        eVU_Normal,
        eVU_UV0,
    };
    enum VertexElementType
    {
        eVET_Float,
        eVET_Float2,
        eVET_Float3,
        eVET_Float4,
        eVET_Int,
        eVET_Int2,
        eVET_Int3,
        eVET_Int4
    };

    struct VertexElement
    {
        VertexUsage         mUsage;
        VertexElementType   mType;

        VertexElement(VertexUsage usage, VertexElementType type)        { mUsage = usage; mType = type; }
    };

    VertexFormat()
    {
        mSize = 0;
    }

    int Add(VertexUsage usage, VertexElementType type);
    int GetSize() const         { return mSize; }

protected:
    DynamicArray<VertexElement> mElements;
    int                         mSize;
};

inline int VertexFormat::Add(VertexUsage usage, VertexElementType type)
{
    int offset = mSize;
    mElements.Add(VertexElement(usage, type));
    switch( type )
    {
        case eVET_Float:
        case eVET_Int:
            mSize += 4;
            break;
        case eVET_Float2:
        case eVET_Int2:
            mSize += 8;
            break;
        case eVET_Float3:
        case eVET_Int3:
            mSize += 12;
            break;
        case eVET_Float4:
        case eVET_Int4:
            mSize += 16;
            break;
    }
    return offset;
}


#endif // _VERTEX_FORMAT_H_