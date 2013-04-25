#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "Debug.h"

namespace Assert
{
    enum eAssertChoice
    {
        eAssert_Exit,
        eAssert_Debug,
        eAssert_Ignore,
        eAssert_IgnoreAll
    };

    extern bool sAssertsIgnored;

    inline bool AreAssertsIgnored()        { return sAssertsIgnored; }
    
    eAssertChoice ShowDialog();
};

#define ASSERT(assertCondition)                                         \
    if( !(assertCondition) && !Assert::AreAssertsIgnored() )            \
    {                                                                   \
        if( DEBUG_IsDebuggerPresent )                                   \
        {                                                               \
            DEBUG_Break;                                                \
        }                                                               \
        else                                                            \
        {                                                               \
            if( Assert::ShowDialog() == Assert::eAssert_Debug )         \
            {                                                           \
                DEBUG_Break;                                            \
            }                                                           \
        }                                                               \
    }
#endif

