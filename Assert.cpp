#include "PTEngine.h"
#include "Assert.h"


bool Assert::sAssertsIgnored = false;

Assert::eAssertChoice Assert::ShowDialog()
{
    return eAssert_Debug;
}