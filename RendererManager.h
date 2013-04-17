#ifndef _RENDERER_MANAGER_H_
#define _RENDERER_MANAGER_H_

class RendererManager
{
public:
    static RendererManager* GetInstance();

private:
    RendererManager(void);
    ~RendererManager(void);

};

#endif // _RENDERER_MANAGER_H_
