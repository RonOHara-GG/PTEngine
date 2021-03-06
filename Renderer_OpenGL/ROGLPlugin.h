#ifndef _ROGL_PLUGIN_H_
#define _ROGL_PLUGIN_H_

#include "..\Plugin.h"

class ROGLPlugin : public Plugin
{
public:
    ROGLPlugin(void);
    ~ROGLPlugin(void);

    bool Init();

private:
    bool PlatformInit();
};

#endif // _ROGL_PLUGIN_H_