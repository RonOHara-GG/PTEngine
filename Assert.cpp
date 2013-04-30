#include "PTEngine.h"
#include "Assert.h"

static Assert sAssert;
Assert* Assert::sInstance = &sAssert;

Assert::eAssertChoice Assert::ShowDialog()
{
    return eAssert_Debug;
}