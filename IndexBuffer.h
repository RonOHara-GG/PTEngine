#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

#include "Renderer.h"

class IndexBuffer : public OwnedObject
{
public:
    IndexBuffer(void);
    ~IndexBuffer(void);

    void Lock();
    void Unlock();
    
    void Set(int index, uint vertex);

protected:

};

#endif // _INDEX_BUFFER_H_

