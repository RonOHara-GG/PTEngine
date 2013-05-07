#include "..\PTEngine.h"
#include "..\Material.h"

#include "RendererD3D.h"
#include "VertexProfileD3D.h"
#include "VertexBufferD3D9.h"
#include "IndexBufferD3D9.h"
#include "VertexShaderD3D9.h"
#include "PixelShaderD3D9.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

RendererD3D::RendererD3D(void)
{
    mDevice = 0;
    mCurrentIndexBuffer = 0;
    mCurrentVertexProfile = 0;
    mCurrentVertexBuffers = 0;
    mCurrentMaterial = 0;
}


RendererD3D::~RendererD3D(void)
{
    if( mCurrentVertexBuffers )
    {
        free(mCurrentVertexBuffers);
        mCurrentVertexBuffers = 0;
    }
}

bool RendererD3D::Init(void* window, bool fullScreen)
{
    IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS presentParams;
    memset(&presentParams, 0, sizeof(presentParams));
    presentParams.Windowed = fullScreen ? FALSE : TRUE;
    presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParams.hDeviceWindow = (HWND)window;

    d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &mDeviceCaps);
    if( d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &presentParams, &mDevice) != D3D_OK )
        return false;
    
    mCurrentVertexBuffers = (VertexBuffer**)malloc(sizeof(VertexBuffer*) * mDeviceCaps.MaxStreams);
    memset(mCurrentVertexBuffers, 0, sizeof(VertexBuffer*) * mDeviceCaps.MaxStreams);

    mVertexShaderProfile = D3DXGetVertexShaderProfile(mDevice);
    mPixelShaderProfile = D3DXGetPixelShaderProfile(mDevice);

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

void RendererD3D::SetViewport(const Box& viewSpace)
{
    mCurrentViewport = viewSpace;

    D3DVIEWPORT9 vp;
    vp.X = (DWORD)viewSpace.mMin.mX;
    vp.Y = (DWORD)viewSpace.mMin.mY;
    vp.MinZ = viewSpace.mMin.mZ;
    vp.MaxZ = viewSpace.mMax.mZ;
    vp.Height = (DWORD)viewSpace.mMax.mY;
    vp.Width = (DWORD)viewSpace.mMax.mX;

    mDevice->SetViewport(&vp);
}

const Box& RendererD3D::GetViewport()
{
    return mCurrentViewport;
}

void RendererD3D::SetViewMatrix(const Matrix4x4& view)
{
    mViewMatrix = view;
    UpdateViewProjection();
}

void RendererD3D::SetProjectionMatrix(const Matrix4x4& projection)
{
    mProjectionMatrix = projection;
    UpdateViewProjection();
}

