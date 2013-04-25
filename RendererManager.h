#ifndef _RENDERER_MANAGER_H_
#define _RENDERER_MANAGER_H_

class Renderer;

class RendererManager
{
public:
    static RendererManager* GetInstance();

    
    void RegisterRenderer(const char* rendererLibrary);    
    Renderer* GetRenderer(const char* rendererName);

private:
    RendererManager(void);
    ~RendererManager(void);
};

#endif // _RENDERER_MANAGER_H_
