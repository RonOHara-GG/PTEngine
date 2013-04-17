#include "RendererManager.h"

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
