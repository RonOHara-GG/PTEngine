#ifndef _RD3D_PLUGIN_H_
#define _RD3D_PLUGIN_H_

#include "..\Plugin.h"

class RD3DPlugin : public Plugin
{
public:
    RD3DPlugin(void);
    ~RD3DPlugin(void);

    bool Init();
};

#endif // _RD3D_PLUGIN_H_
