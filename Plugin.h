#ifndef _PLUGIN_H_
#define _PLUGIN_H_

class DynamicLibrary;
#include "Renderer.h"

class Plugin
{
protected:
    enum eModuleType
    {
        eMT_Renderer,
    };

    struct Module
    {
        eModuleType mType;
        const char* mName;
        void*       mModulePointer;
    };


public:
    virtual ~Plugin(void);

    void SetLibrary(DynamicLibrary* library)        { mLibrary = library; }

    Renderer* FindRenderer(const char* rendererName);

protected:
    void AddModule(eModuleType type, const char* moduleName, void* modulePointer);
    Module* FindModule(eModuleType type, const char* moduleName);
    
protected:
    DynamicLibrary*         mLibrary;
    DynamicArray<Module*>   mModules;

public:
    static Plugin* LoadPlugin(const char* pluginFile);
};

inline Plugin::~Plugin()
{
    // Cleanup all modules
    for( int i = 0; i < mModules.Count(); i++ )
    {
        Module* module = mModules[i];
        if( module )
        {
            // Delete the specific module data
            switch( module->mType )
            {
                case eMT_Renderer:
                    {
                        Renderer* renderer = (Renderer*)module->mModulePointer;
                        delete renderer;
                    }
                    break;
            }

            // Delete the module structure
            delete module;
        }
    }
    mModules.Clear();
}

inline void Plugin::AddModule(eModuleType type, const char* moduleName, void* modulePointer)
{
    Module* module = new Module();
    module->mType = type;
    module->mName = moduleName;
    module->mModulePointer = modulePointer;
    mModules.Add(module);
}

#endif // _PLUGIN_H_