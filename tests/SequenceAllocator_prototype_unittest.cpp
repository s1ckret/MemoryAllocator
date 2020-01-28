#include "gtest/gtest.h"

#include "Allocators/SequenceAllocator_prototype.h"
#include "EnviromentMacro.h"


TEST( AlignFunction, Zero ) {
    EXPECT_EQ( align( 0 ), 0 );
}

TEST( AlignFunction, OneWord ) {
#ifdef ENVIRONMENT64
    EXPECT_EQ( align( 3 ), WORD );
    EXPECT_EQ( align( 7 ), WORD );
    EXPECT_EQ( align( WORD ), WORD );
#endif 
#ifdef ENVIRONMENT32
    EXPECT_EQ( align( 3 ), WORD );
    EXPECT_EQ( align( WORD ), WORD );
#endif 
}

TEST( AlignFunction, OneMegabyte ) {
#ifdef ENVIRONMENT64
    EXPECT_EQ( align( 1023 ), 1024 );
    EXPECT_EQ( align( 1032 ), 1032 );
    EXPECT_EQ( align( 1020 ), 1024 );
#endif 
#ifdef ENVIRONMENT32
    EXPECT_EQ( align( 1020 ), 1020 );
    EXPECT_EQ( align( 1023 ), 1024 );
    EXPECT_EQ( align( 1026 ), 1028 );
    EXPECT_EQ( align( 1032 ), 1032 );
#endif 
}

