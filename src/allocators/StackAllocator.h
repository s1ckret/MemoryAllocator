#pragma once

#include "IAllocator.h"

class StackAllocator : public IAllocator {
public:
    StackAllocator( );
    ~StackAllocator( );

    void * allocate( size_t size ) override;
    void deallocate( void * data_ptr ) override;
    void flush( );

private:
#ifdef _DEBUG
    void info( ) override;
#endif

private:
    void * _start;
    void * _end;

// Offset counts in bytes.
    size_t _offset;

    struct BlockHeader {
        size_t blockSize;
    };
};