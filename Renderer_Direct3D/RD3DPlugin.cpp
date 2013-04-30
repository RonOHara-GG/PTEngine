#include "..\PTEngine.h"
#include "RD3DPlugin.h"
#include "RendererD3D.h"

Memory* Memory::sInstance = 0;
Assert* Assert::sInstance = 0;

static RD3DPlugin* sPluginInstance = 0;

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

__declspec(dllexport) Plugin* GetPlugin(Memory* memoryManager, Assert* asserts)
{
    Memory::sInstance = memoryManager;
    Assert::sInstance = asserts;

    if( sPluginInstance == 0 )
    {
        sPluginInstance = new RD3DPlugin();
        if( !sPluginInstance->Init() )
        {
            delete sPluginInstance;
            sPluginInstance = 0;
        }
    }

    return sPluginInstance;
}

#ifdef __cplusplus
}
#endif

RD3DPlugin::RD3DPlugin(void)
{
}


RD3DPlugin::~RD3DPlugin(void)
{
}

bool RD3DPlugin::Init()
{
    AddModule(Plugin::eMT_Renderer, "Direct3D", new RendererD3D());

    return true;
}