#include "stdafx.h"
#include "PTTest.h"

#include "..\PTEngine.h"
#include "..\Renderer.h"
#include "..\PluginManager.h"
#include "..\Shapes.h"

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
        gRenderers[0]->Init(hWndTop, false);

    gRenderers[1] = PLUGIN_MANAGER->GetRenderer("OpenGL");
    if( gRenderers[1] )
        gRenderers[1]->Init(hWndBottom, false);

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


            RGBA ClearColor(1.0f, 0.5f, 0, 1.0f);
            gRenderers[i]->Clear(true, ClearColor);

            gRenderers[i]->BeginFrame();

            //Matrix4x4 localToWorld;
            //Shapes::DrawCube(gRenderers[i], localToWorld);

            gRenderers[i]->EndFrame();
            gRenderers[i]->FinishFrame();
        }
    }
}