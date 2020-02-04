#pragma once

#include "IAllocator.h"

class SequenceAllocator : public IAllocator {
public:
    SequenceAllocator( );
    ~SequenceAllocator( );

    void * allocate( size_t size ) override;
    void deallocate( void * data_ptr ) override;
    void flush( );
};