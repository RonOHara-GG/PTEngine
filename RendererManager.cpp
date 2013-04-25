#include "PTEngine.h"
#include "RendererManager.h"
#include "Renderer.h"

static RendererManager* sManager = 0;

RendererManager* RendererManager::GetInstance()
{
    if( !sManager )
        sManager = new RendererManager();

    return sManager;
}

RendererManager::RendererManager(void)
{
}


RendererManager::~RendererManager(void)
{
}

void RendererManager::RegisterRenderer(const char* rendererLibrary)
{
}

Renderer* RendererManager::GetRenderer(const char* rendererName)
{
}