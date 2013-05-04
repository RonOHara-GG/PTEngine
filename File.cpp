#include "PTEngine.h"
#include "File.h"

File::File(void* data, uint size)
{
    mData = data;
    mSize = size;
}

File::~File()
{
    if( mData )
    {
        free(mData);
        mData = 0;
    }
}