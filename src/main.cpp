#include <string>

#include "gtest/gtest.h"

std::string getDeveloperName( ) {
    return "S1ckret";
}

TEST( HelloWorld, DeveloperName ) {
    EXPECT_EQ( "S1ckret", getDeveloperName( ) );
}

int main( int argc, char* argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}