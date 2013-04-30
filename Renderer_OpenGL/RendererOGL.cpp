#include "..\PTEngine.h"
#include "RendererOGL.h"

#include <gl\GL.h>

#pragma comment (lib, "OpenGL32.lib")

RendererOGL::RendererOGL(void)
{
	mDeviceContext = 0;
	mRenderContext = 0;
}

RendererOGL::~RendererOGL(void)
{
	wglDeleteContext(mRenderContext);
	ReleaseDC(mWindow, mDeviceContext);
}

bool RendererOGL::Init(void* window, bool fullScreen)
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

	mWindow = (HWND)window;

	mDeviceContext = GetDC(mWindow);
	if( mDeviceContext == 0 )
		return false;

	GLuint pixelFormat = ChoosePixelFormat(mDeviceContext, &pfd);
	if( !pixelFormat )
		return false;

	if( !SetPixelFormat(mDeviceContext, pixelFormat, &pfd) )
		return false;

	mRenderContext = wglCreateContext(mDeviceContext);
	DWORD err = GetLastError();
	if( mRenderContext == 0 )
		return false;

	if( !wglMakeCurrent(mDeviceContext, mRenderContext) )
	{
		wglDeleteContext(mRenderContext);
		mRenderContext = 0;
		return false;
	}

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH);
	
    return true;
}

void RendererOGL::Shutdown()
{
}

void RendererOGL::BeginFrame()
{
}

void RendererOGL::EndFrame()
{
}

void RendererOGL::FinishFrame()
{
	SwapBuffers(mDeviceContext);
}

void RendererOGL::SetViewport(Box viewSpace)
{
}

void RendererOGL::GetViewport(Box& viewSpace)
{
}

void RendererOGL::SetViewMatrix(const Matrix4x4& view)
{
}

void RendererOGL::SetProjectionMatrix(const Matrix4x4& projection)
{
}

void RendererOGL::Clear(bool bClearColor, const RGBA& color, bool bClearDepth, float depthValue, bool bClearStencil, unsigned int stencilValue)
{
	GLbitfield clearBits = bClearColor ? GL_COLOR_BUFFER_BIT : 0;
	clearBits |= bClearDepth ? GL_DEPTH_BUFFER_BIT : 0;

	glClearColor(color.mRed, color.mGreen, color.mBlue, color.mAlpha);
	glClearDepth(depthValue);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

VertexBuffer* RendererOGL::CreateVertexBuffer(int vertexCount, uint vertexComponents, bool dynamic)
{
    return 0;
}

IndexBuffer* RendererOGL::CreateIndexBuffer(int indexCount, bool sixteenBit)
{
    return 0;
}

void RendererOGL::DrawMesh(Mesh* mesh)
{
}