#include "PTEngine.h"
#include "PluginManager.h"

static PluginManager sPluginManager;
PluginManager* PluginManager::sInstance = 0;

PluginManager::PluginManager(void)
{
    ASSERT(sInstance == 0);
    sInstance = this;
}


PluginManager::~PluginManager(void)
{
}

bool PluginManager::LoadPlugin(const char* pluginFile)
{
    DynamicLibrary* plugin = new DynamicLibrary();
    if( plugin->Load(pluginFile) )
    {
        mPlugins.Add(plugin);
    }
    else
    {
        delete plugin;
    }
}

Renderer* PluginManager::GetRenderer(const char* rendererName)
{
    for( int i = 0; i < mPlugins.Count(); i++ )
    {
        if( mPlugins[i] )
        {
        }
    }
}