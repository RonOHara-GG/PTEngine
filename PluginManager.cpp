#include "PTEngine.h"
#include "PluginManager.h"
#include "Plugin.h"

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
    Plugin* plugin = Plugin::LoadPlugin(pluginFile);
    if( plugin )
        mPlugins.Add(plugin);

    return (plugin != 0);
}

Renderer* PluginManager::GetRenderer(const char* rendererName)
{
    for( int i = 0; i < mPlugins.Count(); i++ )
    {
        if( mPlugins[i] )
        {
            Renderer* renderer = mPlugins[i]->FindRenderer(rendererName);
            if( renderer )
                return renderer;
        }
    }
    return 0;
}