#ifndef _DYNAMIC_LIBRARY_H_
#define _DYNAMIC_LIBRARY_H_

class DynamicLibrary
{
public:
    DynamicLibrary();
    ~DynamicLibrary();

    bool Load(const char* libraryFile);
    
    void* FindFunction(const char* functionName);

private:
    void*   mLibrary;
};


#endif // _DYNAMIC_LIBRARY_H_