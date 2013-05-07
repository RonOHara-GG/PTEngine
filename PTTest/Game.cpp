#include "stdafx.h"
#include "PTTest.h"

#include "..\PTEngine.h"
#include "..\Renderer.h"
#include "..\PluginManager.h"
#include "..\FileManager.h"
#include "..\Shapes.h"
#include "..\Mesh.h"
#include "..\Material.h"

Material* gMaterials[2] = {0,0};
Mesh* gCubes[2] = {0, 0};
Renderer* gRenderers[2] = {0, 0};
#define NUM_RENDERERS   (sizeof(gRenderers) / sizeof(Renderer*))



Matrix4x4 gViewMatrix;
Matrix4x4 gProjectionMatrix;

void InitGame(HWND hWndTop, HWND hWndBottom)
{
    PLUGIN_MANAGER->LoadPlugin("Renderer_Direct3D.dll");
    PLUGIN_MANAGER->LoadPlugin("Renderer_OpenGL.dll");

    gRenderers[0] = PLUGIN_MANAGER->GetRenderer("Direct3D");
    if( gRenderers[0] )
    {
        if( !gRenderers[0]->Init(hWndTop, false) )
        {
            gRenderers[0] = 0;
        }
        else
        {            
            gMaterials[0] = new Material();
            File* vertexShaderFile = FILE_MANAGER->LoadFile("BasicVertexShader.hlsl");
            File* pixelShaderFile = FILE_MANAGER->LoadFile("BasicPixelShader.hlsl");

            VertexShader* vs = gRenderers[0]->CreateVertexShader(vertexShaderFile->GetData(), vertexShaderFile->GetSize());
            gMaterials[0]->SetVertexShader(vs);

            PixelShader* ps = gRenderers[0]->CreatePixelShader(pixelShaderFile->GetData(), pixelShaderFile->GetSize());
            gMaterials[0]->SetPixelShader(ps);
        }
    }

    gRenderers[1] = PLUGIN_MANAGER->GetRenderer("OpenGL");
    if( gRenderers[1] )
    {
        if( !gRenderers[1]->Init(hWndBottom, false) )
            gRenderers[1] = 0;
    }
    
    RECT rect;
    GetWindowRect(hWndTop, &rect);
    Box viewport;
    viewport.mMin.Set((float)rect.left, (float)rect.top, 0.1f);
    viewport.mMax.Set((float)rect.right, (float)rect.bottom, 50000.0f);
    
    Matrix4x4 perspective;
    perspective.SetPerspective((float)rect.right - rect.left, (float)rect.bottom - rect.top, 0.1f, 50000.0f, true);
    
    Matrix4x4 view;
    view.SetLook(Vector3(0.0f, 0.0f, -10.0f), Vector3(0, 0, 0), Vector3(0.0f, 1.0f, 0.0f));
   
    for( int i = 0; i < NUM_RENDERERS; i++ )
    {
        if( gRenderers[i] )
        {            
            gRenderers[i]->SetViewport(viewport);
            gRenderers[i]->SetProjectionMatrix(perspective);
            gRenderers[i]->SetViewMatrix(view);

			gCubes[i] = Shapes::CreateCube(gRenderers[i], gMaterials[i]);
        }
    }
}

void ShutdownGame()
{
    for( int i = 0; i < NUM_RENDERERS; i++ )
    {
        if( gRenderers[i] )
           gRenderers[i]->Shutdown();
    }
}

void DoFrame()
{
    for( int i = 0; i < NUM_RENDERERS; i++ )
    {
        if( gRenderers[i] )
        {			
            RGBA clearColor(0.5f, 0.5f, 0.5f, 1.0f);
            gRenderers[i]->Clear(true, clearColor);

            gRenderers[i]->BeginFrame();

            if( gCubes[i] )
            {
                Matrix4x4 localToWorld;
                gCubes[i]->Draw(localToWorld);
            }

            gRenderers[i]->EndFrame();
            gRenderers[i]->FinishFrame();
        }
    }
}