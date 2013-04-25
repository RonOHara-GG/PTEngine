#ifndef _OWNED_OBJECT_H_
#define _OWNED_OBJECT_H_

class OwnedObject
{
protected:
    OwnedObject()   { mOwner = 0; }

public:
    void* GetOwner()                { return mOwner; }
    void SetOwner(void* owner)      { mOwner = owner; }

protected:
    void* mOwner;
};

#endif // _OWNED_OBJECT_H_