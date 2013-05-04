#ifndef _FILE_H_
#define _FILE_H_

class File
{
public:
    File(void* data, uint size);
    virtual ~File();

    uint GetSize()      { return mSize; }
    void* GetData()     { return mData; }

protected:
    uint    mSize;
    void*   mData;
};

#endif // _FILE_H_