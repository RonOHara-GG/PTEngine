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

    
    RECT rect;
    GetWindowRect(hWndTop, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    gRenderers[0] = PLUGIN_MANAGER->GetRenderer("Direct3D");
    if( gRenderers[0] )
    {
        if( !gRenderers[0]->Init(hWndTop, width, height, false) )
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
        if( !gRenderers[1]->Init(hWndBottom, width, height, false) )
            gRenderers[1] = 0;
    }
    
    Box viewport;
    viewport.mMin.Set(0, 0, 0.1f);
    viewport.mMax.Set((float)width, (float)height, 50000.0f);
    
    Matrix4x4 perspective;
    perspective.SetPerspectiveFov(DEGREES_TO_RADIANS(45), (float)width / (float)height, 1.0f, 100.0f);
    
    Matrix4x4 view;
    view.SetLook(Vector3(0.0f, 2.0f, -10.0f), Vector3(0, 0, 1), Vector3(0.0f, 1.0f, 0.0f));
   
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
    Matrix4x4 localToWorld;
    static float index = 0.0f; index+=0.05f;
    localToWorld.SetRotationY(index);

    for( int i = 0; i < NUM_RENDERERS; i++ )
    {
        if( gRenderers[i] )
        {			
            RGBA clearColor(0.5f, 0.5f, 0.5f, 1.0f);
            gRenderers[i]->Clear(true, clearColor);

            gRenderers[i]->BeginFrame();

            if( gCubes[i] )
            {
                
                gCubes[i]->Draw(localToWorld);
            }
            
            gRenderers[i]->EndFrame();
            gRenderers[i]->FinishFrame();
        }
    }
}