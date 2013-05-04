#include <Windows.h>
#undef malloc
#undef free

#include "PTEngine.h"
#include "FileManager.h"

File* FileManager::LoadFile(const char* fileName)
{
    HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if( hFile == INVALID_HANDLE_VALUE )
        return 0;

    DWORD size = GetFileSize(hFile, 0);
    void* dataBuffer = malloc(size);

    File* file = 0;
    if( ReadFile(hFile, dataBuffer, size, 0, 0) )
    {
        file = new File(dataBuffer, size);
    }
    else
    {
        free(dataBuffer);
    }

    CloseHandle(hFile);
    return file;
}