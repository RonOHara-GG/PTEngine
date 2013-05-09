#include "..\PTEngine.h"
#include "RendererOGL.h"
#include "glBind.h"

#undef malloc
#undef free
#include <Windows.h>
#include <stdio.h>

#pragma comment (lib, "Opengl32.lib")

static HWND     sWindow = 0;
static HDC		sDeviceContext = 0;
static HGLRC	sRenderContext = 0;
static HMODULE  sOpenGLDLL = 0;

void* WinGLFindFunction(const char* functionName)
{
    DWORD err;
    void* functionAddress = wglGetProcAddress(functionName);
    if( functionAddress == 0 )
    {
        err = GetLastError();
        if( err == 127 )
        {
            functionAddress = GetProcAddress(sOpenGLDLL, functionName);
            if( !functionAddress )
                err = GetLastError();
        }

        if( !functionAddress )
        {
            char debugStr[4096];
            sprintf(debugStr, "Failed to find gl function(%d): %s\n", err, functionName);
            OutputDebugString(debugStr);
        }
    }
    return functionAddress;
}

bool RendererOGL::PlatformInit(void* window, int width, int height, bool fullScreen)
{
    static	PIXELFORMATDESCRIPTOR pfd=	
	{
		sizeof(PIXELFORMATDESCRIPTOR),	1,								
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,	
		PFD_TYPE_RGBA,
		32,											
		0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 24, 0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	sWindow = (HWND)window;

	sDeviceContext = GetDC(sWindow);
	if( sDeviceContext == 0 )
		return false;

	GLuint pixelFormat = ChoosePixelFormat(sDeviceContext, &pfd);
	if( !pixelFormat )
		return false;

	if( !SetPixelFormat(sDeviceContext, pixelFormat, &pfd) )
		return false;

	sRenderContext = wglCreateContext(sDeviceContext);
	DWORD err = GetLastError();
	if( sRenderContext == 0 )
		return false;

	if( !wglMakeCurrent(sDeviceContext, sRenderContext) )
	{
		wglDeleteContext(sRenderContext);
		sRenderContext = 0;
		return false;
	}

    // Bind the gl functions
    sOpenGLDLL = LoadLibrary("opengl32.dll");
    glBind(WinGLFindFunction);
    return true;
}

void RendererOGL::PlatformShutdown()
{
    wglDeleteContext(sRenderContext);
	ReleaseDC(sWindow, sDeviceContext);
}

void RendererOGL::PlatformFinishFrame()
{    
	SwapBuffers(sDeviceContext);
}