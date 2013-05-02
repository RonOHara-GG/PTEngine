#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

class IndexBuffer : public OwnedObject
{
public:
    virtual ~IndexBuffer(void) {}

    virtual void Lock() = 0;
    virtual void Unlock() = 0;
    
    virtual void Set(int index, uint vertex) = 0;

    virtual void* GetBuffer() = 0;

protected:

};

#endif // _INDEX_BUFFER_H_

