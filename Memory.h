#ifndef _MEMORY_H_
#define _MEMORY_H_

class MemoryBlockInfo
{
public:        
    uint                mMarker;
    uint                mLastContiguous;
    uint                mSpace;
    int                 mAllocationLine;
    const char*         mAllocationFile;
    MemoryBlockInfo*    mNextBlock;
    MemoryBlockInfo*    mPrevBlock;
};

class Memory
{
public:
    Memory(void);

    virtual void* Allocate(uint size, const char* file, int line);
    virtual void Free(void* memory);

private:
    void OSInit();
    void* OSAllocateBlock();
    uint OSBlockSize();

    MemoryBlockInfo* AllocateBlock();

private:
    MemoryBlockInfo*    mAllocatedBlocks;
    MemoryBlockInfo*    mFreeBlocks;
    bool                mOSOutOfMemory;

public:
    static Memory*   sInstance;
};

#define malloc(size)    Memory::sInstance->Allocate(size, __FILE__, __LINE__)
#define free(pointer)   Memory::sInstance->Free(pointer)

__forceinline void* operator new(size_t size)
{
    return malloc(size);
}

inline void operator delete(void* memory)
{
    free(memory);
}

__forceinline void* operator new[](size_t size)
{
    return malloc(size);
}

inline void operator delete[](void* memory)
{
    free(memory);
}
#endif // _MEMORY_H_

