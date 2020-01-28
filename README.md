# MemoryAllocator
Learn sequence, free list, pool memory allocators for L-system project.
## How to build
You need to have bazel installed.
// TODO: Add Cmake build file.
### BUILD file contains three targets namely
- MemoryAllocator  *(dynamic library)*
- MemoryAllocator_main  *(client part that depends on library)*
- MemoryAllocator_test  *(unit tests for library)*

### 64 or 32 bit
If you are under 64 or 32 bit machine and want to build 64 or 32 bit app respectively, then run next command
```shell
bazel build :<Target Name>
# Example
bazel build :MemoryAllocator
```
 *Note: you have to be in folder with WORKSPACE file.*
 
### 64 bit to 32 bit
If you are under 64 bit machine and want to build for 32 bit, then run next command
```shell
bazel build :<Target Name> --copt=-m32 --cxxopt=-m32 --linkopt=-m32
# Example
bazel build :MemoryAllocator --copt=-m32 --cxxopt=-m32 --linkopt=-m32
```
 *Note: you have to be in folder with WORKSPACE file.*

