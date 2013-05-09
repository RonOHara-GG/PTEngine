#ifndef _VERTEX_FORMAT_H_
#define _VERTEX_FORMAT_H_

class VertexFormat
{
public:
    enum VertexUsage
    {
        eVU_Position = 0,
        eVU_Normal,
        eVU_Color,
        eVU_UV0,
    };
    enum VertexElementType
    {
        eVET_Float,
        eVET_Float2,
        eVET_Float3,
        eVET_Float4,
        eVET_UInt,
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
    int GetElementCount() const { return mElements.Count(); }
    
    const VertexElement& GetElement(int index) const    { return mElements[index]; }


    static int GetDataSizeOfType(VertexElementType type);

protected:
    DynamicArray<VertexElement> mElements;
    int                         mSize;
};

inline int VertexFormat::GetDataSizeOfType(VertexElementType type)
{
    int size = 0;
    switch( type )
    {
        case eVET_Float:
            size += 4;
            break;
        case eVET_Float2:
            size += 8;
            break;
        case eVET_Float3:
            size += 12;
            break;
        case eVET_Float4:
            size += 16;
            break;
        case eVET_UInt:
            size += 4;
            break;
    }
    return size;
}

inline int VertexFormat::Add(VertexUsage usage, VertexElementType type)
{
    int offset = mSize;
    mElements.Add(VertexElement(usage, type));
    mSize += GetDataSizeOfType(type);
    return offset;
}


#endif // _VERTEX_FORMAT_H_