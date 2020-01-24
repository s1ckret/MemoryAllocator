#include "gtest/gtest.h"
 
#include "AddFunction.h"

TEST( AddFunctionTest, Positive ) {
    EXPECT_EQ( 5, add( 3, 2 ) );
}

TEST( AddFunctionTest, Negative ) {
    EXPECT_EQ( 243, add( 255, -12 ) );
}

TEST( AddFunctionTest, Zero ) {
    EXPECT_EQ( 54, add( 0, 54 ) );
}
