#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "Debug.h"

class Assert
{
public:
    enum eAssertChoice
    {
        eAssert_Exit,
        eAssert_Debug,
        eAssert_Ignore,
        eAssert_IgnoreAll
    };

    Assert()
    {
        sAssertsIgnored = false;
    }
        

    virtual inline bool AreAssertsIgnored()        { return sAssertsIgnored; }
    virtual eAssertChoice ShowDialog();

protected:
    bool sAssertsIgnored;   

public:
    static Assert* sInstance;
};

#define ASSERT(assertCondition)                                             \
    if( !(assertCondition) && !Assert::sInstance->AreAssertsIgnored() )     \
    {                                                                       \
        if( DEBUG_IsDebuggerPresent )                                       \
        {                                                                   \
            DEBUG_Break;                                                    \
        }                                                                   \
        else                                                                \
        {                                                                   \
            if( Assert::sInstance->ShowDialog() == Assert::eAssert_Debug )  \
            {                                                               \
                DEBUG_Break;                                                \
            }                                                               \
        }                                                                   \
    }
#endif

