#include "..\PTEngine.h"
#include "RendererD3D.h"
#include "VertexBufferD3D9.h"

#pragma comment (lib, "d3d9.lib")

RendererD3D::RendererD3D(void)
{
    mDevice = 0;
}


RendererD3D::~RendererD3D(void)
{
}

bool RendererD3D::Init(void* window, bool fullScreen)
{
    IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS presentParams;
    memset(&presentParams, 0, sizeof(presentParams));
    presentParams.Windowed = fullScreen ? FALSE : TRUE;
    presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParams.hDeviceWindow = (HWND)window;

    if( d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &presentParams, &mDevice) != D3D_OK )
        return false;

    return true;
}

void RendererD3D::Shutdown()
{
}

void RendererD3D::BeginFrame()
{
    mDevice->BeginScene();
}

void RendererD3D::EndFrame()
{
    mDevice->EndScene();
}

void RendererD3D::FinishFrame()
{
    mDevice->Present(NULL, NULL, NULL, NULL);
}

void RendererD3D::SetViewport(Box viewSpace)
{
}

void RendererD3D::GetViewport(Box& viewSpace)
{
}

void RendererD3D::SetViewMatrix(const Matrix4x4& view)
{
}

void RendererD3D::SetProjectionMatrix(const Matrix4x4& projection)
{
}

void RendererD3D::Clear(bool bClearColor, const RGBA& color, bool bClearDepth, float depthValue, bool bClearStencil, unsigned int stencilValue)
{
    DWORD flags = 0;
    flags |= (bClearColor) ? D3DCLEAR_TARGET : 0;
    //flags |= (bClearDepth) ? D3DCLEAR_ZBUFFER : 0;
    //flags |= (bClearStencil) ? D3DCLEAR_STENCIL : 0;

    int a = (int)(color.mAlpha * 255);
    int r = (int)(color.mRed * 255);
    int g = (int)(color.mGreen * 255);
    int b = (int)(color.mBlue * 255);
    D3DCOLOR clearColor = D3DCOLOR_ARGB(a, r, g, b);

    mDevice->Clear(0, NULL, flags, clearColor, depthValue, stencilValue);
}

VertexBuffer* RendererD3D::CreateVertexBuffer(int vertexCount, const VertexFormat& format, bool dynamic)
{   
    VertexBufferD3D9* vb = 0;

    int vertexSize = format.GetSize();
    DWORD flags = 0;
    flags |= dynamic ? D3DUSAGE_DYNAMIC : 0;

    IDirect3DVertexBuffer9* vbd3d = 0;
    HRESULT res = mDevice->CreateVertexBuffer(vertexCount * vertexSize, flags, 0, D3DPOOL_DEFAULT, &vbd3d, 0);
    if( res == D3D_OK )
    {
        vb = new VertexBufferD3D9(vbd3d, format);
    }

    return vb;
}

IndexBuffer* RendererD3D::CreateIndexBuffer(int indexCount, bool sixteenBit)
{
    return 0;
}

void RendererD3D::DrawMesh(Mesh* mesh)
{
}