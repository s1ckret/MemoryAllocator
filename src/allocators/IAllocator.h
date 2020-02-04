#pragma once

#include <cstddef>

class IAllocator {
public:
    IAllocator( );
    ~IAllocator( );

    virtual void * allocate( size_t size ) = 0;
    virtual void deallocate( void * data_ptr ) = 0;

    inline size_t getMaxMemory() const { return _maxMemory; };
    inline size_t getUsedMemory() const { return _usedMemory; };
    inline size_t getNumAllocations() const { return _numAllocations; };
protected:
    size_t _maxMemory;
    size_t _usedMemory;
    size_t _numAllocations;
};