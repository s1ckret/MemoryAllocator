#include "src/EnviromentMacro.h"

namespace Utils {
    inline size_t align( size_t n ) {
    return ( n + WORD_SIZE - 1 ) & ~( WORD_SIZE - 1 );
    }
};