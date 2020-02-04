#include "IAllocator.h"

#include <cassert>

IAllocator::IAllocator( ) {

}

IAllocator::~IAllocator( ) {
    assert( _numAllocations == 0 && _usedMemory == 0 );
}