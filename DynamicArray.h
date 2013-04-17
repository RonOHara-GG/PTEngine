#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

class DynamicArrayBase
{
protected:
    DynamicArrayBase(int itemSize, int allocationBlockCount = 10);        // Can only be constructed by DynamicArray class
    
public:
    ~DynamicArrayBase();

    void Reserve(int reserveCount);
    void Clear();
    int Count()                 { return mCount; }

protected:
    int Add(void* item);
    void* Get(int index);
    void Set(int index, void* item);
    void* operator[](int index);    

private:
    void Allocate(int count);

protected:
    void* mData;
    int mCount;
    int mAllocatedCount;
    int mAllocationBlockCount;
    int mItemSize;
};

template<class T>
class DynamicArray : public DynamicArrayBase
{
public:
    DynamicArray();

    int Add(T& item);
    T& Get(int index);
    void Set(int index, T& item);
    T& operator[](int index);
};


inline DynamicArrayBase::DynamicArrayBase(int itemSize, int allocationBlockCount)
{
    mData = 0;
    mCount = 0;
    mAllocatedCount = 0;
    mAllocationBlockCount = allocationBlockCount;
    mItemSize = itemSize;
}

inline DynamicArrayBase::~DynamicArrayBase()
{
    Clear();
}

inline void DynamicArrayBase::Allocate(int count)
{
    int newAllocCount = mAllocatedCount + count;
    void* newData = malloc(newAllocCount * mItemSize);
    if( mData )
    {
        memcpy(newData, mData, mAllocatedCount * mItemSize);
        free(mData);
    }
    mData = newData;
    mAllocatedCount = newAllocCount;
}

inline void DynamicArrayBase::Reserve(int reserveCount)
{
    int freeCount = mAllocatedCount - mCount;
    if( freeCount < reserveCount )
    {
        int count = reserveCount - freeCount;
        Allocate(count);
    }
}

inline int DynamicArrayBase::Add(void* item)
{
    // Allocate space if needed
    if( mAllocatedCount <= mCount )
        Allocate(mAllocationBlockCount);
        
    int index = mCount;
    Set(index, item);
    mCount++;
    return index;
}

inline void DynamicArrayBase::Clear()
{
    if( mData )
    {
        free(mData);
        mData = 0;
    }
    mCount = 0;
    mAllocatedCount = 0;
}
inline void DynamicArrayBase::Set(int index, void* item)
{
    ASSERT(index >= mCount && index < mAllocatedCount && index >= 0);

    char* itemPtr = (char*)mData + (index * mItemSize);
    memcpy(itemPtr, item, mItemSize);
}

inline void* DynamicArrayBase::Get(int index)
{
    ASSERT(index >= mCount && index < mAllocatedCount && index >= 0);

    char* itemPtr = (char*)mData + (index * mItemSize);
    return itemPtr;
}

inline void* DynamicArrayBase::operator[](int index)
{
    return Get(index);
}


//////////////////////////////////////////////////////////////
// Dynamic Array
//////////////////////////////////////////////////////////////
template<class T>
inline DynamicArray::DynamicArray() : DynamicArrayBase(sizeof(T))
{
}

template<class T>
inline int DynamicArray::Add(T& item)
{
    return DynamicArrayBase::Add(&item);
}

template<class T>
inline void DynamicArray::Set(int index, T& item)
{
    DynamicArrayBase::Set(index, &item);
}

template<class T>
inline T& DynamicArray::Get(int index)
{
    void* itemPtr = DynamicArrayBase::Get(index);
    return (T&)itemPtr;
}

template<class T>
inline T& DynamicArray::operator[](int index)
{
    return (T&)DynamicArrayBase::operator[index];
}

#endif // _DYNAMIC_ARRAY_H_