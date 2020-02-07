#pragma once

#include <cstddef>

namespace Utils {

    void * requestFromOS( size_t size );

    void * getCurrentBreak( );

    inline size_t align( size_t size );
};

#include "Utils.inl"