#include "SequenceAllocator_prototype.h"

#include <unistd.h>  
#include <utility>

static Block * heapStart = nullptr;
static Block * heapTop = heapStart;

word_t * alloc( size_t size ) {
    size = align( size );

    Block * block = requesFromOs( size );
    block->size = size;
    block->isUsed = true;

    // Init heap
    if ( !heapStart ) {
        heapStart = block;
    }

    // Chaining
    if ( !heapTop ) {
        heapTop->next = block;
    }
    heapTop = block;

    return block->data;
}

void free( word_t * data) {
    Block * block = getHeader( data );
    block->isUsed = false;
}

Block * requesFromOs( size_t size ) {
    Block * block = reinterpret_cast<Block*>( sbrk( 0 ) );

    if ( sbrk( allocSize( size ) ) == reinterpret_cast<void*>( -1 ) ) {
        return nullptr;
    }

    return block;
}

Block * getHeader( word_t * data ) {
    return reinterpret_cast<Block*>( reinterpret_cast<char*>( data ) - sizeof( Block ) + sizeof( std::declval<Block>().data ) );
}