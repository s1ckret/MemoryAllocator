#include "IAllocator.h"

#include <cassert>

IAllocator::IAllocator( )
    : _maxMemory( 0 )
    , _usedMemory( 0 )
    , _numAllocations( 0 ) 
{

}

IAllocator::~IAllocator( ) {
    assert( _numAllocations == 0 && _usedMemory == 0 );
}

#ifdef _DEBUG
#include <iostream>

void IAllocator::info( ) {
    std::cout << "Allocator status:\n";
    std::cout << "Max Memory: " << _maxMemory << " bytes.\n";
    std::cout << "Used Memory: " << _usedMemory << " bytes.\n";
    std::cout << "Number of allocations: " << _numAllocations << ".\n";
}
#endif