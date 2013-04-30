#include "PTEngine.h"
#include "DynamicLibrary.h"

#undef malloc
#undef free
#include <Windows.h>

bool DynamicLibrary::Load(const char* libraryFile)
{
    HMODULE module = LoadLibrary(libraryFile);
    mLibrary = module;
    return (module != 0);
}

void* DynamicLibrary::FindFunction(const char* functionName)
{
    void* function = GetProcAddress((HMODULE)mLibrary, functionName);
    return function;
}