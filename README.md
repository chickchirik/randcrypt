# randcrypt
encryption/decryption library that uses random algorithms

## Build Instructions
build instructions may differ in the future releases

### Requirements

- [git](https://git-scm.com/)
- [cmake](https://cmake.org/)
- [gcc](https://www.gnu.org/software/gcc/) or [clang](https://clang.llvm.org/) or [msvc](https://visualstudio.microsoft.com/)

### Building
Remember to rename project and subproject directories and their references in CMakeLists configurations.

```bash
$ mkdir bin
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ../
$ make
$ make install
$ cd..
```
or
```bash
$ mkdir bin; mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=Debug ../; make ;make install; cd..
```

### Running

```bash
$ ./bin/SUBPROJECT
```

### Links

- CMake: https://cmake.org/
- CMake documentation: https://cmake.org/documentation/
- CMake FAQ: https://gitlab.kitware.com/cmake/community/wikis/FAQ
