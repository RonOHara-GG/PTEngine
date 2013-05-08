#include "..\PTEngine.h"
#include "..\DynamicLibrary.h"
#include "ROGLPlugin.h"
#include "glBind.h"

#pragma comment (lib, "Opengl32.lib")

bool ROGLPlugin::PlatformInit()
{
    // Load the dll
    DynamicLibrary* openGL = new DynamicLibrary();
    if( !openGL->Load("opengl32.dll") )
    {
        delete openGL;
        return false;
    }

    // Bind the gl functions
    glBind(openGL);
    return true;
}