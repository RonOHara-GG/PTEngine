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

MemoryBlockInfo* Memory::AllocateBlock()
{
    // Get memory from the OS
    void* memory = OSAllocateBlock();
    
    // Setup the memory block
	MemoryBlockInfo* block = (MemoryBlockInfo*)memory;
	if( block )
	{
		block->mMarker = 0xAAAAAAAA;
		block->mLastContiguous = 0;
		block->mSpace = OSBlockSize() - sizeof(MemoryBlockInfo);
		block->mAllocationLine = 0;
		block->mAllocationFile = (const char*)0xFFFFFFFF;
		block->mNextBlock = 0;

		// Add this block to the end of the free list
		if( mFreeBlocks )
		{
			MemoryBlockInfo* free = mFreeBlocks;
			while( free->mNextBlock )
				free = free->mNextBlock;
			free->mNextBlock = block;
			block->mPrevBlock = free;
		}
		else
		{
			mFreeBlocks = block;
			block->mPrevBlock = 0;
		}
	}
	return block;
}

void* Memory::Allocate(uint size, const char* file, int line)
{
    // Make sure we can even handle this size of allocation
    if( size > OSBlockSize() ) 
        return 0;

    // Find a free block large enough for this allocation
    MemoryBlockInfo* freeBlock = mFreeBlocks;
    while( freeBlock )
    {
        if( freeBlock->mSpace >= size )
        {
            // This block has enough space for this allocation
            break;
        }

        freeBlock = freeBlock->mNextBlock;
    }

	if( !freeBlock )
	{
		// Didn't find one large enough, allocate a new one
		freeBlock = AllocateBlock();
	}
	ASSERT(freeBlock);

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

void Memory::Free(void* memory)
{
    // Get the block header
    MemoryBlockInfo* block = (MemoryBlockInfo*)memory - 1;
    bool validBlock = (block->mMarker & 0xFFFFFFFF) == 0xAAAAAAAA;
    ASSERT(validBlock);
    if( validBlock )
    {
        // Remove the block from the allocated list
        if( block->mPrevBlock )
            block->mPrevBlock->mNextBlock = block->mNextBlock;
        if( block->mNextBlock )
            block->mNextBlock->mPrevBlock = block->mPrevBlock;

        // Attempt to merge up
		if( block->mLastContiguous )
		{
			MemoryBlockInfo* prevBlock = (MemoryBlockInfo*)((char*)block - block->mLastContiguous);
			if( (block->mMarker & 0xFFFFFFFF) == 0xAAAAAAAA && prevBlock->mAllocationLine >= 0 )
			{
				// Previous block is free, we can merge up
				prevBlock->mSpace += sizeof(MemoryBlockInfo) + block->mSpace;
				block = prevBlock;
			}
		}

        // Attempt to merge down
		MemoryBlockInfo* nextBlock = (MemoryBlockInfo*)((char*)block + sizeof(MemoryBlockInfo) + block->mSpace);
		if( (block->mMarker & 0xFFFFFFFF) == 0xAAAAAAAA && nextBlock->mAllocationLine >= 0 )
		{
			// Both blocks free, remove next block from the free list
            if( nextBlock->mPrevBlock )
                nextBlock->mPrevBlock->mNextBlock = nextBlock->mNextBlock;
            if( nextBlock->mNextBlock )
                nextBlock->mNextBlock->mPrevBlock = nextBlock->mPrevBlock;

			// Merge blocks
			nextBlock->mSpace += sizeof(MemoryBlockInfo) + nextBlock->mSpace;
		}
		block->mAllocationLine = 0;

        // Add to the free list
		MemoryBlockInfo* free = mFreeBlocks;
		bool inList = false;
		while( free )
		{
			if( free == block )
			{
				inList = true;
				break;
			}
			free = free->mNextBlock;
		}
		if( !inList )
		{
			free = mFreeBlocks;
			while( free )
			{
				if( block->mSpace <= free->mSpace )
				{
					block->mNextBlock = free;
					block->mPrevBlock = free->mPrevBlock;
					free->mPrevBlock = block;
					break;
				}
				free = free->mNextBlock;
			}
		}
    }
}
