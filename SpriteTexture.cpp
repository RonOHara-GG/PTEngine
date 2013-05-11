#include "PTEngine.h"
#include "SpriteTexture.h"
#include "Texture.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Material.h"


SpriteTexture::SpriteTexture(Texture* texture)
{
    mTexture = texture;
    mVertexBuffer = 0;
    mSprites = 0;
    mNumSprites = 0;
}

SpriteTexture::~SpriteTexture(void)
{
    if( mSprites )
        delete mSprites;
    if( mVertexBuffer )
    {
        delete mVertexBuffer;
        mVertexBuffer = 0;
    }
}

void SpriteTexture::AddSprite(float x, float y, float width, float height, float u, float v, float s, float t, float z)
{
    if( !mSprites )
        mSprites = new DynamicArray<Sprite>();

    Sprite sprite;
    sprite.x = x;
    sprite.y = y;
    sprite.z = z;
    sprite.width = width;
    sprite.height = height;
    if( width < 0 )
        sprite.width = (float)mTexture->GetWidth();
    if( height < 0 )
        sprite.height = (float)mTexture->GetHeight();
    sprite.u = u;
    sprite.v = v;
    sprite.s = s;
    sprite.t = t;
    mSprites->Add(sprite);
}

void SpriteTexture::Finish(Renderer* renderer)
{
    // Clear any existing vertex buffer
    if( mVertexBuffer )
        delete mVertexBuffer;

    // Create a new vertex buffer
    VertexFormat format;
    int positionOffset = format.Add(VertexFormat::eVU_Position, VertexFormat::eVET_Float3);
    int uvOffset = format.Add(VertexFormat::eVU_UV0, VertexFormat::eVET_Float2);
    mVertexBuffer = renderer->CreateVertexBuffer(mSprites->Count() * 6, format);

    mVertexBuffer->Lock();
    int vertex = 0;
    mNumSprites = mSprites->Count();
    for( int i = 0; i < mSprites->Count(); i++ )
    {
        const Sprite& sprite = mSprites->Get(i);

        Vector3 topLeft(sprite.x, sprite.y, sprite.z);
        Vector3 topRight(sprite.x + sprite.width, sprite.y, sprite.z);
        Vector3 bottomRight(sprite.x + sprite.width, sprite.y + sprite.height, sprite.z);
        Vector3 bottomLeft(sprite.x, sprite.y + sprite.height, sprite.z);

        Vector3 uvTopLeft(sprite.u, sprite.v, 0.0f);
        Vector3 uvTopRight(sprite.s, sprite.v, 0.0f);
        Vector3 uvBotRight(sprite.s, sprite.t, 0.0f);
        Vector3 uvBotLeft(sprite.u, sprite.t, 0.0f);

        mVertexBuffer->SetVertexElement(vertex, positionOffset, sizeof(Vector3), &topLeft);
        mVertexBuffer->SetVertexElement(vertex++, uvOffset, 8, &uvTopLeft);

        mVertexBuffer->SetVertexElement(vertex, positionOffset, sizeof(Vector3), &topRight);
        mVertexBuffer->SetVertexElement(vertex++, uvOffset, 8, &uvTopRight);

        mVertexBuffer->SetVertexElement(vertex, positionOffset, sizeof(Vector3), &bottomLeft);
        mVertexBuffer->SetVertexElement(vertex++, uvOffset, 8, &uvBotLeft);
        
        mVertexBuffer->SetVertexElement(vertex, positionOffset, sizeof(Vector3), &bottomLeft);
        mVertexBuffer->SetVertexElement(vertex++, uvOffset, 8, &uvBotLeft);

        mVertexBuffer->SetVertexElement(vertex, positionOffset, sizeof(Vector3), &topRight);
        mVertexBuffer->SetVertexElement(vertex++, uvOffset, 8, &uvTopRight);

        mVertexBuffer->SetVertexElement(vertex, positionOffset, sizeof(Vector3), &bottomRight);
        mVertexBuffer->SetVertexElement(vertex++, uvOffset, 8, &uvBotRight);
    }
    delete mSprites;
    mSprites = 0;
    mVertexBuffer->Unlock();
}

void SpriteTexture::Draw(Renderer* renderer)
{
    // Finish building any sprites
    if( mSprites )
        Finish(renderer);

    if( mNumSprites && mVertexBuffer )
    {
        // Bind the vertex buffer
        renderer->SetVertexBuffer(0, mVertexBuffer);
        renderer->SetIndexBuffer(0);
        
        // Draw
        renderer->DrawSprites(mTexture, mNumSprites);
    }
}