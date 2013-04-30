#include "PTEngine.h"
#include "Plugin.h"
#include "DynamicLibrary.h"

typedef Plugin* (*PluginAccessor)(Memory* memoryManager, Assert* asserts);

Plugin::Module* Plugin::FindModule(eModuleType type, const char* moduleName)
{
    for( int i = 0; i < mModules.Count(); i++ )
    {
        Module* module = mModules[i];
        if( module && module->mType == eMT_Renderer )
        {
            if( strcmp(module->mName, moduleName) == 0 )
                return module;
        }
    }
    return 0;
}

Renderer* Plugin::FindRenderer(const char* rendererName)
{
    Module* module = FindModule(eMT_Renderer, rendererName);
    if( module )
    {
        return (Renderer*)module->mModulePointer;
    }
    return 0;
}

Plugin* Plugin::LoadPlugin(const char* pluginFile)
{
    DynamicLibrary* lib = new DynamicLibrary();
    if( !lib->Load(pluginFile) )
    {
        delete lib;
        return 0;
    }

    PluginAccessor accessor = (PluginAccessor)lib->FindFunction("GetPlugin");
    if( !accessor )
    {
        delete lib;
        return 0;
    }

    Plugin* plugin = accessor(Memory::sInstance, Assert::sInstance);
    if( !plugin )
    {
        delete lib;
        return 0;
    }

    plugin->SetLibrary(lib);
    return plugin;
}