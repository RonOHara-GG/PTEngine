#ifndef _DDS_H_
#define _DDS_H_


#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((uint)(unsigned char)(ch0) | ((uint)(unsigned char)(ch1) << 8) |   \
                ((uint)(unsigned char)(ch2) << 16) | ((uint)(unsigned char)(ch3) << 24 ))
#endif

#define D3DFMT_DXT1     (MAKEFOURCC('D', 'X', 'T', '1'))
#define D3DFMT_DXT2     (MAKEFOURCC('D', 'X', 'T', '2'))
#define D3DFMT_DXT3     (MAKEFOURCC('D', 'X', 'T', '3'))
#define D3DFMT_DXT4     (MAKEFOURCC('D', 'X', 'T', '4'))
#define D3DFMT_DXT5     (MAKEFOURCC('D', 'X', 'T', '5'))

#define DDPF_ALPHAPIXELS    0x1
#define DDPF_ALPHA          0x2
#define DDPF_FOURCC         0x4
#define DDPF_RGB            0x40
#define DDPF_YUV            0x200
#define DDPF_LUMINANCE      0x20000

#define DDSCAPS_COMPLEX     0x8
#define DDSCAPS_MIPMAP      0x400000
#define DDSCAPS_TEXTURE     0x1000

#define DDSCAPS2_CUBEMAP            0x200
#define DDSCAPS2_CUBEMAP_POSITIVEX  0x400
#define DDSCAPS2_CUBEMAP_NEGATIVEX  0x800
#define DDSCAPS2_CUBEMAP_POSITIVEY  0x1000
#define DDSCAPS2_CUBEMAP_NEGATIVEY  0x2000
#define DDSCAPS2_CUBEMAP_POSITIVEZ  0x4000
#define DDSCAPS2_CUBEMAP_NEGATIVEZ  0x8000
#define DDSCAPS2_VOLUME             0x200000

typedef struct 
{
    uint    mDXGIFormat;
    uint    mResourceDimension;
    uint    mMiscFlag;
    uint    mArraySize;
    uint    mReserved;
} DDSHeader10;

typedef struct 
{
    uint    mSize;
    uint    mFlags;
    uint    mFourCC;
    uint    mRGBBitCount;
    uint    mRedMask;
    uint    mGreenMask;
    uint    mBlueMask; 
    uint    mAlphaMask;
} DDSPixelFormat;

struct DDS
{
    uint            mMagicNumber;       // 'DDS ' 0x20534444
    uint            mSize;
    uint            mFlags;
    uint            mHeight;
    uint            mWidth;
    uint            mPitchOrLinearSize;
    uint            mDepth;
    uint            mMipMapCount;
    uint            mReserved1[11];
    DDSPixelFormat  mPixelFormat;
    uint            mCaps;
    uint            mCaps2;
    uint            mCaps3;
    uint            mCaps4;
    uint            mReserved2;

    bool HasDDSHeader10()       { return (HasFourCC() && (mPixelFormat.mFourCC == 'DX10')); }
    bool HasAlphaPixels()       { return ((mPixelFormat.mFlags & DDPF_ALPHAPIXELS) == DDPF_ALPHAPIXELS); }
    bool HasAlpha()             { return ((mPixelFormat.mFlags & DDPF_ALPHA) == DDPF_ALPHA); }
    bool HasFourCC()            { return ((mPixelFormat.mFlags & DDPF_FOURCC) == DDPF_FOURCC); }
    bool HasRGB()               { return ((mPixelFormat.mFlags & DDPF_RGB) == DDPF_RGB); }
    bool HasYUV()               { return ((mPixelFormat.mFlags & DDPF_YUV) == DDPF_YUV); }
    bool HasLuminance()         { return ((mPixelFormat.mFlags & DDPF_LUMINANCE) == DDPF_LUMINANCE); }
    bool IsCubemap()            { return ((mCaps2 & DDSCAPS2_CUBEMAP) == DDSCAPS2_CUBEMAP); }
    bool IsVolume()             { return ((mCaps2 & DDSCAPS2_VOLUME) == DDSCAPS2_VOLUME); }
    
    unsigned char*  GetDataPointer()    { return (unsigned char*)(((unsigned char*)(this + 1)) + HasDDSHeader10() ? sizeof(DDSHeader10) : 0); }
    DDSHeader10*    GetDDSHeader10()    { return (DDSHeader10*)(this + 1); }
};

#endif // _DDS_H_