#include "IAllocator.h"

#include <assert.h>

IAllocator::IAllocator() {

}

IAllocator::~IAllocator() {
    assert( _numAllocations == 0 && _usedMemory == 0 );
}