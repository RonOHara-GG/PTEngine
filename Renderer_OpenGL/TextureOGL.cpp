#include "..\PTEngine.h"
#include "TextureOGL.h"
#include "gl.h"


TextureOGL::TextureOGL(void)
{
    mTexture = 0;
}

TextureOGL::~TextureOGL(void)
{
}

bool TextureOGL::Init(DDS* dds)
{
    if( mTexture )
        return false;

    if( dds->HasDDSHeader10() )
        return false;   // Not supporting dx10 dds files yet

    uint blockSize = dds->mPixelFormat.mRGBBitCount;
    bool dxt = false;
    uint format = 0;
    uint dataFormat = 0;
    uint dataType = GL_UNSIGNED_BYTE;

    if( dds->HasFourCC() )
    {
        blockSize = 16;
        dxt = true;
        switch( dds->mPixelFormat.mFourCC )
        {
            case D3DFMT_DXT1:
                format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                blockSize = 8;
                break;
            case D3DFMT_DXT2:
            case D3DFMT_DXT3:
                format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                break;
            case D3DFMT_DXT4:
            case D3DFMT_DXT5:
                format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                break;
            default:
                break;       // Currently Unsupported format
        }
    }
    else if( dds->HasRGB() )
    {
        if( dds->HasAlphaPixels() )
        {
            if( dds->mPixelFormat.mRGBBitCount == 32 )
            {
                if( dds->mPixelFormat.mRedMask == 0x3ff00000 )
                    format = GL_RGB10_A2_EXT;
                else
                {
                    format = GL_RGBA;
                    dataFormat = GL_BGRA;
                }
            }
            else // 16 bit
            {
                if( dds->mPixelFormat.mRedMask == 0xf00 )
                    format = GL_RGBA4_EXT;
            }
        }
        else
        {
            if( dds->mPixelFormat.mRGBBitCount == 32 )
            {
                format = GL_RGBA8_EXT;
            }
            else if( dds->mPixelFormat.mRGBBitCount == 24 )
            {
                format = GL_RGB8_EXT;
            }
            else // 16 bit
            {
                if( dds->mPixelFormat.mRedMask == 0x7c00 )
                    format = GL_RGB5_EXT;
                else
                    format = GL_RGB4_EXT;
            }
        }
    }
    else if( dds->HasLuminance() )
    {
        if( dds->mPixelFormat.mRGBBitCount == 16 )
        {
            if( dds->mPixelFormat.mRedMask == 0xffff )
                format = GL_LUMINANCE16_EXT;
            else
                format = GL_LUMINANCE8_ALPHA8_EXT;
        }
        else    // 8 bit
        {
            if( dds->mPixelFormat.mRedMask == 0xF )
                format = GL_LUMINANCE4_ALPHA4_EXT;
            else
                format = GL_LUMINANCE8_EXT;
        }
    }
    if( format == 0 )
        return false;
    if( dataFormat == 0 )
        dataFormat = format;

    // Copy the DDS header for later
    mDDS = *dds;

    // Create a named texture
    glGenTextures(1, &mTexture);

    // Setup the texture
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );

    // Copy the pixel data
    char* dataPtr = (char*)(dds + 1);
    uint width = dds->mWidth;
    uint height = dds->mHeight;
    uint levels = (dds->mMipMapCount == 0) ? 1 : dds->mMipMapCount;
            
    for( uint i = 0; i < levels; i++ )
    {
        uint size = 0;
        if( dxt )
        {
            size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
            glCompressedTexImage2D(GL_TEXTURE_2D, i, format, width, height, 0, size, dataPtr);
        }
        else
        {
            size = width * height * (dds->mPixelFormat.mRGBBitCount / 8);
            glTexImage2D(GL_TEXTURE_2D, i, format, width, height, 0, dataFormat, dataType, dataPtr);
        }

        dataPtr += size;
        width >>= 1;
        height >>= 1;
        if( width < 1 || height < 1 )
            break;
    }
    
    return true;
}

void TextureOGL::Bind()
{
    if( mTexture )
    {
        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture);

        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );    
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    }
}