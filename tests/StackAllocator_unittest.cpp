#include "gtest/gtest.h"

#include "allocators/StackAllocator.h"
#include "EnviromentMacro.h"

#define HEADER_SIZE WORD_SIZE

TEST( StackAllocator, NumberOfAllocation ) {
    StackAllocator allocator;
    void * p1 = allocator.allocate( WORD_SIZE );
    void * p2 = allocator.allocate( WORD_SIZE );
    void * p3 = allocator.allocate( WORD_SIZE );
    void * p4 = allocator.allocate( WORD_SIZE );

    EXPECT_EQ( allocator.getNumAllocations(), 4 );

    allocator.deallocate( p4 );
    allocator.deallocate( p3 );

    EXPECT_EQ( allocator.getNumAllocations(), 2 );

    allocator.deallocate( p2 );
    allocator.deallocate( p1 );

    EXPECT_EQ( allocator.getNumAllocations(), 0 );
}

TEST( StackAllocator, SameSizeAllocation ) {
    StackAllocator allocator;
    void * p1 = allocator.allocate( WORD_SIZE );
    void * p2 = allocator.allocate( WORD_SIZE );
    void * p3 = allocator.allocate( WORD_SIZE );
    void * p4 = allocator.allocate( WORD_SIZE );

    //                                   Data            Headers        
    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );

    allocator.deallocate( p4 );
    allocator.deallocate( p3 );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE  );
    EXPECT_EQ( allocator.getUsedMemory(), 2 * WORD_SIZE + 2 * HEADER_SIZE);

    allocator.deallocate( p2 );
    allocator.deallocate( p1 );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE  );
    EXPECT_EQ( allocator.getUsedMemory(), 0 * WORD_SIZE + 0 * HEADER_SIZE );
}

TEST( StackAllocator, SameSizeReuseAllocation ) {
    StackAllocator allocator;
    void * p1 = allocator.allocate( WORD_SIZE );
    void * p2 = allocator.allocate( WORD_SIZE );
    void * p3 = allocator.allocate( WORD_SIZE );
    void * p4 = allocator.allocate( WORD_SIZE );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );

    allocator.deallocate( p4 );
    allocator.deallocate( p3 );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 2 * WORD_SIZE + 2 * HEADER_SIZE );

    p3 = allocator.allocate( WORD_SIZE );
    p4 = allocator.allocate( WORD_SIZE );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );

    allocator.deallocate( p4 );
    allocator.deallocate( p3 );
    allocator.deallocate( p2 );
    allocator.deallocate( p1 );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 4 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 0 * WORD_SIZE + 0 * HEADER_SIZE );
}

TEST( StackAllocator, DifferentSizeAllocation ) {
    StackAllocator allocator;
    void * p1 = allocator.allocate( WORD_SIZE );
    void * p2 = allocator.allocate( 2 * WORD_SIZE );
    void * p3 = allocator.allocate( 3 * WORD_SIZE );
    void * p4 = allocator.allocate( WORD_SIZE );

    EXPECT_EQ( allocator.getMaxMemory(), 7 * WORD_SIZE + 4 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 7 * WORD_SIZE + 4 * HEADER_SIZE );

    allocator.deallocate( p4 );
    allocator.deallocate( p3 );
    allocator.deallocate( p2 );
    allocator.deallocate( p1 );

    EXPECT_EQ( allocator.getMaxMemory(), 7 * WORD_SIZE + 4 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 0 * WORD_SIZE + 0 * HEADER_SIZE );
}

TEST( StackAllocator, DifferentSizeReuseAllocation ) {
    StackAllocator allocator;
    void * p1 = allocator.allocate( WORD_SIZE );
    void * p2 = allocator.allocate( WORD_SIZE );

    EXPECT_EQ( allocator.getMaxMemory(), 2 * WORD_SIZE + 2 * HEADER_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 2 * WORD_SIZE + 2 * HEADER_SIZE );

    allocator.deallocate( p2 );

    void * p3 = allocator.allocate( 3 * WORD_SIZE );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 2 * WORD_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 4 * WORD_SIZE + 2 * WORD_SIZE );

    allocator.deallocate( p3 );
    allocator.deallocate( p1 );

    EXPECT_EQ( allocator.getMaxMemory(), 4 * WORD_SIZE + 2 * WORD_SIZE );
    EXPECT_EQ( allocator.getUsedMemory(), 0 * WORD_SIZE + 0 * HEADER_SIZE );
}