void RendererD3D::UpdateViewProjection()
{
    mViewProjectionMatrix = mViewMatrix * mProjectionMatrix;
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

ID3DXBuffer* RendererD3D::CompileShader(void* shaderData, uint shaderDataSize, const char* entryPoint, const char* shaderProfile)
{    
    ID3DXBuffer* d3dshader = 0;
	ID3DXBuffer* errors = 0;
    HRESULT res = D3DXCompileShader((const char*)shaderData, shaderDataSize, 0, 0, entryPoint, shaderProfile, 0, &d3dshader, &errors, 0);
    if( res == D3D_OK )
        return d3dshader;

	OutputDebugString((const char*)errors->GetBufferPointer());

    return 0;
}

VertexShader* RendererD3D::CreateVertexShader(void* shaderData, uint shaderDataSize)
{
    VertexShaderD3D9* shader = 0;

    ID3DXBuffer* d3dshader = CompileShader(shaderData, shaderDataSize, "vsmain", mVertexShaderProfile);
    if( d3dshader )
    {
        IDirect3DVertexShader9* d3dShader = 0;
        HRESULT res = mDevice->CreateVertexShader((const DWORD*)d3dshader->GetBufferPointer(), &d3dShader);
        if( res == D3D_OK )
        {
            shader = new VertexShaderD3D9(d3dShader);
        }

        d3dshader->Release();
    }

    return shader;
}

PixelShader* RendererD3D::CreatePixelShader(void* shaderData, uint shaderDataSize)
{
    PixelShaderD3D9* shader = 0;

    ID3DXBuffer* d3dshader = CompileShader(shaderData, shaderDataSize, "psmain", mPixelShaderProfile);
    if( d3dshader )
    {
        IDirect3DPixelShader9* d3dShader = 0;
        HRESULT res = mDevice->CreatePixelShader((const DWORD*)d3dshader->GetBufferPointer(), &d3dShader);
        if( res == D3D_OK )
        {
            shader = new PixelShaderD3D9(d3dShader);
        }

        d3dshader->Release();
    }

    return shader;
}

VertexProfile* RendererD3D::CreateVertexProfile(const DynamicArray<VertexBuffer*>& vertexBuffers)
{
    VertexProfileD3D* profile = 0;

    int totalElements = 1;
    for( int i = 0; i < vertexBuffers.Count(); i++ )
    {
        if( vertexBuffers[i] )
            totalElements += vertexBuffers[i]->GetVertexFormat().GetElementCount();
    }

    if( totalElements > 1 )
    {
        D3DVERTEXELEMENT9* elements = (D3DVERTEXELEMENT9*)malloc(totalElements * sizeof(D3DVERTEXELEMENT9));

        int elementIndex = 0;
        for( int i = 0; i < vertexBuffers.Count(); i++ )
        {
            if( vertexBuffers[i] )
            {
                const VertexFormat& format = vertexBuffers[i]->GetVertexFormat();
                int offset = 0;
                for( int j = 0; j < format.GetElementCount(); j++ )
                {
                    const VertexFormat::VertexElement& vertElement = format.GetElement(j);

                    D3DVERTEXELEMENT9* element = elements + elementIndex;
                    element->Stream = i;
                    element->Offset = offset;
                    element->Method = D3DDECLMETHOD_DEFAULT;

                    switch( vertElement.mType )
                    {
                        case VertexFormat::eVET_Float:
                            offset += 4;
                            element->Type = D3DDECLTYPE_FLOAT1;
                            break;
                        case VertexFormat::eVET_Float2:
                            offset += 8;
                            element->Type = D3DDECLTYPE_FLOAT2;
                            break;
                        case VertexFormat::eVET_Float3:
                            offset += 12;
                            element->Type = D3DDECLTYPE_FLOAT3;
                            break;
                        case VertexFormat::eVET_Float4:
                            offset += 16;
                            element->Type = D3DDECLTYPE_FLOAT4;
                            break;
                    }

                    switch( vertElement.mUsage )
                    {
                        case VertexFormat::eVU_Position:
                            element->Usage = D3DDECLUSAGE_POSITION;
                            element->UsageIndex = 0;
                            break;
                        case VertexFormat::eVU_Normal:
                            element->Usage = D3DDECLUSAGE_NORMAL;
                            element->UsageIndex = 0;
                            break;
                        case VertexFormat::eVU_UV0:
                            element->Usage = D3DDECLUSAGE_TEXCOORD;
                            element->UsageIndex = 0;
                            break;
                    }
                
                    elementIndex++;
                }
            }
        }
        D3DVERTEXELEMENT9 endElement = D3DDECL_END();
        elements[elementIndex] = endElement;

        IDirect3DVertexDeclaration9* decl = 0;
        HRESULT res = mDevice->CreateVertexDeclaration(elements, &decl);
        if( res == D3D_OK )
        {
            profile = new VertexProfileD3D(decl);
        }

        free(elements);
    }

    return profile;
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
    IndexBufferD3D9* ib = 0;

    int indexSize = sixteenBit ? 2 : 4;
    IDirect3DIndexBuffer9* ibd3d = 0;
    HRESULT res = mDevice->CreateIndexBuffer(indexCount * indexSize, D3DUSAGE_WRITEONLY, sixteenBit ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &ibd3d, 0);
    if( res == D3D_OK )
    {
        ib = new IndexBufferD3D9(ibd3d, indexCount, sixteenBit);
    }

    return ib;
}

Material* RendererD3D::SetMaterial(Material* material, const Matrix4x4& ltw)
{
    Material* old = mCurrentMaterial;
    mCurrentMaterial = material;

    VertexShaderD3D9* vs = (VertexShaderD3D9*)material->GetVertexShader();
    mDevice->SetVertexShader(vs->GetShader());

    Matrix4x4 wvp = ltw * mViewProjectionMatrix;
    mDevice->SetVertexShaderConstantF(0, wvp, 4);

    PixelShaderD3D9* ps = (PixelShaderD3D9*)material->GetPixelShader();
    mDevice->SetPixelShader(ps->GetShader());

    return old;
}

VertexProfile* RendererD3D::SetVertexProfile(VertexProfile* profile)
{
    VertexProfile* existing = mCurrentVertexProfile;
    mCurrentVertexProfile = profile;

    VertexProfileD3D* d3dProfile = (VertexProfileD3D*)profile;
    mDevice->SetVertexDeclaration(d3dProfile->GetDeclaration());

    return existing;
}

VertexBuffer* RendererD3D::SetVertexBuffer(uint index, VertexBuffer* vb)
{
    VertexBuffer* existing = 0;
    if( index < mDeviceCaps.MaxStreams )
    {
        existing = mCurrentVertexBuffers[index];
        mDevice->SetStreamSource(index, (IDirect3DVertexBuffer9*)vb->GetBuffer(), 0, vb->GetVertexSize());
        mCurrentVertexBuffers[index] = vb;
    }
    return existing;
}

IndexBuffer* RendererD3D::SetIndexBuffer(IndexBuffer* ib)
{
    IndexBuffer* existing = mCurrentIndexBuffer;
    mDevice->SetIndices((IDirect3DIndexBuffer9*)ib->GetBuffer());
    mCurrentIndexBuffer = ib;
    return existing;
}