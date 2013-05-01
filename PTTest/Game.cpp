#include "stdafx.h"
#include "PTTest.h"

#include "..\PTEngine.h"
#include "..\Renderer.h"
#include "..\PluginManager.h"
#include "..\Shapes.h"

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
            gRenderers[0] = 0;
    }

    gRenderers[1] = PLUGIN_MANAGER->GetRenderer("OpenGL");
    if( gRenderers[1] )
    {
        if( !gRenderers[1]->Init(hWndBottom, false) )
            gRenderers[1] = 0;
    }

    for( int i = 0; i < NUM_RENDERERS; i++ )
    {
        if( gRenderers[i] )
        {
            gCubes[i] = Shapes::CreateCube(gRenderers[i]);
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
            //gRenderers[i]->SetViewMatrix(gViewMatrix);
            //gRenderers[i]->SetProjectionMatrix(gProjectionMatrix);

			
            RGBA clearColor(0.5f, 0.5f, 0.5f, 1.0f);
            gRenderers[i]->Clear(true, clearColor);

            gRenderers[i]->BeginFrame();

            if( gCubes[i] )
            {
                Matrix4x4 localToWorld;
                Shapes::DrawCube(gCubes[i], localToWorld);
            }

            gRenderers[i]->EndFrame();
            gRenderers[i]->FinishFrame();
        }
    }
}