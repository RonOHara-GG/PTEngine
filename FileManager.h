#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include "File.h"

class FileManager
{
public:
    FileManager(void);
    ~FileManager(void);

    File* LoadFile(const char* fileName);
    
public:
    static FileManager*  sInstance;
};

#define FILE_MANAGER  (FileManager::sInstance)

#endif // _FILE_MANAGER_H_
