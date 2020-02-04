#include "SequenceAllocator.h"
#include "src/platform/Utils.h"

#include <cassert>

void * SequenceAllocator::allocate( size_t size ) {
    size = Utils::align( size );

    _maxMemory += size;
    _usedMemory += size;
    _numAllocations++;

    return Utils::requestFromOS( size );
}

void SequenceAllocator::deallocate( void * data_ptr ) {
    assert( false && "Use flush() instead!" );
}

void SequenceAllocator::flush( ) {
    _maxMemory = 0;
    _usedMemory = 0;
    _numAllocations = 0;
}