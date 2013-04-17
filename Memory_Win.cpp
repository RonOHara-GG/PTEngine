#include "PTEngine.h"
#include "Memory.h"

#include <Windows.h>

#define MEMORY_PAGE_SIZE   (512 * 1024 * 1024)    

static HANDLE sWinHeap = 0;

void Memory::OSInit()
{
    sWinHeap = GetProcessHeap();
}

void* Memory::OSAllocateBlock()
{
    void* memory = HeapAlloc(sWinHeap, 0, MEMORY_PAGE_SIZE);
    if( !memory )
        mOSOutOfMemory = true;
    return memory;
}

uint Memory::OSBlockSize()
{
    return MEMORY_PAGE_SIZE;
}