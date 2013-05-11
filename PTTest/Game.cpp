#include "stdafx.h"
#include "PTTest.h"

#include "..\PTEngine.h"
#include "..\Renderer.h"
#include "..\PluginManager.h"
#include "..\FileManager.h"
#include "..\Shapes.h"
#include "..\Mesh.h"
#include "..\Material.h"
#include "..\SpriteTexture.h"

const char* gVSFiles[2] = {"BasicVertexShader.hlsl", "BasicVertexShader.glsl"};
const char* gPSFiles[2] = {"BasicPixelShader.hlsl", "BasicPixelShader.glsl"};
const char* gSpriteVSFiles[2] = {"SpriteVS.hlsl", "SpriteVS.glsl"};
const char* gSpritePSFiles[2] = {"SpritePS.hlsl", "SpritePS.glsl"};
HWND gWindows[2];

Mesh* gCubes[2] = {0, 0};
Renderer* gRenderers[2] = {0, 0};
SpriteTexture* gSprites[2] = {0, 0};
#define NUM_RENDERERS   (sizeof(gRenderers) / sizeof(Renderer*))

Matrix4x4 gOrthoMatrix;
Matrix4x4 gPerspectiveMatrix;

void InitGame(HWND hWndTop, HWND hWndBottom)
{
    PLUGIN_MANAGER->LoadPlugin("Renderer_Direct3D.dll");
    PLUGIN_MANAGER->LoadPlugin("Renderer_OpenGL.dll");
    gRenderers[0] = PLUGIN_MANAGER->GetRenderer("Direct3D");
    gRenderers[1] = PLUGIN_MANAGER->GetRenderer("OpenGL");
    gWindows[0] = hWndTop;
    gWindows[1] = hWndBottom;

    RECT rect;
    GetWindowRect(hWndTop, &rect);
    float width = (float)(rect.right - rect.left);
    float height = (float)(rect.bottom - rect.top);
    float nearz = 0.1f;
    float farz = 10000.0f;
    
    Box viewport;
    viewport.mMin.Set(0, 0, nearz);
    viewport.mMax.Set(width, height, farz);
    
    gOrthoMatrix.SetOrthographic(width, height, nearz, farz);
    gPerspectiveMatrix.SetPerspectiveFov(DEGREES_TO_RADIANS(45), width / height, nearz, farz);
    
    Matrix4x4 view;
    view.SetLook(Vector3(0.0f, 2.0f, 5.0f), Vector3(0, 0, 0), Vector3(0.0f, 1.0f, 0.0f));

    File* textureFile = FILE_MANAGER->LoadFile("Sprite.dds");
   
    for( int i = 0; i < NUM_RENDERERS; i++ )
    {
        if( gRenderers[i] )
        {
            if( gRenderers[i]->Init(gWindows[i], (int)width, (int)height, false) )
            {
                gRenderers[i]->SetViewport(viewport);
                gRenderers[i]->SetProjectionMatrix(gPerspectiveMatrix);
                gRenderers[i]->SetViewMatrix(view);

                Material* cubeMaterial = new Material();
                File* vertexShaderFile = FILE_MANAGER->LoadFile(gVSFiles[i]);
                File* pixelShaderFile = FILE_MANAGER->LoadFile(gPSFiles[i]);

                VertexShader* vs = gRenderers[i]->CreateVertexShader(vertexShaderFile->GetData(), vertexShaderFile->GetSize());
                PixelShader* ps = gRenderers[i]->CreatePixelShader(pixelShaderFile->GetData(), pixelShaderFile->GetSize());
                cubeMaterial->SetVertexShader(vs);
                cubeMaterial->SetPixelShader(ps);

                delete vertexShaderFile;
                delete pixelShaderFile;
                gCubes[i] = Shapes::CreateCube(gRenderers[i], cubeMaterial);


                vertexShaderFile = FILE_MANAGER->LoadFile(gSpriteVSFiles[i]);
                pixelShaderFile = FILE_MANAGER->LoadFile(gSpritePSFiles[i]);
                vs = gRenderers[i]->CreateVertexShader(vertexShaderFile->GetData(), vertexShaderFile->GetSize());
                ps = gRenderers[i]->CreatePixelShader(pixelShaderFile->GetData(), pixelShaderFile->GetSize());
                Material* spriteMaterial = new Material();
                spriteMaterial->SetVertexShader(vs);
                spriteMaterial->SetPixelShader(ps);
                gRenderers[i]->SetSpriteMaterial(spriteMaterial);

                delete vertexShaderFile;
                delete pixelShaderFile;	
                
                Texture* texture = gRenderers[i]->CreateTexture((DDS*)textureFile->GetData(), textureFile->GetSize());
                gSprites[i] = new SpriteTexture(texture);
                gSprites[i]->AddSprite(0, 100, width, 10);
                gSprites[i]->Finish(gRenderers[i]);
                
            }
            else
                gRenderers[i] = 0;
        }
    }

    delete textureFile;
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
    static float index = 0.0f; index+=0.025f;
    localToWorld.SetRotationY(index);

    for( int i = 0; i < NUM_RENDERERS; i++ )
    {
        if( gRenderers[i] )
        {			
            RGBA clearColor(0.5f, 0.5f, 0.5f, 1.0f);
            gRenderers[i]->Clear(true, clearColor);

            gRenderers[i]->BeginFrame();
            
            // Draw Cube
            gRenderers[i]->SetProjectionMatrix(gPerspectiveMatrix);
            if( gCubes[i] )
            {
                gCubes[i]->Draw(localToWorld);
            }

            // Draw lines
            gRenderers[i]->SetProjectionMatrix(gOrthoMatrix);
            
            gRenderers[i]->EndFrame();
            gRenderers[i]->FinishFrame();
        }
    }
}