#pragma once

#include <utility>

inline size_t align( size_t n ) {
    return ( n + sizeof( word_t ) - 1 ) & ~( sizeof( word_t ) - 1 );
}

inline size_t allocSize( size_t size ) {
    return size + sizeof( Block ) - sizeof( std::declval<Block>().data );
}