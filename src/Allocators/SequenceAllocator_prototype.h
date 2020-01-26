#pragma once

#include <stdint.h>
#include <cstddef>

// Can be 8 or 4 bytes, depending on architecture
using word_t = intptr_t;

struct Block {
    // Header
    size_t size;
    bool isUsed;
    Block * next;
    
    // Data
    word_t * data;

};

word_t * alloc( size_t size );
void free( word_t * data);

Block * requesFromOs( size_t size );

Block * getHeader( word_t * data );

inline size_t align( size_t n );
inline size_t allocSize( size_t size );

#include "SequenceAllocator_prototype.inl"