#include "StackAllocator.h"
#include "src/platform/Utils.h"

#include <cassert>

StackAllocator::StackAllocator( ) 
    : _start( nullptr ) 
    , _end( nullptr )
    , _offset( 0 )
{
    _start = Utils::getCurrentBreak( );
    _end = _start;
}

StackAllocator::~StackAllocator( ) {
    assert( _offset == 0 );
}

void * StackAllocator::allocate( size_t size ) {
    size = Utils::align( size + sizeof( BlockHeader ) );
    
    void * currentAddress = reinterpret_cast<byte_t*>( _start ) + _offset;

    void * block = nullptr;
    if ( _usedMemory + size < _maxMemory ) {
          // Block reuse
        block = currentAddress;
    }
    else {
        // Allocate new memory
        if ( _usedMemory == _maxMemory ) {
            // All space is occupied.
            // Request *size* amount of bytes
            block = Utils::requestFromOS( size );

            if ( block ) {
                _end = reinterpret_cast<byte_t*>( _end ) + size;
                _maxMemory += size;
            }
        }
        else {
            // We have some unmapped space.
            // We dont have enough space.
            size_t sizeToAllocate = size + _usedMemory - _maxMemory;
            Utils::requestFromOS( sizeToAllocate );
            
            block = currentAddress;

            if ( block ) {
                _end = reinterpret_cast<byte_t*>( _end ) + sizeToAllocate;
                _maxMemory += sizeToAllocate;
            }
        }
    }

    void * dataBlock = nullptr;
    if ( block ) {
        BlockHeader * blockHeader = reinterpret_cast<BlockHeader*>( block );
        blockHeader->blockSize = size;
        
        _offset += size;

        _usedMemory += size;
        _numAllocations++;

        dataBlock = reinterpret_cast<byte_t*>( block ) + sizeof( BlockHeader );
    }
    // else out of memory

#ifdef _DEBUG
    info( );
#endif

    return dataBlock;
}

void StackAllocator::deallocate( void * data_ptr ) {
    BlockHeader * blockHeader = reinterpret_cast<BlockHeader*>( reinterpret_cast<byte_t*>( data_ptr ) - sizeof( BlockHeader ) );
    _offset -= blockHeader->blockSize;
    _usedMemory -= blockHeader->blockSize;
    _numAllocations--;
#ifdef _DEBUG
    info( );
#endif
}

void StackAllocator::flush( ) {
    _maxMemory = 0;
    _usedMemory = 0;
    _numAllocations = 0;

    _offset = 0;
    _end = _start;
}

#ifdef _DEBUG
#include <iostream>

void StackAllocator::info( ) {
    IAllocator::info( );
    std::cout << "Heap start pointer: 0x" << _start << "\n";
    std::cout << "Heap end pointer: 0x" << _end << "\n";
    std::cout << "Offset: " << _offset << "\n\n";
       
}
#endif