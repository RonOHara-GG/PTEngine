#include "..\PTEngine.h"
#include "ROGLPlugin.h"
#include "RendererOGL.h"

Memory* Memory::sInstance = 0;
Assert* Assert::sInstance = 0;

static ROGLPlugin* sPluginInstance = 0;

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

__declspec(dllexport) Plugin* GetPlugin(Memory* memoryManager, Assert* asserts)
{
    Memory::sInstance = memoryManager;
    Assert::sInstance = asserts;

    if( sPluginInstance == 0 )
    {
        sPluginInstance = new ROGLPlugin();
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

ROGLPlugin::ROGLPlugin(void)
{
}


ROGLPlugin::~ROGLPlugin(void)
{
}

bool ROGLPlugin::Init()
{
    if( !PlatformInit() )
        return false;

    AddModule(Plugin::eMT_Renderer, "OpenGL", new RendererOGL());

    return true;
}