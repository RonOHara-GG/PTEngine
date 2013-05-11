#ifndef _SPRITE_TEXTURE_H_
#define _SPRITE_TEXTURE_H_

class Texture;
class Renderer;
class VertexBuffer;
class VertexProfile;
class Material;
class VertexShader;
class PixelShader;

class SpriteTexture
{
    struct Sprite
    {
        float x, y, width, height;
        float u,v,s,t;
        float z;
    };

public:
    SpriteTexture(Texture* texture);
    ~SpriteTexture(void);

    void AddSprite(float x, float y, float width = -1.0f, float height = -1.0f, float u = 0.0f, float v = 0.0f, float s = 1.0f, float t = 1.0f, float z = 0.0f);
    void Finish(Renderer* renderer);

    void Draw(Renderer* renderer);
    
protected:
    Texture*                mTexture;

    VertexBuffer*           mVertexBuffer;
    int                     mNumSprites;
    DynamicArray<Sprite>*   mSprites;
};

#endif // _SPRITE_TEXTURE_H_