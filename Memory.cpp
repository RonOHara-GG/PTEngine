#include "PTEngine.h"
#include "Memory.h"

// Instantiate static memory object
static bool sMemoryInitialized = false;
static Memory instance;

Memory::Memory(void)
{
    ASSERT(!sMemoryInitialized);
    sMemoryInitialized = true;
    sInstance = this;

    mAllocatedBlocks = 0;
    mFreeBlocks = 0;
    mOSOutOfMemory = false;

    // Initialize OS memory system
    OSInit();

    // Allocate an initial block of memory
    AllocateBlock();
}

void Memory::AllocateBlock()
{
    // Get memory from the OS
    void* memory = OSAllocateBlock();
    
    // Setup the memory block
    memory->mPageSize = OSPageSize();
    memory->mFreeSpace = memory->mPageSize - (sizeof(OSMemoryPageInfo) + sizeof(MemoryBlockInfo));
    memory->mLargestFreeBlock = (MemoryBlockInfo*)(memory + 1);
    memory->mNextPage = 0;
    memory->mPrevPage = 0;
    
    // Setup an initial allocation block
    memory->mLargestFreeBlock->mBlockSize = memory->mFreeSpace;
    memory->mLargestFreeBlock->mAllocationLine = -1;

    // Add to the free list
    if( mFreePages )
    {
        OSMemoryPageInfo* lastFreePage = mFreePages;
        while( lastFreePage->mNextPage )
            lastFreePage = lastFreePage->mNextPage;
        lastFreePage->mNextPage = memory;
        memory->mPrevPage = lastFreePage;
    }
    else
        mFreePages = memory;    
}

void* Memory::Allocate(uint size, const char* file, int line)
{
    // Make sure we can even handle this size of allocation
    if( size > OSBlockSize() ) 
        return 0;

    // Find a free block large enough for this allocation
    MemoryBlockInfo* freeBlock = mFreeBlocks;
    void* memory = 0;
    while( freeBlock && memory == 0)
    {
        if( freeBlock->mSpace >= size )
        {
            // This block has enough space for this allocation
            freeBlock->mAllocationFile = file;
            freeBlock->mAllocationLine = line;            

            // Remove the block from the free list
            if( freeBlock->mPrevBlock )
                freeBlock->mPrevBlock->mNextBlock = freeBlock->mNextBlock;
            if( freeBlock->mNextBlock )
                freeBlock->mNextBlock->mPrevBlock = freeBlock->mPrevBlock;

            // Check to see if we need to create a remainder free space block
            uint extraSpace = freeBlock->mSpace - size;
            if( extraSpace > sizeof(MemoryBlockInfo) )
            {
                // Create a new block for the extra space
                MemoryBlockInfo* extraBlock = (MemoryBlockInfo*)((char*)freeBlock + sizeof(MemoryBlockInfo) + size);
                extraBlock->mSpace = extraSpace - sizeof(MemoryBlockInfo);
                extraBlock->mLastContiguous = size + sizeof(MemoryBlockInfo);
                extraBlock->mMarker = freeBlock->mMarker;
                freeBlock->mMarker |= 1;

                // Add the new extra space block to the free list
                extraBlock->mNextBlock = mFreeBlocks;
                mFreeBlocks->mPrevBlock = extraBlock;
                mFreeBlocks = extraBlock;
            }
            
            // Add this block to the allocated list
            freeBlock->mNextBlock = mAllocatedBlocks;
            if( mAllocatedBlocks )
                mAllocatedBlocks->mPrevBlock = freeBlock;
            mAllocatedBlocks = freeBlock;
        }

        freeBlock = freeBlock->mNextBlock;
    }
}

void Memory::Free(void* memory)
{
    // Get the block header
    MemoryBlockInfo* block = (MemoryBlockInfo*)memory - 1;
    bool validBlock = (block->mMarker & 0xFFFFFFFE) == 0xAAAAAAAA;
    ASSERT(validBlock);
    if( validBlock )
    {
        // Remove the block from the allocated list
        if( block->mPrevBlock )
            block->mPrevBlock->mNextBlock = block->mNextBlock;
        if( block->mNextBlock )
            block->mNextBlock->mPrevBlock = block->mPrevBlock;

        // Attempt to merge up

        // Attempt to merge down

        // Add to the free list
    }
}
