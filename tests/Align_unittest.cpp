#include "gtest/gtest.h"

#include "platform/Utils.h"
#include "EnviromentMacro.h"

#ifdef ENVIRONMENT64
    TEST( AlignFunction, Environment64 ) {
        EXPECT_EQ( Utils::align( 0 ), 0 );
        EXPECT_EQ( Utils::align( 4 ), WORD_SIZE);
        EXPECT_EQ( Utils::align( 7 ), WORD_SIZE );
        EXPECT_EQ( Utils::align( 8 ), WORD_SIZE );
        EXPECT_EQ( Utils::align( 124 ), 128 );
    }
#endif
#ifdef ENVIRONMENT32
    TEST( AlignFunction, Environment32 ) {
        EXPECT_EQ( Utils::align( 0 ), 0 );
        EXPECT_EQ( Utils::align( 4 ), WORD_SIZE );
        EXPECT_EQ( Utils::align( 7 ), 2 * WORD_SIZE );
        EXPECT_EQ( Utils::align( 8 ), 2 * WORD_SIZE );
        EXPECT_EQ( Utils::align( 124 ), 124 );
    }
#endif