#include "stdafx.h"
#include "PTTest.h"

#include "..\PTEngine.h"
#include "..\Renderer.h"
#include "..\RendererManager.h"
#include "..\Shapes.h"

Renderer* gRenderer = 0;
Matrix4x4 gViewMatrix;
Matrix4x4 gProjectionMatrix;

void InitGame(HWND hWnd)
{
    RendererManager::GetInstance()->RegisterRenderer("Renderer_Direct3D.dll");
    RendererManager::GetInstance()->RegisterRenderer("Renderer_OpenGL.dll");

    gRenderer = RendererManager::GetInstance()->GetRenderer("Direct3D");
    gRenderer->Init(hWnd);


}

void ShutdownGame()
{
    gRenderer->Shutdown();
}

void DoFrame()
{
    gRenderer->SetViewMatrix(gViewMatrix);
    gRenderer->SetProjectionMatrix(gProjectionMatrix);

    gRenderer->BeginFrame();

    RGBA ClearColor(1.0f, 0.5f, 0, 1.0f);
    gRenderer->Clear(true, ClearColor);

    Matrix4x4 localToWorld;
    Shapes::DrawCube(gRenderer, localToWorld);

    gRenderer->EndFrame();
    gRenderer->FinishFrame();
}