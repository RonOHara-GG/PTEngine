#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

class Renderer;
class Plugin;

class PluginManager
{
public:
    PluginManager(void);
    ~PluginManager(void);

    bool LoadPlugin(const char* pluginFile);

    Renderer* GetRenderer(const char* rendererName);

private:
    DynamicArray<Plugin*> mPlugins;

public:
    static PluginManager*  sInstance;
};

#define PLUGIN_MANAGER  (PluginManager::sInstance)

#endif // _PLUGIN_MANAGER_H_

