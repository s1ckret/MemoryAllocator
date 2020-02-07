#include "src/platform/Utils.h"

#include <unistd.h>     /* sbrk() */
#include <assert.h>

namespace Utils {

#if __GNUC__
    void * requestFromOS( size_t size ) {
        void * block = sbrk( 0 );
        // Out of memory
        if ( sbrk( size ) == reinterpret_cast<void*>( -1 ) ) {
            return nullptr;
        }
        return block;
    }

    void * getCurrentBreak( ) {
        return sbrk( 0 );
    }
#endif

};