#include "PTEngine.h"
#include "FileManager.h"

FileManager theFileManager;
FileManager* FileManager::sInstance = 0;

FileManager::FileManager(void)
{
    ASSERT(sInstance == 0);
    sInstance = this;
}

FileManager::~FileManager(void)
{
}